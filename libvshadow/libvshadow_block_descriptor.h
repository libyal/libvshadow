/*
 * Block descriptor functions
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

#if !defined( _LIBVSHADOW_BLOCK_DESCRIPTOR_H )
#define _LIBVSHADOW_BLOCK_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libvshadow_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvshadow_block_descriptor libvshadow_block_descriptor_t;

struct libvshadow_block_descriptor
{
	/* The original (volume) offset
	 */
	off64_t original_offset;

	/* The (block) offset
	 */
	off64_t offset;

	/* The relative (block) offset
	 */
	off64_t relative_offset;

	/* The (block) flags
	 */
	uint32_t flags;

	/* The (allocation) bitmap
	 */
	uint32_t bitmap;

	/* The block index
	 */
	int index;

	/* The reverse block index
	 */
	int reverse_index;

	/* The overlay block descriptor
	 */
	libvshadow_block_descriptor_t *overlay;
};

int libvshadow_block_descriptor_initialize(
     libvshadow_block_descriptor_t **block_descriptor,
     libcerror_error_t **error );

int libvshadow_block_descriptor_free(
     libvshadow_block_descriptor_t **block_descriptor,
     libcerror_error_t **error );

int libvshadow_block_descriptor_free_reverse(
     libvshadow_block_descriptor_t **block_descriptor,
     libcerror_error_t **error );

int libvshadow_block_descriptor_clone(
     libvshadow_block_descriptor_t **destination_block_descriptor,
     libvshadow_block_descriptor_t *source_block_descriptor,
     libcerror_error_t **error );

int libvshadow_block_descriptor_read_data(
     libvshadow_block_descriptor_t *block_descriptor,
     const uint8_t *data,
     size_t data_size,
     int store_index,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSHADOW_BLOCK_DESCRIPTOR_H ) */

