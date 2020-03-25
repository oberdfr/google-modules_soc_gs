// SPDX-License-Identifier: GPL-2.0-only
/*
 * MIPI-DSI based s6e3hc2 AMOLED LCD panel driver.
 *
 * Copyright (c) 2019 Samsung Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/of_platform.h>
#include <linux/module.h>
#include <panel-samsung-drv.h>

static const unsigned char SEQ_PPS_WQHD[] = {
	// WQHD+ :1440x3040
	0x11, 0x00, 0x00, 0x89, 0x30, 0x80, 0x0B, 0xE0,
	0x05, 0xA0, 0x00, 0x28, 0x02, 0xD0, 0x02, 0xD0,
	0x02, 0x00, 0x02, 0x68, 0x00, 0x20, 0x04, 0x6C,
	0x00, 0x0A, 0x00, 0x0C, 0x02, 0x77, 0x01, 0xE9,
	0x18, 0x00, 0x10, 0xF0, 0x03, 0x0C, 0x20, 0x00,
	0x06, 0x0B, 0x0B, 0x33, 0x0E, 0x1C, 0x2A, 0x38,
	0x46, 0x54, 0x62, 0x69, 0x70, 0x77, 0x79, 0x7B,
	0x7D, 0x7E, 0x01, 0x02, 0x01, 0x00, 0x09, 0x40,
	0x09, 0xBE, 0x19, 0xFC, 0x19, 0xFA, 0x19, 0xF8,
	0x1A, 0x38, 0x1A, 0x78, 0x1A, 0xB6, 0x2A, 0xF6,
	0x2B, 0x34, 0x2B, 0x74, 0x3B, 0x74, 0x6B, 0xF4,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const unsigned char SEQ_PPS_FHD[] = {
	//FHD+ :1080x2340
	0x11, 0x00, 0x00, 0x89, 0x30, 0x80, 0x09, 0x24,
	0x04, 0x38, 0x00, 0x41, 0x02, 0x1C, 0x02, 0x1C,
	0x02, 0x00, 0x02, 0x0E, 0x00, 0x20, 0x06, 0x50,
	0x00, 0x07, 0x00, 0x0C, 0x01, 0x80, 0x01, 0x91,
	0x18, 0x00, 0x10, 0xF0, 0x03, 0x0C, 0x20, 0x00,
	0x06, 0x0B, 0x0B, 0x33, 0x0E, 0x1C, 0x2A, 0x38,
	0x46, 0x54, 0x62, 0x69, 0x70, 0x77, 0x79, 0x7B,
	0x7D, 0x7E, 0x01, 0x02, 0x01, 0x00, 0x09, 0x40,
	0x09, 0xBE, 0x19, 0xFC, 0x19, 0xFA, 0x19, 0xF8,
	0x1A, 0x38, 0x1A, 0x78, 0x1A, 0xB6, 0x2A, 0xF6,
	0x2B, 0x34, 0x2B, 0x74, 0x3B, 0x74, 0x6B, 0xF4,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static int s6e3hc2_disable(struct drm_panel *panel)
{
	struct exynos_panel *ctx;

	ctx = container_of(panel, struct exynos_panel, panel);
	ctx->enabled = false;
	dev_dbg(ctx->dev, "%s +\n", __func__);
	return 0;
}

static int s6e3hc2_unprepare(struct drm_panel *panel)
{
	struct exynos_panel *ctx;

	ctx = container_of(panel, struct exynos_panel, panel);

	dev_dbg(ctx->dev, "%s +\n", __func__);
	exynos_panel_set_power(ctx, false);
	dev_dbg(ctx->dev, "%s -\n", __func__);
	return 0;
}

static int s6e3hc2_prepare(struct drm_panel *panel)
{
	struct exynos_panel *ctx;

	ctx = container_of(panel, struct exynos_panel, panel);

	dev_dbg(ctx->dev, "%s +\n", __func__);
	exynos_panel_set_power(ctx, true);
	dev_dbg(ctx->dev, "%s -\n", __func__);

	return 0;
}

static int s6e3hc2_enable(struct drm_panel *panel)
{
	struct exynos_panel *ctx;

	ctx = container_of(panel, struct exynos_panel, panel);

	dev_dbg(ctx->dev, "%s +\n", __func__);

	exynos_panel_reset(ctx);

	EXYNOS_DCS_WRITE_SEQ(ctx, 0xf0, 0x5a, 0x5a);
	EXYNOS_DCS_WRITE_SEQ(ctx, 0xfc, 0x5a, 0x5a);

	/* DSC related configuration */
	exynos_dcs_compression_mode(ctx, 0x1);

	EXYNOS_PPS_LONG_WRITE(ctx);
	/* sleep out: 120ms delay */
	EXYNOS_DCS_WRITE_SEQ_DELAY(ctx, 120, 0x11);
	EXYNOS_DCS_WRITE_SEQ(ctx, 0xB9, 0x00, 0xB0, 0x8F, 0x09, 0x00, 0x00,
			0x00, 0x11, 0x01);
	EXYNOS_DCS_WRITE_SEQ(ctx, 0x1A, 0x1F, 0x00, 0x00, 0x00, 0x00);

	EXYNOS_DCS_WRITE_SEQ(ctx, 0x35); /* TE on */
	EXYNOS_DCS_WRITE_SEQ(ctx, 0xED, 0x44);

