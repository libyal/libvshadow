/*
 * Info handle
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
#include <byte_stream.h>
#include <file_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "byte_size_string.h"
#include "info_handle.h"
#include "vshadowtools_libbfio.h"
#include "vshadowtools_libcerror.h"
#include "vshadowtools_libfdatetime.h"
#include "vshadowtools_libfguid.h"
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

#define INFO_HANDLE_NOTIFY_STREAM		stdout

/* Copies a string of a decimal value to a 64-bit value
 * Returns 1 if successful or -1 on error
 */
int vshadowtools_system_string_copy_from_64_bit_in_decimal(
     const system_character_t *string,
     size_t string_size,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	static char *function              = "vshadowtools_system_string_copy_from_64_bit_in_decimal";
	size_t string_index                = 0;
	system_character_t character_value = 0;
	uint8_t maximum_string_index       = 20;
	int8_t sign                        = 1;

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( value_64bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 64-bit.",
		 function );

		return( -1 );
	}
	*value_64bit = 0;

	if( string[ string_index ] == (system_character_t) '-' )
	{
		string_index++;
		maximum_string_index++;

		sign = -1;
	}
	else if( string[ string_index ] == (system_character_t) '+' )
	{
		string_index++;
		maximum_string_index++;
	}
	while( string_index < string_size )
	{
		if( string[ string_index ] == 0 )
		{
			break;
		}
		if( string_index > (size_t) maximum_string_index )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
			 "%s: string too large.",
			 function );

			return( -1 );
		}
		*value_64bit *= 10;

		if( ( string[ string_index ] >= (system_character_t) '0' )
		 && ( string[ string_index ] <= (system_character_t) '9' ) )
		{
			character_value = (system_character_t) ( string[ string_index ] - (system_character_t) '0' );
		}
		else
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported character value: %" PRIc_SYSTEM " at index: %d.",
			 function,
			 string[ string_index ],
			 string_index );

			return( -1 );
		}
		*value_64bit += character_value;

		string_index++;
	}
	if( sign == -1 )
	{
		*value_64bit *= (uint64_t) -1;
	}
	return( 1 );
}

/* Creates an info handle
 * Make sure the value info_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid info handle value already set.",
		 function );

		return( -1 );
	}
	*info_handle = memory_allocate_structure(
	                info_handle_t );

	if( *info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create info handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *info_handle,
	     0,
	     sizeof( info_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear info handle.",
		 function );

		memory_free(
		 *info_handle );

		*info_handle = NULL;

		return( -1 );
	}
	if( libbfio_file_range_initialize(
	     &( ( *info_handle )->input_file_io_handle ),
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
	     &( ( *info_handle )->input_volume ),
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
	( *info_handle )->notify_stream = INFO_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *info_handle != NULL )
	{
		if( ( *info_handle )->input_file_io_handle != NULL )
		{
			libbfio_handle_free(
			 &( ( *info_handle )->input_file_io_handle ),
			 NULL );
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( -1 );
}

/* Frees an info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( libvshadow_volume_free(
		     &( ( *info_handle )->input_volume ),
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
		     &( ( *info_handle )->input_file_io_handle ),
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
		 *info_handle );

		*info_handle = NULL;
	}
	return( result );
}

/* Signals the info handle to abort
 * Returns 1 if successful or -1 on error
 */
