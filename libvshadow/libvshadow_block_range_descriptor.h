/*
 * Block range descriptor functions
 *
 * Copyright (C) 2011-2020, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBVSHADOW_BLOCK_RANGE_DESCRIPTOR_H )
#define _LIBVSHADOW_BLOCK_RANGE_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libvshadow_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvshadow_block_range_descriptor libvshadow_block_range_descriptor_t;

struct libvshadow_block_range_descriptor
{
	/* The (block range) offset
	 */
	off64_t offset;

	/* The relative (block range) offset
	 */
	off64_t relative_offset;

	/* The (block range) size
	 */
	size64_t size;
};

int libvshadow_block_range_descriptor_initialize(
     libvshadow_block_range_descriptor_t **block_range_descriptor,
     libcerror_error_t **error );

int libvshadow_block_range_descriptor_free(
     libvshadow_block_range_descriptor_t **block_range_descriptor,
     libcerror_error_t **error );

int libvshadow_block_range_descriptor_read_data(
     libvshadow_block_range_descriptor_t *block_range_descriptor,
     const uint8_t *data,
     size_t data_size,
     int store_index,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSHADOW_BLOCK_RANGE_DESCRIPTOR_H ) */

