/*
 * Input/Output (IO) handle functions
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

#if !defined( _LIBVSHADOW_IO_HANDLE_H )
#define _LIBVSHADOW_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libvshadow_libbfio.h"
#include "libvshadow_libcdata.h"
#include "libvshadow_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint8_t vshadow_vss_identifier[ 16 ];

typedef struct libvshadow_io_handle libvshadow_io_handle_t;

struct libvshadow_io_handle
{
	/* The block size
	 */
	size_t block_size;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libvshadow_io_handle_initialize(
     libvshadow_io_handle_t **io_handle,
     libcerror_error_t **error );

int libvshadow_io_handle_free(
     libvshadow_io_handle_t **io_handle,
     libcerror_error_t **error );

int libvshadow_io_handle_clear(
     libvshadow_io_handle_t *io_handle,
     libcerror_error_t **error );

int libvshadow_io_handle_read_volume_header(
     libvshadow_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     off64_t *catalog_offset,
     libcerror_error_t **error );

int libvshadow_io_handle_read_volume_header_data(
     libvshadow_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     off64_t *catalog_offset,
     libcerror_error_t **error );

int libvshadow_io_handle_read_catalog(
     libvshadow_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     size64_t *volume_size,
     libcdata_array_t *store_descriptors_array,
     libcerror_error_t **error );

int libvshadow_io_handle_read_catalog_header_data(
     libvshadow_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     off64_t *next_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSHADOW_IO_HANDLE_H ) */