int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_volume != NULL )
	{
		if( libvshadow_volume_signal_abort(
		     info_handle->input_volume,
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
int info_handle_set_volume_offset(
     info_handle_t *info_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function = "info_handle_set_volume_offset";
	size_t string_length  = 0;
	uint64_t value_64bit  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	string_length = system_string_length(
	                 string );

	if( vshadowtools_system_string_copy_from_64_bit_in_decimal(
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
	info_handle->volume_offset = (off64_t) value_64bit;

	return( 1 );
}

/* Opens the info handle
 * Returns 1 if successful, 0 if no VSS enabled volume was found or -1 on error
 */
int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function  = "info_handle_open_input";
	size_t filename_length = 0;
	int result             = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	filename_length = system_string_length(
	                   filename );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libbfio_file_range_set_name_wide(
	     info_handle->input_file_io_handle,
	     filename,
	     filename_length,
	     error ) != 1 )
#else
	if( libbfio_file_range_set_name(
	     info_handle->input_file_io_handle,
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
	     info_handle->input_file_io_handle,
	     info_handle->volume_offset,
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
	          info_handle->input_file_io_handle,
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
		     info_handle->input_volume,
		     info_handle->input_file_io_handle,
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

/* Closes the info handle
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_close";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libvshadow_volume_close(
	     info_handle->input_volume,
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

/* Prints the block information to a stream
 * Returns 1 if successful or -1 on error
 */
int info_handle_block_fprint(
     info_handle_t *info_handle,
     int block_index,
     libvshadow_block_t *block,
     libcerror_error_t **error )
{
	static char *function   = "info_handle_block_fprint";
	off64_t original_offset = 0;
	off64_t offset          = 0;
	off64_t relative_offset = 0;
	uint32_t flags          = 0;
	uint32_t bitmap         = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libvshadow_block_get_values(
	     block,
	     &original_offset,
	     &relative_offset,
	     &offset,
	     &flags,
	     &bitmap,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve block: %d values.",
		 function,
		 block_index );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "Block: %d\n",
	 block_index + 1 );

	fprintf(
	 info_handle->notify_stream,
	 "\tOriginal offset\t\t: 0x%08" PRIx64 "\n",
	 original_offset );

	fprintf(
	 info_handle->notify_stream,
	 "\tRelative offset\t\t: 0x%08" PRIx64 "\n",
	 relative_offset );

	fprintf(
	 info_handle->notify_stream,
	 "\tOffset\t\t\t: 0x%08" PRIx64 "\n",
	 offset );

	fprintf(
	 info_handle->notify_stream,
	 "\tFlags\t\t\t: 0x%08" PRIx32 "\n",
	 flags );

	fprintf(
	 info_handle->notify_stream,
	 "\tBitmap\t\t\t: 0x%08" PRIx32 "\n",
	 bitmap );

	return( 1 );
}

/* Prints the store information to a stream
 * Returns 1 if successful or -1 on error
 */
int info_handle_store_fprint(
     info_handle_t *info_handle,
     int store_index,
     libvshadow_store_t *store,
     libcerror_error_t **error )
{
	system_character_t byte_size_string[ 16 ];
	system_character_t filetime_string[ 32 ];
	system_character_t guid_string[ 48 ];
	uint8_t guid_buffer[ 16 ];

	libfdatetime_filetime_t *filetime = NULL;
	libfguid_identifier_t *guid       = NULL;
	libvshadow_block_t *block         = NULL;
	static char *function             = "info_handle_store_fprint";
	size64_t volume_size              = 0;
	uint64_t value_64bit              = 0;
	uint32_t attribute_flags          = 0;
	int block_index                   = 0;
	int has_in_volume_store_data      = 0;
	int number_of_blocks              = 0;
	int result                        = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Store: %d\n",
	 store_index + 1 );

	if( libfdatetime_filetime_initialize(
	     &filetime,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create filetime.",
		 function );

		goto on_error;
	}
	if( libfguid_identifier_initialize(
	     &guid,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create GUID.",
		 function );

		goto on_error;
	}
	has_in_volume_store_data = libvshadow_store_has_in_volume_data(
	                            store,
	                            error );

	if( has_in_volume_store_data == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if store: %d has in-volume data.",
		 function,
		 store_index );

		goto on_error;
	}
	else if( has_in_volume_store_data == 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tData stored outside volume.\n" );
	}
	if( libvshadow_store_get_identifier(
	     store,
	     guid_buffer,
	     16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve store: %d identifier.",
		 function,
		 store_index );

		goto on_error;
	}
	if( libfguid_identifier_copy_from_byte_stream(
	     guid,
	     guid_buffer,
	     16,
	     LIBFGUID_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy byte stream to GUID.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfguid_identifier_copy_to_utf16_string(
		  guid,
		  (uint16_t *) guid_string,
		  48,
		  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
		  error );
#else
	result = libfguid_identifier_copy_to_utf8_string(
		  guid,
		  (uint8_t *) guid_string,
		  48,
		  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy GUID to string.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tIdentifier\t\t: %" PRIs_SYSTEM "\n",
	 guid_string );

	result = libvshadow_store_get_copy_set_identifier(
	          store,
	          guid_buffer,
	          16,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve store: %d shadow copy set identifier.",
		 function,
		 store_index );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     guid_buffer,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tShadow copy set ID\t: %" PRIs_SYSTEM "\n",
		 guid_string );
	}
	if( libvshadow_store_get_creation_time(
	     store,
	     &value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve store: %d creation time.",
		 function,
		 store_index );

		goto on_error;
	}
	if( libfdatetime_filetime_copy_from_64bit(
	     filetime,
	     value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to create filetime.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfdatetime_filetime_copy_to_utf16_string(
		  filetime,
		  (uint16_t *) filetime_string,
		  32,
		  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		  error );
#else
	result = libfdatetime_filetime_copy_to_utf8_string(
		  filetime,
		  (uint8_t *) filetime_string,
		  32,
		  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy filetime to string.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tCreation time\t\t: %" PRIs_SYSTEM " UTC\n",
	 filetime_string );

	result = libvshadow_store_get_copy_identifier(
	          store,
	          guid_buffer,
	          16,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve store: %d shadow copy identifier.",
		 function,
		 store_index );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     guid_buffer,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tShadow copy ID\t\t: %" PRIs_SYSTEM "\n",
		 guid_string );
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
	result = byte_size_string_create(
	          byte_size_string,
	          16,
	          volume_size,
	          BYTE_SIZE_STRING_UNIT_MEBIBYTE,
	          NULL );

	if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tVolume size\t\t: %" PRIs_SYSTEM " (%" PRIu64 " bytes)\n",
		 byte_size_string,
		 volume_size );
	}
	else
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tVolume size\t\t: %" PRIu64 " bytes\n",
		 volume_size );
	}
	result = libvshadow_store_get_attribute_flags(
	          store,
	          &attribute_flags,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve store: %d attribute flags.",
		 function,
		 store_index );

		goto on_error;
	}
	else if( result != 0 )
	{
/* TODO print a description of the flags */
		fprintf(
		 info_handle->notify_stream,
		 "\tAttribute flags\t\t: 0x%08" PRIx32 "\n",
		 attribute_flags );
	}
	if( libfguid_identifier_free(
	     &guid,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free GUID.",
		 function );

		goto on_error;
	}
	if( libfdatetime_filetime_free(
	     &filetime,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free filetime.",
		 function );

		goto on_error;
	}
	if( info_handle->show_allocation_information != 0 )
	{
		if( libvshadow_store_get_number_of_blocks(
		     store,
		     &number_of_blocks,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve store: %d number of blocks.",
			 function,
			 store_index );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tNumber of blocks\t: %d\n",
		 number_of_blocks );

		for( block_index = 0;
		     block_index < number_of_blocks;
		     block_index++ )
		{
			if( libvshadow_store_get_block_by_index(
			     store,
			     block_index,
			     &block,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve block: %d.",
				 function,
				 block_index );

				goto on_error;
			}
			if( info_handle_block_fprint(
			     info_handle,
			     block_index,
			     block,
			     error ) != 1 )
			{
				goto on_error;
			}
			if( libvshadow_block_free(
			     &block,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free block: %d.",
				 function,
				 block_index );

				goto on_error;
			}
		}
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( block != NULL )
	{
		libvshadow_block_free(
		 &block,
		 NULL );
	}
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( -1 );
}

/* Prints the volume information to a stream
 * Returns 1 if successful or -1 on error
 */
int info_handle_volume_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libvshadow_store_t *store = NULL;
	static char *function     = "vshadowinfo_volume_info_fprint";
	int number_of_stores      = 0;
	int store_index           = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Volume Shadow Snapshot information:\n" );

	if( libvshadow_volume_get_number_of_stores(
	     info_handle->input_volume,
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
	 info_handle->notify_stream,
	 "\tNumber of stores:\t%d\n",
	 number_of_stores );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	for( store_index = 0;
	     store_index < number_of_stores;
	     store_index++ )
	{
		if( libvshadow_volume_get_store(
		     info_handle->input_volume,
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
		if( info_handle_store_fprint(
		     info_handle,
		     store_index,
		     store,
		     error ) != 1 )
		{
			goto on_error;
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

