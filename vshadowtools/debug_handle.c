/*
 * Debug handle
 *
 * Copyright (C) 2011-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "debug_handle.h"
#include "vshadowtools_libbfio.h"
#include "vshadowtools_libcerror.h"
#include "vshadowtools_libcsystem.h"
#include "vshadowtools_libvshadow.h"

#if !defined( LIBVSHADOW_HAVE_BFIO )

extern \
int libvshadow_volume_open_file_io_handle(
     libvshadow_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvshadow_error_t **error );

extern \
int libvshadow_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#endif /* !defined( LIBVSHADOW_HAVE_BFIO ) */

#define TEST_HANDLE_NOTIFY_STREAM		stdout

/* Creates a debug handle
 * Make sure the value debug_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int debug_handle_initialize(
     debug_handle_t **debug_handle,
     libcerror_error_t **error )
{
	static char *function = "debug_handle_initialize";

	if( debug_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid debug handle.",
		 function );

		return( -1 );
	}
	if( *debug_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid debug handle value already set.",
		 function );

		return( -1 );
	}
	*debug_handle = memory_allocate_structure(
	                 debug_handle_t );

	if( *debug_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create debug handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *debug_handle,
	     0,
	     sizeof( debug_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear debug handle.",
		 function );

		memory_free(
		 *debug_handle );

		*debug_handle = NULL;

		return( -1 );
	}
	if( libbfio_file_range_initialize(
	     &( ( *debug_handle )->input_file_io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input file IO handle.",
		 function );

		goto on_error;
	}
	if( libvshadow_volume_initialize(
	     &( ( *debug_handle )->input_volume ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input volume.",
		 function );

		goto on_error;
	}
	( *debug_handle )->notify_stream = TEST_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *debug_handle != NULL )
	{
		if( ( *debug_handle )->input_file_io_handle != NULL )
		{
			libbfio_handle_free(
			 &( ( *debug_handle )->input_file_io_handle ),
			 NULL );
		}
		memory_free(
		 *debug_handle );

		*debug_handle = NULL;
	}
	return( -1 );
}

/* Frees a debug handle
 * Returns 1 if successful or -1 on error
 */
