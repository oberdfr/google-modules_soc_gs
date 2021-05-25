// SPDX-License-Identifier: GPL-2.0 only
/*
 *  Emerald Hill compression engine driver
 *
 *  Copyright (C) 2020 Google LLC
 *  Author: Petri Gynther <pgynther@google.com>
 *
 *  Derived from:
 *  Hardware Compressed RAM offload driver
 *  Copyright (C) 2015 The Chromium OS Authors
 *  Author: Sonny Rao <sonnyrao@chromium.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _EH_H_
#define _EH_H_

#include <linux/types.h>
#include <linux/mm_types.h>

struct eh_device;

/* These are the possible values for the status field from the specification */
enum eh_cdesc_status {
	/* descriptor not in use */
	EH_CDESC_IDLE = 0x0,

	/* descriptor completed with compressed bytes written to target */
	EH_CDESC_COMPRESSED = 0x1,

	/*
	 * descriptor completed, incompressible page, uncompressed bytes written
	 * to target
	 */
	EH_CDESC_COPIED = 0x2,

	/* descriptor completed, incompressible page, nothing written to target
	 */
	EH_CDESC_ABORT = 0x3,

	/* descriptor completed, page was all zero, nothing written to target */
	EH_CDESC_ZERO = 0x4,

	/*
	 * descriptor count not be completed dut to an error.
	 * queue operation continued to next descriptor
	 */
	EH_CDESC_ERROR_CONTINUE = 0x5,

	/*
	 * descriptor count not be completed dut to an error.
	 * queue operation halted
	 */
	EH_CDESC_ERROR_HALTED = 0x6,

	/* descriptor in queue or being processed by hardware */
	EH_CDESC_PENDING = 0x7,
};

typedef void (*eh_cb_fn)(unsigned int status, void *data, unsigned int size,
			 void *priv);

/* tear down hardware block, mostly done when eh_device is unloaded */
void eh_remove(struct eh_device *eh_dev);

/*
 * start a compression, returns non-zero if fifo is full
 *
 * the completion argument includes a callback which is called when
 * the compression is completed and returns the size, status, and
 * the memory used to store the compressed data.
 */
int eh_compress_page(struct eh_device *eh_dev, struct page *page, void *priv);
int eh_decompress_page(struct eh_device *eh_dev, void *src,
                       unsigned int slen, struct page *page);

/* create eh_device for user */
struct eh_device *eh_create(eh_cb_fn comp);

/* destroty eh_device */
void eh_destroy(struct eh_device *eh_dev);

#endif /* _EH_H_ */
