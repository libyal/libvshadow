/*
 * Store functions
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

#if !defined( _LIBVSHADOW_INTERNAL_STORE_H )
#define _LIBVSHADOW_INTERNAL_STORE_H

#include <common.h>
#include <types.h>

#include "libvshadow_extern.h"
#include "libvshadow_libbfio.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_libcthreads.h"
#include "libvshadow_store_descriptor.h"
#include "libvshadow_types.h"
#include "libvshadow_volume.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvshadow_internal_store libvshadow_internal_store_t;

struct libvshadow_internal_store
{
	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The IO handle
	 */
	libvshadow_io_handle_t *io_handle;

	/* The internal volume
	 */
	libvshadow_internal_volume_t *internal_volume;

	/* The store descriptor index
	 */
	int store_descriptor_index;

	/* The store descriptor
	 */
	libvshadow_store_descriptor_t *store_descriptor;

	/* The current offset
	 */
	off64_t current_offset;

#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

int libvshadow_store_initialize(
     libvshadow_store_t **store,
     libbfio_handle_t *file_io_handle,
     libvshadow_io_handle_t *io_handle,
     libvshadow_internal_volume_t *internal_volume,
     int store_descriptor_index,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_store_free(
     libvshadow_store_t **store,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_store_has_in_volume_data(
     libvshadow_store_t *store,
     libcerror_error_t **error );

ssize_t libvshadow_internal_store_read_buffer_from_file_io_handle(
         libvshadow_internal_store_t *internal_store,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVSHADOW_EXTERN \
ssize_t libvshadow_store_read_buffer(
         libvshadow_store_t *store,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVSHADOW_EXTERN \
ssize_t libvshadow_store_read_buffer_from_file_io_handle(
         libvshadow_store_t *store,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVSHADOW_EXTERN \
ssize_t libvshadow_store_read_buffer_at_offset(
         libvshadow_store_t *store,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

off64_t libvshadow_internal_store_seek_offset(
         libvshadow_internal_store_t *internal_store,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBVSHADOW_EXTERN \
off64_t libvshadow_store_seek_offset(
         libvshadow_store_t *store,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_store_get_offset(
     libvshadow_store_t *store,
     off64_t *offset,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_store_get_size(
     libvshadow_store_t *store,
     size64_t *size,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_store_get_volume_size(
     libvshadow_store_t *store,
     size64_t *volume_size,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_store_get_identifier(
     libvshadow_store_t *store,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_store_get_creation_time(
     libvshadow_store_t *store,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_store_get_copy_identifier(
     libvshadow_store_t *store,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_store_get_copy_set_identifier(
     libvshadow_store_t *store,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_store_get_attribute_flags(
     libvshadow_store_t *store,
     uint32_t *attribute_flags,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_store_get_number_of_blocks(
     libvshadow_store_t *store,
     int *number_of_blocks,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_store_get_block_by_index(
     libvshadow_store_t *store,
     int block_index,
     libvshadow_block_t **block,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSHADOW_INTERNAL_STORE_H ) */