int debug_handle_free(
     debug_handle_t **debug_handle,
     libcerror_error_t **error )
{
	static char *function = "debug_handle_free";
	int result            = 1;

	if( debug_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid debug handle.",
		 function );

		return( -1 );
	}
	if( *debug_handle != NULL )
	{
		if( libvshadow_volume_free(
		     &( ( *debug_handle )->input_volume ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free input volume.",
			 function );

			result = -1;
		}
		if( libbfio_handle_free(
		     &( ( *debug_handle )->input_file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free input file IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 *debug_handle );

		*debug_handle = NULL;
	}
	return( result );
}

/* Signals the debug handle to abort
 * Returns 1 if successful or -1 on error
 */
int debug_handle_signal_abort(
     debug_handle_t *debug_handle,
     libcerror_error_t **error )
{
	static char *function = "debug_handle_signal_abort";

	if( debug_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid debug handle.",
		 function );

		return( -1 );
	}
	if( debug_handle->input_volume != NULL )
	{
		if( libvshadow_volume_signal_abort(
		     debug_handle->input_volume,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input volume to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the volume offset
 * Returns 1 if successful or -1 on error
 */
int debug_handle_set_volume_offset(
     debug_handle_t *debug_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function = "debug_handle_set_volume_offset";
	size_t string_length  = 0;
	uint64_t value_64bit  = 0;

	if( debug_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid debug handle.",
		 function );

		return( -1 );
	}
	string_length = system_string_length(
	                 string );

	if( libcsystem_string_decimal_copy_to_64_bit(
	     string,
	     string_length + 1,
	     &value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy string to 64-bit decimal.",
		 function );

		return( -1 );
	}
	debug_handle->volume_offset = (off64_t) value_64bit;

	return( 1 );
}

/* Opens the debug handle
 * Returns 1 if successful, 0 if no VSS enabled volume was found or -1 on error
 */
int debug_handle_open_input(
     debug_handle_t *debug_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function  = "debug_handle_open_input";
	size_t filename_length = 0;
	int result             = 0;

	if( debug_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid debug handle.",
		 function );

		return( -1 );
	}
	filename_length = system_string_length(
	                   filename );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libbfio_file_range_set_name_wide(
	     debug_handle->input_file_io_handle,
	     filename,
	     filename_length,
	     error ) != 1 )
#else
	if( libbfio_file_range_set_name(
	     debug_handle->input_file_io_handle,
	     filename,
	     filename_length,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set filename.",
		 function );

		return( -1 );
	}
	if( libbfio_file_range_set(
	     debug_handle->input_file_io_handle,
	     debug_handle->volume_offset,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open set volume offset.",
		 function );

		return( -1 );
	}
	result = libvshadow_check_volume_signature_file_io_handle(
	          debug_handle->input_file_io_handle,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if volume has a VSS signature.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libvshadow_volume_open_file_io_handle(
		     debug_handle->input_volume,
		     debug_handle->input_file_io_handle,
		     LIBVSHADOW_OPEN_READ,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open input volume.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

/* Closes the debug handle
 * Returns the 0 if succesful or -1 on error
 */
int debug_handle_close(
     debug_handle_t *debug_handle,
     libcerror_error_t **error )
{
	static char *function = "debug_handle_close";

	if( debug_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid debug handle.",
		 function );

		return( -1 );
	}
	if( libvshadow_volume_close(
	     debug_handle->input_volume,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input volume.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Tests read
 * Returns 1 if successful or -1 on error
 */
int debug_handle_test_read(
     debug_handle_t *debug_handle,
     libcerror_error_t **error )
{
	uint8_t buffer[ 8000 ];

	libvshadow_store_t *store = NULL;
	static char *function     = "debug_handle_test_read";
	off64_t volume_offset     = 0;
	size64_t volume_size      = 0;
	size_t read_size          = 8000;
	ssize_t read_count        = 0;
	int number_of_stores      = 0;
	int store_index           = 0;

	if( debug_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid debug handle.",
		 function );

		return( -1 );
	}
	if( libvshadow_volume_get_number_of_stores(
	     debug_handle->input_volume,
	     &number_of_stores,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of stores.",
		 function );

		goto on_error;
	}
	fprintf(
	 debug_handle->notify_stream,
	 "Testing reading data from stores.\n" );

	for( store_index = number_of_stores - 1;
	     store_index >= 0;
	     store_index-- )
	{
		fprintf(
		 debug_handle->notify_stream,
		 "Reading data from store %d out of %d\n",
		 store_index + 1,
		 number_of_stores );

		if( libvshadow_volume_get_store(
		     debug_handle->input_volume,
		     store_index,
		     &store,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve store: %d.",
			 function,
			 store_index );

			goto on_error;
		}
		if( libvshadow_store_get_volume_size(
		     store,
		     &volume_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve store: %d volume size.",
			 function,
			 store_index );

			goto on_error;
		}
		volume_offset = 0;

		if( libvshadow_store_seek_offset(
		     store,
		     volume_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek offset in store: %d.",
			 function,
			 store_index );

			return( -1 );
		}
		while( (size64_t) volume_offset < volume_size )
		{
			read_count = libvshadow_store_read_buffer(
			              store,
			              buffer,
			              read_size,
			              error );

			if( read_count == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read buffer from store: %d.",
				 function,
				 store_index );

				goto on_error;
			}
			volume_offset += read_size;
		}
		if( libvshadow_store_free(
		     &store,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free store: %d.",
			 function,
			 store_index );

			goto on_error;
		}
	}
	fprintf(
	 debug_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( store != NULL )
	{
		libvshadow_store_free(
		 &store,
		 NULL );
	}
	return( -1 );
}

