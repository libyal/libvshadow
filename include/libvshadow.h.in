/*
 * Library to access the Windows NT Volume Shadow Snapshot (VSS) format
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

#if !defined( _LIBVSHADOW_H )
#define _LIBVSHADOW_H

#include <libvshadow/codepage.h>
#include <libvshadow/definitions.h>
#include <libvshadow/error.h>
#include <libvshadow/extern.h>
#include <libvshadow/features.h>
#include <libvshadow/types.h>

#include <stdio.h>

#if defined( LIBVSHADOW_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBVSHADOW_EXTERN \
const char *libvshadow_get_version(
             void );

/* Returns the access flags for reading
 */
LIBVSHADOW_EXTERN \
int libvshadow_get_access_flags_read(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_get_codepage(
     int *codepage,
     libvshadow_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_set_codepage(
     int codepage,
     libvshadow_error_t **error );

/* Determines if a file contains a VSS volume signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_check_volume_signature(
     const char *filename,
     libvshadow_error_t **error );

#if defined( LIBVSHADOW_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains a VSS volume signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_check_volume_signature_wide(
     const wchar_t *filename,
     libvshadow_error_t **error );

#endif /* defined( LIBVSHADOW_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVSHADOW_HAVE_BFIO )

/* Determines if a file contains a VSS volume signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libvshadow_error_t **error );

#endif /* defined( LIBVSHADOW_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBVSHADOW_EXTERN \
void libvshadow_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_notify_set_stream(
     FILE *stream,
     libvshadow_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_notify_stream_open(
     const char *filename,
     libvshadow_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_notify_stream_close(
     libvshadow_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBVSHADOW_EXTERN \
void libvshadow_error_free(
      libvshadow_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_error_fprint(
     libvshadow_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_error_sprint(
     libvshadow_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_error_backtrace_fprint(
     libvshadow_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_error_backtrace_sprint(
     libvshadow_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * Volume functions
 * ------------------------------------------------------------------------- */

/* Creates the volume
 * Make sure the value volume is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_volume_initialize(
     libvshadow_volume_t **volume,
     libvshadow_error_t **error );

/* Frees a volume
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_volume_free(
     libvshadow_volume_t **volume,
     libvshadow_error_t **error );

/* Signals the volume to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_volume_signal_abort(
     libvshadow_volume_t *volume,
     libvshadow_error_t **error );

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_volume_open(
     libvshadow_volume_t *volume,
     const char *filename,
     int access_flags,
     libvshadow_error_t **error );

#if defined( LIBVSHADOW_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_volume_open_wide(
     libvshadow_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libvshadow_error_t **error );

#endif /* defined( LIBVSHADOW_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVSHADOW_HAVE_BFIO )

/* Opens a volume using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_volume_open_file_io_handle(
     libvshadow_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvshadow_error_t **error );

#endif /* defined( LIBVSHADOW_HAVE_BFIO ) */

/* Closes a volume
 * Returns 0 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_volume_close(
     libvshadow_volume_t *volume,
     libvshadow_error_t **error );

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_volume_get_size(
     libvshadow_volume_t *volume,
     size64_t *size,
     libvshadow_error_t **error );

/* Retrieves the number of stores
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_volume_get_number_of_stores(
     libvshadow_volume_t *volume,
     int *number_of_stores,
     libvshadow_error_t **error );

/* Retrieves a specific store
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_volume_get_store(
     libvshadow_volume_t *volume,
     int store_index,
     libvshadow_store_t **store,
     libvshadow_error_t **error );

/* Retrieves a specific store identifier
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_volume_get_store_identifier(
     libvshadow_volume_t *volume,
     int store_index,
     uint8_t *guid,
     size_t size,
     libvshadow_error_t **error );

/* -------------------------------------------------------------------------
 * Store functions
 * ------------------------------------------------------------------------- */

/* Frees a store
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_store_free(
     libvshadow_store_t **store,
     libvshadow_error_t **error );

/* Determines if the store has in-volume data
 * Returns 1 if the store has in-volume data, 0 if not or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_store_has_in_volume_data(
     libvshadow_store_t *store,
     libvshadow_error_t **error );

/* Reads (store) data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
LIBVSHADOW_EXTERN \
ssize_t libvshadow_store_read_buffer(
         libvshadow_store_t *store,
         void *buffer,
         size_t buffer_size,
         libvshadow_error_t **error );

#if defined( LIBVSHADOW_HAVE_BFIO )

/* Opens a volume using a Basic File IO (bfio) handle using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
ssize_t libvshadow_store_read_buffer_from_file_io_handle(
         libvshadow_store_t *store,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libvshadow_error_t **error );

#endif /* defined( LIBVSHADOW_HAVE_BFIO ) */

/* Reads (store) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
LIBVSHADOW_EXTERN \
ssize_t libvshadow_store_read_buffer_at_offset(
         libvshadow_store_t *store,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libvshadow_error_t **error );

/* Seeks a certain offset of the (store) data
 * Returns the offset if seek is successful or -1 on error
 */
LIBVSHADOW_EXTERN \
off64_t libvshadow_store_seek_offset(
         libvshadow_store_t *store,
         off64_t offset,
         int whence,
         libvshadow_error_t **error );

/* Retrieves the the current offset of the (store) data
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_store_get_offset(
     libvshadow_store_t *store,
     off64_t *offset,
     libvshadow_error_t **error );

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_store_get_size(
     libvshadow_store_t *store,
     size64_t *size,
     libvshadow_error_t **error );

/* Retrieves the volume size as stored in the store information
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_store_get_volume_size(
     libvshadow_store_t *store,
     size64_t *volume_size,
     libvshadow_error_t **error );

/* Retrieves the identifier
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_store_get_identifier(
     libvshadow_store_t *store,
     uint8_t *guid,
     size_t size,
     libvshadow_error_t **error );

/* Retrieves the creation date and time
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_store_get_creation_time(
     libvshadow_store_t *store,
     uint64_t *filetime,
     libvshadow_error_t **error );

/* Retrieves the copy identifier
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_store_get_copy_identifier(
     libvshadow_store_t *store,
     uint8_t *guid,
     size_t size,
     libvshadow_error_t **error );

/* Retrieves the copy set identifier
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_store_get_copy_set_identifier(
     libvshadow_store_t *store,
     uint8_t *guid,
     size_t size,
     libvshadow_error_t **error );

/* Retrieves the attribute flags
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_store_get_attribute_flags(
     libvshadow_store_t *store,
     uint32_t *attribute_flags,
     libvshadow_error_t **error );

/* Retrieves the number of blocks
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_store_get_number_of_blocks(
     libvshadow_store_t *store,
     int *number_of_blocks,
     libvshadow_error_t **error );

/* Retrieves a specific block
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_store_get_block_by_index(
     libvshadow_store_t *store,
     int block_index,
     libvshadow_block_t **block,
     libvshadow_error_t **error );

/* -------------------------------------------------------------------------
 * Block functions
 * ------------------------------------------------------------------------- */

/* Frees a block
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_block_free(
     libvshadow_block_t **block,
     libvshadow_error_t **error );

/* Retrieves the original offset
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_block_get_original_offset(
     libvshadow_block_t *block,
     off64_t *original_offset,
     libvshadow_error_t **error );

/* Retrieves the relative offset
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_block_get_relative_offset(
     libvshadow_block_t *block,
     off64_t *relative_offset,
     libvshadow_error_t **error );

/* Retrieves the offset
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_block_get_offset(
     libvshadow_block_t *block,
     off64_t *offset,
     libvshadow_error_t **error );

/* Retrieves the block values
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_block_get_values(
     libvshadow_block_t *block,
     off64_t *original_offset,
     off64_t *relative_offset,
     off64_t *offset,
     uint32_t *flags,
     uint32_t *bitmap,
     libvshadow_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSHADOW_H ) */