#if defined(CONFIG_EXYNOS_PLL_SLEEP)
	EXYNOS_DCS_WRITE_SEQ(ctx, 0xB9, 0x01, 0xB0, 0x91, 0x09);
#else
	EXYNOS_DCS_WRITE_SEQ(ctx, 0xB9, 0x00, 0xB0, 0x9C, 0x09);
#endif
	EXYNOS_DCS_WRITE_SEQ(ctx, 0xCE, 0x0D, 0x58, 0x14, 0x64, 0x38, 0xB8,
			0xF2, 0x03, 0x00, 0xFF, 0x02, 0x0A, 0x0A, 0x0A, 0x0A,
			0x0F, 0x23);

	EXYNOS_DCS_WRITE_SEQ(ctx, 0x53, 0x20); /* enable brightness control */
	EXYNOS_DCS_WRITE_SEQ(ctx, 0x51, 0x01, 0x80); /* brightness level */

	EXYNOS_DCS_WRITE_SEQ(ctx, 0x29); /* display on */

	ctx->enabled = true;

	dev_dbg(ctx->dev, "%s -\n", __func__);

	return 0;
}

static int s6e3hc2_set_brightness(struct exynos_panel *exynos_panel, u16 br)
{
	u16 brightness;

	brightness = (br & 0xff) << 8 | br >> 8;
	return exynos_dcs_set_brightness(exynos_panel, brightness);
}

static const struct exynos_display_mode s6e3hc2_wqhd_mode_private = {
	.mode_flags = MIPI_DSI_CLOCK_NON_CONTINUOUS,
	.dsc = {
		.enabled = true,
		.dsc_count = 2,
		.slice_count = 2,
		.slice_height = 40,
	},
};

static const struct drm_display_mode s6e3hc2_wqhd_mode = {
	.clock = 56125,	/* 898Mbps / 2 = 449Mhz / 8 = 56.125Mhz */
	.hdisplay = 1440,
	.hsync_start = 1440 + 2,
	.hsync_end = 1440 + 2 + 2,
	.htotal = 1440 + 2 + 2 + 2,
	.vdisplay = 3040,
	.vsync_start = 3040 + 8,
	.vsync_end = 3040 + 8 + 1,
	.vtotal = 3040 + 8 + 1 + 15,
	.vrefresh = 60,
	.flags = 0,
	.width_mm = 69,
	.height_mm = 142,
	.private = (int *) &s6e3hc2_wqhd_mode_private,
	.private_flags = EXYNOS_DISPLAY_MODE_FLAG_EXYNOS_PANEL,
};

static const struct exynos_display_mode s6e3hc2_fhd_mode_private = {
	.mode_flags = MIPI_DSI_CLOCK_NON_CONTINUOUS,
	.dsc = {
		.enabled = true,
		.dsc_count = 2,
		.slice_count = 2,
		.slice_height = 65,
	},
};

