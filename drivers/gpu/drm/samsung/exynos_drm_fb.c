// SPDX-License-Identifier: GPL-2.0-only
/* exynos_drm_fb.c
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Authors:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <drm/drmP.h>
#include <drm/drm_crtc.h>
#include <drm/drm_crtc_helper.h>
#include <drm/drm_fb_helper.h>
#include <drm/drm_gem_framebuffer_helper.h>
#include <drm/drm_atomic.h>
#include <drm/drm_atomic_helper.h>
#include <uapi/drm/exynos_drm.h>
#include <uapi/linux/videodev2_exynos_media.h>
#include <linux/dma-buf.h>
#include <linux/ion_exynos.h>

#include <exynos_drm_decon.h>
#include <exynos_drm_drv.h>
#include <exynos_drm_fb.h>
#include <exynos_drm_fbdev.h>
#include <exynos_drm_crtc.h>
#include <exynos_drm_dsim.h>
#include <exynos_drm_format.h>
#include <exynos_drm_gem.h>
#include <exynos_drm_hibernation.h>

static const struct drm_framebuffer_funcs exynos_drm_fb_funcs = {
	.destroy	= drm_gem_fb_destroy,
	.create_handle	= drm_gem_fb_create_handle,
};

struct drm_framebuffer *
exynos_drm_framebuffer_init(struct drm_device *dev,
			    const struct drm_mode_fb_cmd2 *mode_cmd,
			    struct drm_gem_object **obj,
			    int count)
{
	struct drm_framebuffer *fb;
	int i;
	int ret;

	fb = kzalloc(sizeof(*fb), GFP_KERNEL);
	if (!fb)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < count; i++)
		fb->obj[i] = obj[i];

	drm_helper_mode_fill_fb_struct(dev, fb, mode_cmd);

	ret = drm_framebuffer_init(dev, fb, &exynos_drm_fb_funcs);
	if (ret < 0) {
		DRM_ERROR("failed to initialize framebuffer\n");
		kfree(fb);
		return ERR_PTR(ret);
	}

	return fb;
}

#define Y_SIZE_8P2(w, h)	(NV12N_10B_Y_8B_SIZE(w, h) +		\
					NV12N_10B_Y_2B_SIZE(w, h))
#define UV_SIZE_8P2(w, h)	(NV12N_10B_CBCR_8B_SIZE(w, h) +		\
					NV12N_10B_CBCR_2B_SIZE(w, h))
static struct drm_framebuffer *
exynos_user_fb_create(struct drm_device *dev, struct drm_file *file_priv,
		      const struct drm_mode_fb_cmd2 *mode_cmd)
{
	const struct drm_format_info *info = drm_get_format_info(dev, mode_cmd);
	struct drm_gem_object *obj[MAX_FB_BUFFER] = { 0 };
	struct drm_framebuffer *fb;
	u32 height;
	size_t size;
	int i;
	int ret;

	DRM_DEBUG("%s +\n", __func__);

	if (unlikely(info->num_planes > MAX_FB_BUFFER))
		return ERR_PTR(-EINVAL);

	for (i = 0; i < info->num_planes; i++) {
		height = (i == 0) ? mode_cmd->height :
				     DIV_ROUND_UP(mode_cmd->height, info->vsub);
		size = height * mode_cmd->pitches[i] + mode_cmd->offsets[i];

		if (mode_cmd->modifier[i] ==
				DRM_FORMAT_MOD_SAMSUNG_YUV_8_2_SPLIT) {
			if (i == 0)
				size = Y_SIZE_8P2(mode_cmd->width,
						mode_cmd->height);
			else if (i == 1)
				size = UV_SIZE_8P2(mode_cmd->width,
						mode_cmd->height);
		}

		if (mode_cmd->modifier[i] == DRM_FORMAT_MOD_SAMSUNG_COLORMAP) {
			struct exynos_drm_gem *exynos_gem;

			exynos_gem = exynos_drm_gem_alloc(dev, 0,
						EXYNOS_DRM_GEM_FLAG_COLORMAP);
			if (IS_ERR(exynos_gem)) {
				DRM_ERROR("failed to create colormap gem\n");
				ret = PTR_ERR(exynos_gem);
				goto err;
			}

			exynos_gem->dma_addr = mode_cmd->handles[i];
			obj[i] = &exynos_gem->base;
			continue;
		}

		obj[i] = drm_gem_object_lookup(file_priv, mode_cmd->handles[i]);
		if (!obj[i]) {
			DRM_ERROR("failed to lookup gem object\n");
			ret = -ENOENT;
			goto err;
		}

		if (size > obj[i]->size) {
			i++;
			ret = -EINVAL;
			goto err;
		}
	}

	DRM_DEBUG("width(%d), height(%d), pitches(%d)\n", mode_cmd->width,
			mode_cmd->height, mode_cmd->pitches[0]);
	DRM_DEBUG("offset(%d), handle(%d), size(%lu)\n", mode_cmd->offsets[0],
			mode_cmd->handles[0], size);

	fb = exynos_drm_framebuffer_init(dev, mode_cmd, obj, i);
	if (IS_ERR(fb)) {
		ret = PTR_ERR(fb);
		goto err;
	}

	return fb;

err:
	while (i--)
		drm_gem_object_put_unlocked(obj[i]);

	return ERR_PTR(ret);

}

static const struct drm_format_info *
exynos_get_format_info(const struct drm_mode_fb_cmd2 *cmd)
{
	struct drm_format_name_buf n;
	const char *format_name;
	const struct drm_format_info *info = NULL;

	if (cmd->modifier[0] == DRM_FORMAT_MOD_SAMSUNG_COLORMAP) {
		info = drm_format_info(cmd->pixel_format);
		if (info->format == DRM_FORMAT_BGRA8888)
			return info;

		format_name = drm_get_format_name(info->format, &n);
		DRM_WARN("%s is not proper format for colormap\n", format_name);
	}

	return NULL;
}

dma_addr_t exynos_drm_fb_dma_addr(const struct drm_framebuffer *fb, int index)
{
	const struct exynos_drm_gem *exynos_gem;

	if (WARN_ON_ONCE(index >= MAX_FB_BUFFER) || !fb->obj[index])
		return 0;

	exynos_gem = to_exynos_gem(fb->obj[index]);

	DRM_DEBUG("%s:%d, dma_addr[%d] = 0x%llx (+%llx)\n", __func__, __LINE__,
			index, exynos_gem->dma_addr, fb->offsets[index]);

	return exynos_gem->dma_addr + fb->offsets[index];
}

void plane_state_to_win_config(struct decon_device *decon,
		struct exynos_drm_plane_state *state, int plane_idx)
{
	struct dpu_bts_win_config *win_config;
	const struct drm_framebuffer *fb = state->base.fb;
	int zpos;
	unsigned int simplified_rot;

	zpos = state->base.normalized_zpos;
	win_config = &decon->bts.win_config[zpos];

	win_config->src_x = state->base.src_x >> 16;
	win_config->src_y = state->base.src_y >> 16;
	win_config->src_w = state->base.src_w >> 16;
	win_config->src_h = state->base.src_h >> 16;

	win_config->dst_x = state->base.crtc_x;
	win_config->dst_y = state->base.crtc_y;
	win_config->dst_w = state->base.crtc_w;
	win_config->dst_h = state->base.crtc_h;

	if (fb->modifier & DRM_FORMAT_MOD_ARM_AFBC(0) ||
			fb->modifier == DRM_FORMAT_MOD_SAMSUNG_SBWC)
		win_config->is_comp = true;
	else
		win_config->is_comp = false;

	if (exynos_drm_fb_is_colormap(fb))
		win_config->state = DPU_WIN_STATE_COLOR;
	else
		win_config->state = DPU_WIN_STATE_BUFFER;

	win_config->format = fb->format->format;
	win_config->dpp_ch = plane_idx;

	win_config->comp_src = 0;
	if (win_config->is_comp)
		win_config->comp_src =
			(fb->modifier & AFBC_FORMAT_MOD_SOURCE_MASK);

	simplified_rot = drm_rotation_simplify(state->base.rotation,
			DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_90 |
			DRM_MODE_REFLECT_X | DRM_MODE_REFLECT_Y);
	win_config->is_rot = false;
	if (simplified_rot & DRM_MODE_ROTATE_90)
		win_config->is_rot = true;

	decon->dpp[plane_idx]->dbg_dma_addr = exynos_drm_fb_dma_addr(fb, 0);

	DRM_DEBUG("src[%d %d %d %d], dst[%d %d %d %d]\n",
			win_config->src_x, win_config->src_y,
			win_config->src_w, win_config->src_h,
			win_config->dst_x, win_config->dst_y,
			win_config->dst_w, win_config->dst_h);
	DRM_DEBUG("rot[%d] afbc[%d] format[%d] ch[%d] zpos[%d] comp_src[%lu]\n",
			win_config->is_rot, win_config->is_comp,
			win_config->format, win_config->dpp_ch, zpos,
			win_config->comp_src);
	DRM_DEBUG("alpha[%d] blend mode[%d]\n",
			state->base.alpha, state->base.pixel_blend_mode);
	DRM_DEBUG("simplified rot[0x%x]\n", simplified_rot);
}

static void display_mode_to_bts_info(struct drm_display_mode *mode,
		struct decon_device *decon)
{
	struct videomode vm;

	drm_display_mode_to_videomode(mode, &vm);

	decon->config.image_width = vm.hactive;
	decon->config.image_height = vm.vactive;
	decon->config.dsc.slice_width = DIV_ROUND_UP(decon->config.image_width,
			decon->config.dsc.slice_count);
	decon->bts.vbp = vm.vback_porch;
	decon->bts.vfp = vm.vfront_porch;
	decon->bts.vsa = vm.vsync_len;
	decon->bts.fps = mode->vrefresh;
}

void exynos_atomic_commit_tail(struct drm_atomic_state *old_state)
{
	int i, j;
	struct drm_plane *plane;
	struct drm_plane_state *new_plane_state;
	struct exynos_drm_plane_state *new_exynos_state;
	struct exynos_drm_crtc *exynos_crtc;
	struct decon_device *decon[MAX_DECON_CNT] = {};
	struct drm_crtc *crtc;
	struct drm_crtc_state *old_crtc_state, *new_crtc_state;
	const struct dpu_bts_win_config *win_config;
	struct dpp_device *dpp;
	int max_planes;
	int id = 0;

	for_each_oldnew_crtc_in_state(old_state, crtc, old_crtc_state,
			new_crtc_state, i) {
		DRM_DEBUG("[CRTC:%d:%s] old en:%d active:%d change[%d %d %d]\n",
				crtc->base.id, crtc->name,
				old_crtc_state->enable, old_crtc_state->active,
				old_crtc_state->planes_changed,
				old_crtc_state->mode_changed,
				old_crtc_state->active_changed);

		DRM_DEBUG("[CRTC:%d:%s] new en:%d active:%d change[%d %d %d]\n",
				crtc->base.id, crtc->name,
				new_crtc_state->enable, new_crtc_state->active,
				new_crtc_state->planes_changed,
				new_crtc_state->mode_changed,
				new_crtc_state->active_changed);

		exynos_crtc = container_of(crtc, struct exynos_drm_crtc, base);
		id = crtc->index;
		decon[id] = exynos_crtc->ctx;

		/* acquire initial bandwidth when DECON is enabled. */
		if (!old_crtc_state->active && new_crtc_state->active) {
			display_mode_to_bts_info(&new_crtc_state->mode,
					decon[id]);

			if (IS_ENABLED(CONFIG_EXYNOS_BTS))
				decon[id]->bts.ops->bts_acquire_bw(decon[id]);
		}

		/* initialize BTS structure of each DECON */
		if (new_crtc_state->planes_changed && new_crtc_state->active) {
			max_planes =
				old_state->dev->mode_config.num_total_plane;
			for (j = 0; j < max_planes; ++j) {
				decon[id]->bts.win_config[j].state =
					DPU_WIN_STATE_DISABLED;
				decon[id]->dpp[i]->dbg_dma_addr = 0;
			}
		}
	}

	for_each_new_plane_in_state(old_state, plane, new_plane_state, i) {
		if (!new_plane_state->crtc)
			continue;

		new_exynos_state = to_exynos_plane_state(new_plane_state);
		exynos_crtc = container_of(new_plane_state->crtc,
				struct exynos_drm_crtc, base);
		id = new_plane_state->crtc->index;
		decon[id] = exynos_crtc->ctx;

		plane_state_to_win_config(decon[id], new_exynos_state, i);
	}

	for_each_oldnew_crtc_in_state(old_state, crtc, old_crtc_state,
			new_crtc_state, i) {
		exynos_crtc = container_of(crtc, struct exynos_drm_crtc, base);
		id = crtc->index;
		decon[id] = exynos_crtc->ctx;

		if (new_crtc_state->planes_changed && new_crtc_state->active) {
			DPU_EVENT_LOG_ATOMIC_COMMIT(decon[id]->id);
			if (IS_ENABLED(CONFIG_EXYNOS_BTS)) {
				decon[id]->bts.ops->bts_calc_bw(decon[i]);
				decon[id]->bts.ops->bts_update_bw(decon[i],
						false);
			}
		}

		if (new_crtc_state->active)
			hibernation_block_exit(decon[id]->hibernation);
	}

	drm_atomic_helper_commit_tail_rpm(old_state);

	for_each_oldnew_crtc_in_state(old_state, crtc, old_crtc_state,
			new_crtc_state, i) {
		exynos_crtc = container_of(crtc, struct exynos_drm_crtc, base);
		id = crtc->index;
		decon[id] = exynos_crtc->ctx;

		if (new_crtc_state->planes_changed && new_crtc_state->active) {
			/* plane order == dpp channel order */
			for (j = 0; j < MAX_PLANE; ++j) {
				dpp = decon[id]->dpp[j];
				if (dpp->win_id >= MAX_PLANE)
					continue;

				win_config =
					&decon[id]->bts.win_config[dpp->win_id];
				if (win_config->state == DPU_WIN_STATE_BUFFER &&
						win_config->is_comp)
					dpp->comp_src = win_config->comp_src;
			}

			if (decon[id]->config.mode.op_mode ==
					DECON_MIPI_COMMAND_MODE) {
				DPU_EVENT_LOG(DPU_EVT_DECON_TRIG_MASK,
						decon[id]->id, NULL);
				decon_reg_set_trigger(decon[id]->id,
						&decon[id]->config.mode,
						DECON_TRIG_MASK);
			}

			if (IS_ENABLED(CONFIG_EXYNOS_BTS))
				decon[id]->bts.ops->bts_update_bw(decon[i],
						true);
			DPU_EVENT_LOG(DPU_EVT_DECON_RSC_OCCUPANCY, 0, NULL);
		}

		if (new_crtc_state->active)
			hibernation_unblock(decon[id]->hibernation);

		if ((old_crtc_state->active && !new_crtc_state->active) &&
				IS_ENABLED(CONFIG_EXYNOS_BTS))
			decon[id]->bts.ops->bts_release_bw(decon[id]);
	}
}

static struct drm_mode_config_helper_funcs exynos_drm_mode_config_helpers = {
	.atomic_commit_tail = exynos_atomic_commit_tail,
};

static const struct drm_mode_config_funcs exynos_drm_mode_config_funcs = {
	.fb_create = exynos_user_fb_create,
	.get_format_info = exynos_get_format_info,
	.output_poll_changed = exynos_drm_output_poll_changed,
	.atomic_check = exynos_atomic_check,
	.atomic_commit = drm_atomic_helper_commit,
};

void exynos_drm_mode_config_init(struct drm_device *dev)
{
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;

	/*
	 * set max width and height as default value(4096x4096).
	 * this value would be used to check framebuffer size limitation
	 * at drm_mode_addfb().
	 */
	dev->mode_config.max_width = 4096;
	dev->mode_config.max_height = 4096;

	dev->mode_config.funcs = &exynos_drm_mode_config_funcs;
	dev->mode_config.helper_private = &exynos_drm_mode_config_helpers;

	dev->mode_config.allow_fb_modifiers = true;
}
