/*
 * Volume functions
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

#if !defined( _LIBVSHADOW_INTERNAL_VOLUME_H )
#define _LIBVSHADOW_INTERNAL_VOLUME_H

#include <common.h>
#include <types.h>

#include "libvshadow_extern.h"
#include "libvshadow_io_handle.h"
#include "libvshadow_libbfio.h"
#include "libvshadow_libcdata.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_libcthreads.h"
#include "libvshadow_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvshadow_internal_volume libvshadow_internal_volume_t;

struct libvshadow_internal_volume
{
	/* The (volume) size
	 */
	size64_t size;

	/* The store descriptors array
	 */
	libcdata_array_t *store_descriptors_array;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The IO handle
	 */
	libvshadow_io_handle_t *io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

LIBVSHADOW_EXTERN \
int libvshadow_volume_initialize(
     libvshadow_volume_t **volume,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_volume_free(
     libvshadow_volume_t **volume,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_volume_signal_abort(
     libvshadow_volume_t *volume,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_volume_open(
     libvshadow_volume_t *volume,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBVSHADOW_EXTERN \
int libvshadow_volume_open_wide(
     libvshadow_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBVSHADOW_EXTERN \
int libvshadow_volume_open_file_io_handle(
     libvshadow_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_volume_close(
     libvshadow_volume_t *volume,
     libcerror_error_t **error );

int libvshadow_volume_open_read(
     libvshadow_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libvshadow_volume_open_read_ntfs_volume_headers(
     libvshadow_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_volume_get_size(
     libvshadow_volume_t *volume,
     size64_t *size,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_volume_get_number_of_stores(
     libvshadow_volume_t *volume,
     int *number_of_stores,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_volume_get_store(
     libvshadow_volume_t *volume,
     int store_index,
     libvshadow_store_t **store,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_volume_get_store_identifier(
     libvshadow_volume_t *volume,
     int store_index,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSHADOW_INTERNAL_VOLUME_H ) */

