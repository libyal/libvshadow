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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libvshadow_block.h"
#include "libvshadow_block_descriptor.h"
#include "libvshadow_block_tree.h"
#include "libvshadow_definitions.h"
#include "libvshadow_libbfio.h"
#include "libvshadow_libcdata.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_libcthreads.h"
#include "libvshadow_store.h"
#include "libvshadow_store_descriptor.h"
#include "libvshadow_volume.h"

/* Creates a store
 * Make sure the value store is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvshadow_store_initialize(
     libvshadow_store_t **store,
     libbfio_handle_t *file_io_handle,
     libvshadow_io_handle_t *io_handle,
     libvshadow_internal_volume_t *internal_volume,
     int store_descriptor_index,
     libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store     = NULL;
	libvshadow_store_descriptor_t *store_descriptor = NULL;
	static char *function                           = "libvshadow_store_initialize";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	if( *store != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid store value already set.",
		 function );

		return( -1 );
	}
	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	/* Make sure there is a store descriptor for the store
	 */
	if( libcdata_array_get_entry_by_index(
	     internal_volume->store_descriptors_array,
	     store_descriptor_index,
	     (intptr_t **) &store_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve store descriptor: %d.",
		 function,
		 store_descriptor_index );

		return( -1 );
	}
	internal_store = memory_allocate_structure(
	                  libvshadow_internal_store_t );

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create store.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_store,
	     0,
	     sizeof( libvshadow_internal_store_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear store.",
		 function );

		memory_free(
		 internal_store );

		return( -1 );
	}
#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_initialize(
	     &( internal_store->read_write_lock ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize read/write lock.",
		 function );

		goto on_error;
	}
#endif
	internal_store->file_io_handle         = file_io_handle;
	internal_store->io_handle              = io_handle;
	internal_store->internal_volume        = internal_volume;
	internal_store->store_descriptor       = store_descriptor;
	internal_store->store_descriptor_index = store_descriptor_index;

	*store = (libvshadow_store_t *) internal_store;

	return( 1 );

on_error:
	if( internal_store != NULL )
	{
		memory_free(
		 internal_store );
	}
	return( -1 );
}

/* Frees a store
 * Returns 1 if successful or -1 on error
 */
int libvshadow_store_free(
     libvshadow_store_t **store,
     libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_free";
	int result                                  = 1;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	if( *store != NULL )
	{
		internal_store = (libvshadow_internal_store_t *) *store;
		*store         = NULL;

		/* The file_io_handle, io_handle and internal_volume references are freed elsewhere
		 */
#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_free(
		     &( internal_store->read_write_lock ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free read/write lock.",
			 function );

			result = -1;
		}
#endif
		memory_free(
		 internal_store );
	}
	return( result );
}

/* Determines if the store has in-volume data
 * Returns 1 if the store has in-volume data, 0 if not or -1 on error
 */
int libvshadow_store_has_in_volume_data(
     libvshadow_store_t *store,
     libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_has_in_volume_data";
	int result                                  = 0;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

	if( internal_store->internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing internal volume.",
		 function );

		return( -1 );
	}
	result = libvshadow_store_descriptor_has_in_volume_data(
	          internal_store->store_descriptor,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if store descriptor: %d has in-volume data.",
		 function,
		 internal_store->store_descriptor_index );

		return( -1 );
	}
	return( result );
}

/* Reads (store) data at the current offset into a buffer using a Basic File IO (bfio) handle
 * This function is not multi-thread safe acquire write lock before call
 * Returns the number of bytes read or -1 on error
 */
ssize_t libvshadow_internal_store_read_buffer_from_file_io_handle(
         libvshadow_internal_store_t *internal_store,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	static char *function = "libvshadow_internal_store_read_buffer_from_file_io_handle";
	ssize_t read_count    = 0;

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	if( internal_store->internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing internal volume.",
		 function );

		return( -1 );
	}
	if( internal_store->current_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid store - current offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( buffer_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid element data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( buffer_size == 0 )
	 || ( (size64_t) internal_store->current_offset >= internal_store->internal_volume->size ) )
	{
		return( 0 );
	}
	if( (size64_t) buffer_size > ( internal_store->internal_volume->size - internal_store->current_offset ) )
	{
		buffer_size = (size_t) ( internal_store->internal_volume->size - internal_store->current_offset );
	}
	read_count = libvshadow_store_descriptor_read_buffer(
		      internal_store->store_descriptor,
		      file_io_handle,
		      (uint8_t *) buffer,
		      buffer_size,
		      internal_store->current_offset,
		      internal_store->store_descriptor_index,
		      error );

	if( read_count != (ssize_t) buffer_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer from store descriptor: %d.",
		 function,
		 internal_store->store_descriptor_index );

		return( -1 );
	}
	internal_store->current_offset += read_count;

	return( read_count );
}

