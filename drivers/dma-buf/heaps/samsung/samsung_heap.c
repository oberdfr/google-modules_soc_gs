// SPDX-License-Identifier: GPL-2.0
/*
 * DMABUF Heap Allocator - Common implementation
 *
 * Copyright (C) 2021 Samsung Electronics Co., Ltd.
 * Author: <hyesoo.yu@samsung.com> for Samsung
 */

#include <linux/dma-buf.h>
#include <linux/dma-heap.h>
#include <linux/err.h>
#include <linux/highmem.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/scatterlist.h>
#include <linux/slab.h>
#include <linux/of.h>

#include "heap_private.h"

void heap_cache_flush(struct samsung_dma_buffer *buffer)
{
	struct device *dev = dma_heap_get_dev(buffer->heap->dma_heap);

	if (!dma_heap_skip_cache_ops(buffer->flags))
		return;
	/*
	 * Flushing caches on buffer allocation is intended for preventing
	 * corruption from writing back to DRAM from the dirty cache lines
	 * while updating the buffer from DMA. However, cache flush should be
	 * performed on the entire allocated area if the buffer is to be
	 * protected from non-secure access to prevent the dirty write-back
	 * to the protected area.
	 */
	dma_map_sgtable(dev, &buffer->sg_table, DMA_TO_DEVICE, 0);
	dma_unmap_sgtable(dev, &buffer->sg_table, DMA_FROM_DEVICE, 0);
}

/*
 * It should be called by physically contiguous buffer.
 */
void heap_page_clean(struct page *pages, unsigned long size)
{
	unsigned long nr_pages, i;

	if (!PageHighMem(pages)) {
		memset(page_address(pages), 0, size);
		return;
	}

	nr_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;

	for (i = 0; i < nr_pages; i++) {
		void *vaddr = kmap_atomic(&pages[i]);

		memset(vaddr, 0, PAGE_SIZE);
		kunmap_atomic(vaddr);
	}
}

struct samsung_dma_buffer *samsung_dma_buffer_alloc(struct samsung_dma_heap *samsung_dma_heap,
						    unsigned long size, unsigned int nents)
{
	struct samsung_dma_buffer *buffer;

	buffer = kzalloc(sizeof(*buffer), GFP_KERNEL);
	if (!buffer)
		return ERR_PTR(-ENOMEM);

	if (sg_alloc_table(&buffer->sg_table, nents, GFP_KERNEL)) {
		kfree(buffer);
		return ERR_PTR(-ENOMEM);
	}

	INIT_LIST_HEAD(&buffer->attachments);
	mutex_init(&buffer->lock);
	buffer->heap = samsung_dma_heap;
	buffer->len = size;
	buffer->flags = samsung_dma_heap->flags;

	return buffer;
}

void samsung_dma_buffer_free(struct samsung_dma_buffer *buffer)
{
	sg_free_table(&buffer->sg_table);
	kfree(buffer);
}

static const char *samsung_add_heap_name(unsigned long flags)
{
	if (dma_heap_flags_uncached(flags))
		return "-uncached";

	if (dma_heap_flags_protected(flags))
		return "-secure";

	return "";
}

static struct samsung_dma_heap *__samsung_heap_add(struct device *dev, void *priv,
						   void (*release)(struct samsung_dma_buffer *),
						   const struct dma_heap_ops *ops,
						   unsigned int flags)
{
	struct samsung_dma_heap *heap;
	unsigned int alignment = PAGE_SIZE, order, protid = 0;
	struct dma_heap_export_info exp_info;
	const char *name;
	char *heap_name;

	if (dma_heap_flags_protected(flags)) {
		of_property_read_u32(dev->of_node, "dma-heap,protection_id", &protid);
		if (!protid) {
			perrfn("Secure heap should be set with protection id");
			return ERR_PTR(-EINVAL);
		}

		if (!IS_ENABLED(CONFIG_EXYNOS_CONTENT_PATH_PROTECTION))
			return ERR_PTR(-ENODEV);
	}

	if (of_property_read_string(dev->of_node, "dma-heap,name", &name)) {
		perrfn("The heap should define name on device node");
		return ERR_PTR(-EINVAL);
	}

	of_property_read_u32(dev->of_node, "dma-heap,alignment", &alignment);
	order = min_t(unsigned int, get_order(alignment), MAX_ORDER);

	heap = devm_kzalloc(dev, sizeof(*heap), GFP_KERNEL);
	if (!heap)
		return ERR_PTR(-ENOMEM);
	heap->flags = flags;

	heap_name = devm_kasprintf(dev, GFP_KERNEL, "%s%s", name, samsung_add_heap_name(flags));
	if (!heap_name)
		return ERR_PTR(-ENOMEM);

	heap->protection_id = protid;
	heap->alignment = 1 << (order + PAGE_SHIFT);
	heap->release = release;
	heap->priv = priv;
	heap->name = heap_name;

	exp_info.name = heap_name;
	exp_info.ops = ops;
	exp_info.priv = heap;

	heap->dma_heap = dma_heap_add(&exp_info);
	if (IS_ERR(heap->dma_heap))
		return heap;

	pr_info("Registered %s dma-heap successfully\n", heap_name);

	dma_coerce_mask_and_coherent(dma_heap_get_dev(heap->dma_heap), DMA_BIT_MASK(36));

	return heap;
}