static const struct drm_display_mode s6e3hc2_fhd_mode = {
	.clock = 34375,	/* 550Mbps / 2 = 275Mhz / 8 = 34.375Mhz */
	.hdisplay = 1080,
	.hsync_start = 1080 + 32, // add hfp
	.hsync_end = 1080 + 32 + 12, // add hsa
	.htotal = 1080 + 32 + 12 + 16, // add hbp
	.vdisplay = 2340,
	.vsync_start = 2340 + 12, // add vfp
	.vsync_end = 2340 + 12 + 4, // add vsa
	.vtotal = 2340 + 12 + 4 + 16, // add vbp
	.vrefresh = 60,
	.flags = 0,
	.width_mm = 63,
	.height_mm = 137,
	.private = (int *) &s6e3hc2_fhd_mode_private,
	.private_flags = EXYNOS_DISPLAY_MODE_FLAG_EXYNOS_PANEL,
};

static const struct drm_panel_funcs s6e3hc2_drm_funcs = {
	.disable = s6e3hc2_disable,
	.unprepare = s6e3hc2_unprepare,
	.prepare = s6e3hc2_prepare,
	.enable = s6e3hc2_enable,
	.get_modes = exynos_panel_get_modes,
};

static const struct exynos_panel_funcs s6e3hc2_exynos_funcs = {
	.set_brightness = s6e3hc2_set_brightness,
};

const struct exynos_panel_desc samsung_s6e3hc2_wqhd = {
	.dsc_pps = SEQ_PPS_WQHD,
	.dsc_pps_len = ARRAY_SIZE(SEQ_PPS_WQHD),
	.data_lane_cnt = 4,
	.max_brightness = 1023,
	.dft_brightness = 511,
	/* supported HDR format bitmask : 1(DOLBY_VISION), 2(HDR10), 3(HLG) */
	.hdr_formats = BIT(2),
	.max_luminance = 5400000,
	.max_avg_luminance = 1200000,
	.min_luminance = 5,
	.mode = &s6e3hc2_wqhd_mode,
	.panel_func = &s6e3hc2_drm_funcs,
	.exynos_panel_func = &s6e3hc2_exynos_funcs,
};

const struct exynos_panel_desc samsung_s6e3hc2_fhd = {
	.dsc_pps = SEQ_PPS_FHD,
	.dsc_pps_len = ARRAY_SIZE(SEQ_PPS_FHD),
	.data_lane_cnt = 4,
	.max_brightness = 1023,
	.dft_brightness = 511,
	/* supported HDR format bitmask : 1(DOLBY_VISION), 2(HDR10), 3(HLG) */
	.hdr_formats = BIT(2),
	.max_luminance = 5400000,
	.max_avg_luminance = 1200000,
	.min_luminance = 5,
	.mode = &s6e3hc2_fhd_mode,
	.panel_func = &s6e3hc2_drm_funcs,
	.exynos_panel_func = &s6e3hc2_exynos_funcs,
};

static const struct of_device_id exynos_panel_of_match[] = {
	{ .compatible = "samsung,s6e3hc2", .data = &samsung_s6e3hc2_wqhd },
	{ .compatible = "samsung,s6e3hc2-fhd", .data = &samsung_s6e3hc2_fhd },
	{ }
};
MODULE_DEVICE_TABLE(of, exynos_panel_of_match);

static struct mipi_dsi_driver exynos_panel_driver = {
	.probe = exynos_panel_probe,
	.remove = exynos_panel_remove,
	.driver = {
		.name = "panel-samsung-s6e3hc2",
		.of_match_table = exynos_panel_of_match,
	},
};
module_mipi_dsi_driver(exynos_panel_driver);

MODULE_AUTHOR("Jiun Yu <jiun.yu@samsung.com>");
MODULE_DESCRIPTION("MIPI-DSI based Samsung s6e3hc2 panel driver");
MODULE_LICENSE("GPL");