/* Reads (store) data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libvshadow_store_read_buffer(
         libvshadow_store_t *store,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_read_buffer";
	ssize_t read_count                          = 0;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_store->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	read_count = libvshadow_internal_store_read_buffer_from_file_io_handle(
		      internal_store,
		      internal_store->file_io_handle,
		      buffer,
		      buffer_size,
		      error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		read_count = -1;
	}
#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_store->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );
}

/* Reads (store) data at the current offset into a buffer using a Basic File IO (bfio) handle
 * Returns the number of bytes read or -1 on error
 */
ssize_t libvshadow_store_read_buffer_from_file_io_handle(
         libvshadow_store_t *store,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_read_buffer_from_file_io_handle";
	ssize_t read_count                          = 0;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_store->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	read_count = libvshadow_internal_store_read_buffer_from_file_io_handle(
		      internal_store,
		      file_io_handle,
		      buffer,
		      buffer_size,
		      error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		read_count = -1;
	}
#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_store->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );
}

/* Reads (store) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
ssize_t libvshadow_store_read_buffer_at_offset(
         libvshadow_store_t *store,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_read_buffer_at_offset";
	ssize_t read_count                          = 0;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_store->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libvshadow_internal_store_seek_offset(
	     internal_store,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		read_count = -1;
	}
	else
	{
		read_count = libvshadow_internal_store_read_buffer_from_file_io_handle(
			      internal_store,
			      internal_store->file_io_handle,
			      buffer,
			      buffer_size,
			      error );

		if( read_count == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read buffer.",
			 function );

			read_count = -1;
		}
	}
#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_store->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );
}

/* Seeks a certain offset of the (store) data
 * This function is not multi-thread safe acquire write lock before call
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libvshadow_internal_store_seek_offset(
         libvshadow_internal_store_t *internal_store,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	static char *function = "libvshadow_internal_store_seek_offset";

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	if( internal_store->internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing internal volume.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	if( whence == SEEK_CUR )
	{
		offset += internal_store->current_offset;
	}
	else if( whence == SEEK_END )
	{
		offset += (off64_t) internal_store->internal_volume->size;
	}
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid offset value out of bounds.",
		 function );

		return( -1 );
	}
	internal_store->current_offset = offset;

	return( offset );
}

/* Seeks a certain offset of the (store) data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libvshadow_store_seek_offset(
         libvshadow_store_t *store,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_seek_offset";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_store->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	offset = libvshadow_internal_store_seek_offset(
	          internal_store,
	          offset,
	          whence,
	          error );

	if( offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		offset = -1;
	}
#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_store->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( offset );
}

/* Retrieves the current offset of the (store) data
 * Returns 1 if successful or -1 on error
 */