static const unsigned int nonsecure_heap_type[] = {
	0,
	DMA_HEAP_FLAG_UNCACHED,
};

#define num_nonsecure_heaps ARRAY_SIZE(nonsecure_heap_type)

static const unsigned int secure_heap_type[] = {
	DMA_HEAP_FLAG_PROTECTED,
};

#define num_secure_heaps ARRAY_SIZE(secure_heap_type)

/*
 * Maximum heap types is defined by cachable heap types
 * because prot heap type is always only 1.
 */
#define num_max_heaps (num_nonsecure_heaps)

/*
 * NOTE: samsung_heap_create returns error when heap creation fails.
 * In case of -ENODEV, it means that the secure heap doesn't need to be added
 * if system doesn't support content protection.
 */
int samsung_heap_add(struct device *dev, void *priv,
		     void (*release)(struct samsung_dma_buffer *buffer),
		     const struct dma_heap_ops *ops)
{
	struct samsung_dma_heap *heap[num_max_heaps];
	const unsigned int *types;
	int i, ret, count;

	/*
	 * Secure heap should allocate only secure buffer.
	 * Normal cachable heap and uncachable heaps are not registered.
	 */
	if (of_property_read_bool(dev->of_node, "dma-heap,secure")) {
		count = num_secure_heaps;
		types = secure_heap_type;
	} else {
		count = num_nonsecure_heaps;
		types = nonsecure_heap_type;
	}

	for (i = 0; i < count; i++) {
		heap[i] = __samsung_heap_add(dev, priv, release, ops, types[i]);
		if (IS_ERR(heap[i])) {
			ret = PTR_ERR(heap[i]);
			goto heap_put;
		}
	}

	return 0;
heap_put:
	while (i-- > 0)
		dma_heap_put(heap[i]->dma_heap);

	return ret;
}

struct dma_buf *samsung_export_dmabuf(struct samsung_dma_buffer *buffer, unsigned long fd_flags)
{
	DEFINE_SAMSUNG_DMA_BUF_EXPORT_INFO(exp_info, buffer->heap->name);

	exp_info.ops = &samsung_dma_buf_ops;
	exp_info.size = buffer->len;
	exp_info.flags = fd_flags;
	exp_info.priv = buffer;

	return dma_buf_export(&exp_info);
}

static int __init samsung_dma_heap_init(void)
{
	int ret;

	ret = secure_iova_pool_create();
	if (ret)
		return ret;

	ret = cma_dma_heap_init();
	if (ret)
		goto err_cma;

	ret = carveout_dma_heap_init();
	if (ret)
		goto err_carveout;

	ret = system_dma_heap_init();
	if (ret)
		goto err_system;

	return 0;
err_system:
	carveout_dma_heap_exit();
err_carveout:
	cma_dma_heap_exit();
err_cma:
	secure_iova_pool_destroy();

	return ret;
}

static void __exit samsung_dma_heap_exit(void)
{
	system_dma_heap_exit();
	carveout_dma_heap_exit();
	cma_dma_heap_exit();

	secure_iova_pool_destroy();
}

module_init(samsung_dma_heap_init);
module_exit(samsung_dma_heap_exit);
MODULE_DESCRIPTION("DMA-BUF Samsung Heap");
MODULE_LICENSE("GPL v2");