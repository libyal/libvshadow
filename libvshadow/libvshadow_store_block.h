/*
 * Store block functions
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

#if !defined( _LIBVSHADOW_STORE_BLOCK_H )
#define _LIBVSHADOW_STORE_BLOCK_H

#include <common.h>
#include <types.h>

#include "libvshadow_libbfio.h"
#include "libvshadow_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvshadow_store_block libvshadow_store_block_t;

struct libvshadow_store_block
{
	/* The (block) data
	 */
	uint8_t *data;

	/* The (block) data size
	 */
	size_t data_size;

	/* The record type
	 */
	uint32_t record_type;

	/* The version
	 */
	uint32_t version;

	/* The relative offset
	 */
	off64_t relative_offset;

	/* The offset
	 */
	off64_t offset;

	/* The next offset
	 */
	off64_t next_offset;
};

int libvshadow_store_block_initialize(
     libvshadow_store_block_t **store_block,
     size_t block_size,
     libcerror_error_t **error );

int libvshadow_store_block_free(
     libvshadow_store_block_t **store_block,
     libcerror_error_t **error );

int libvshadow_store_block_read(
     libvshadow_store_block_t *store_block,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libvshadow_store_block_read_header_data(
     libvshadow_store_block_t *store_block,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSHADOW_STORE_BLOCK_H ) */