int libvshadow_store_get_offset(
     libvshadow_store_t *store,
     off64_t *offset,
     libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_get_offset";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_store->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*offset = internal_store->current_offset;

#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_store->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libvshadow_store_get_size(
     libvshadow_store_t *store,
     size64_t *size,
     libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_get_size";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

	if( libvshadow_volume_get_size(
	     (libvshadow_volume_t *) internal_store->internal_volume,
	     size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size from volume.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the volume size as stored in the store information
 * Returns 1 if successful or -1 on error
 */
int libvshadow_store_get_volume_size(
     libvshadow_store_t *store,
     size64_t *volume_size,
     libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_get_volume_size";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

	if( internal_store->internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing internal volume.",
		 function );

		return( -1 );
	}
	if( libvshadow_store_descriptor_get_volume_size(
	     internal_store->store_descriptor,
	     volume_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve volume size from store descriptor: %d.",
		 function,
		 internal_store->store_descriptor_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the identifier
 * Returns 1 if successful or -1 on error
 */
int libvshadow_store_get_identifier(
     libvshadow_store_t *store,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_get_identifier";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

	if( internal_store->internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing internal volume.",
		 function );

		return( -1 );
	}
	if( libvshadow_store_descriptor_get_identifier(
	     internal_store->store_descriptor,
	     guid,
	     size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve identifier from store descriptor: %d.",
		 function,
		 internal_store->store_descriptor_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the creation date and time
 * Returns 1 if successful or -1 on error
 */
int libvshadow_store_get_creation_time(
     libvshadow_store_t *store,
     uint64_t *filetime,
     libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_get_creation_time";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

	if( internal_store->internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing internal volume.",
		 function );

		return( -1 );
	}
	if( libvshadow_store_descriptor_get_creation_time(
	     internal_store->store_descriptor,
	     filetime,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve creation time from store descriptor: %d.",
		 function,
		 internal_store->store_descriptor_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the copy identifier
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvshadow_store_get_copy_identifier(
     libvshadow_store_t *store,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_get_copy_identifier";
	int result                                  = 0;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

	if( internal_store->internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing internal volume.",
		 function );

		return( -1 );
	}
	result = libvshadow_store_descriptor_get_copy_identifier(
	          internal_store->store_descriptor,
	          guid,
	          size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve copy identifier from store descriptor: %d.",
		 function,
		 internal_store->store_descriptor_index );

		return( -1 );
	}
	return( result );
}

/* Retrieves the copy set identifier
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvshadow_store_get_copy_set_identifier(
     libvshadow_store_t *store,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_get_copy_set_identifier";
	int result                                  = 0;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

	if( internal_store->internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing internal volume.",
		 function );

		return( -1 );
	}
	result = libvshadow_store_descriptor_get_copy_set_identifier(
	          internal_store->store_descriptor,
	          guid,
	          size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve copy set identifier from store descriptor: %d.",
		 function,
		 internal_store->store_descriptor_index );

		return( -1 );
	}
	return( result );
}

/* Retrieves the attribute flags
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvshadow_store_get_attribute_flags(
     libvshadow_store_t *store,
     uint32_t *attribute_flags,
     libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_get_attribute_flags";
	int result                                  = 0;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

	if( internal_store->internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing internal volume.",
		 function );

		return( -1 );
	}
	result = libvshadow_store_descriptor_get_attribute_flags(
	          internal_store->store_descriptor,
	          attribute_flags,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve attribute flags from store descriptor: %d.",
		 function,
		 internal_store->store_descriptor_index );

		return( -1 );
	}
	return( result );
}

/* Retrieves the number of blocks
 * Returns 1 if successful or -1 on error
 */
int libvshadow_store_get_number_of_blocks(
     libvshadow_store_t *store,
     int *number_of_blocks,
     libcerror_error_t **error )
{
	libvshadow_internal_store_t *internal_store = NULL;
	static char *function                       = "libvshadow_store_get_number_of_blocks";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

	if( internal_store->internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing internal volume.",
		 function );

		return( -1 );
	}
	if( libvshadow_store_descriptor_get_number_of_blocks(
	     internal_store->store_descriptor,
	     internal_store->file_io_handle,
	     number_of_blocks,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of blocks store descriptor: %d.",
		 function,
		 internal_store->store_descriptor_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific block
 * Returns 1 if successful or -1 on error
 */
int libvshadow_store_get_block_by_index(
     libvshadow_store_t *store,
     int block_index,
     libvshadow_block_t **block,
     libcerror_error_t **error )
{
	libvshadow_block_descriptor_t *block_descriptor = NULL;
	libvshadow_internal_store_t *internal_store     = NULL;
	static char *function                           = "libvshadow_store_get_block_by_index";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libvshadow_internal_store_t *) store;

	if( internal_store->internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store - missing internal volume.",
		 function );

		return( -1 );
	}
	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	if( *block != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block value already set.",
		 function );

		return( -1 );
	}
	if( libvshadow_store_descriptor_get_block_descriptor_by_index(
	     internal_store->store_descriptor,
	     internal_store->file_io_handle,
	     block_index,
	     &block_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve block descriptor: %d from store descriptor: %d.",
		 function,
		 block_index,
		 internal_store->store_descriptor_index );

		return( -1 );
	}
	if( libvshadow_block_initialize(
	     block,
	     block_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block: %d.",
		 function,
		 block_index );

		return( -1 );
	}
	return( 1 );
}

