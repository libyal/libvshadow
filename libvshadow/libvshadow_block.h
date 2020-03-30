/*
 * Block functions
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

#if !defined( _LIBVSHADOW_INTERNAL_BLOCK_H )
#define _LIBVSHADOW_INTERNAL_BLOCK_H

#include <common.h>
#include <types.h>

#include "libvshadow_block_descriptor.h"
#include "libvshadow_extern.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvshadow_internal_block libvshadow_internal_block_t;

struct libvshadow_internal_block
{
	/* The block descriptor
	 */
	libvshadow_block_descriptor_t *block_descriptor;
};

int libvshadow_block_initialize(
     libvshadow_block_t **block,
     libvshadow_block_descriptor_t *block_descriptor,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_block_free(
     libvshadow_block_t **block,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_block_get_original_offset(
     libvshadow_block_t *block,
     off64_t *original_offset,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_block_get_relative_offset(
     libvshadow_block_t *block,
     off64_t *relative_offset,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_block_get_offset(
     libvshadow_block_t *block,
     off64_t *offset,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_block_get_values(
     libvshadow_block_t *block,
     off64_t *original_offset,
     off64_t *relative_offset,
     off64_t *offset,
     uint32_t *flags,
     uint32_t *bitmap,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSHADOW_INTERNAL_BLOCK_H ) */

