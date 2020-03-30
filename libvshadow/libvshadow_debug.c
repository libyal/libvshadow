/*
 * Debug functions
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libvshadow_debug.h"
#include "libvshadow_definitions.h"
#include "libvshadow_libbfio.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_libcnotify.h"
#include "libvshadow_libfdatetime.h"
#include "libvshadow_libfguid.h"
#include "libvshadow_libuna.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the attribute flags
 */
void libvshadow_debug_print_attribute_flags(
      uint32_t attribute_flags )
{
	if( ( attribute_flags & 0x00000001 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_PERSISTENT)\n" );
	}
	if( ( attribute_flags & 0x00000002 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_NO_AUTORECOVERY)\n" );
	}
	if( ( attribute_flags & 0x00000004 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_CLIENT_ACCESSIBLE)\n" );
	}
	if( ( attribute_flags & 0x00000008 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_NO_AUTO_RELEASE)\n" );
	}
	if( ( attribute_flags & 0x00000010 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_NO_WRITERS)\n" );
	}
	if( ( attribute_flags & 0x00000020 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_TRANSPORTABLE)\n" );
	}
	if( ( attribute_flags & 0x00000040 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_NOT_SURFACED)\n" );
	}
	if( ( attribute_flags & 0x00000080 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_NOT_TRANSACTED)\n" );
	}

	if( ( attribute_flags & 0x00010000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_HARDWARE_ASSISTED)\n" );
	}
	if( ( attribute_flags & 0x00020000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_DIFFERENTIAL)\n" );
	}
	if( ( attribute_flags & 0x00040000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_PLEX)\n" );
	}
	if( ( attribute_flags & 0x00080000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_IMPORTED)\n" );
	}
	if( ( attribute_flags & 0x00100000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_EXPOSED_LOCALLY)\n" );
	}
	if( ( attribute_flags & 0x00200000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_EXPOSED_REMOTELY)\n" );
	}
	if( ( attribute_flags & 0x00400000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_AUTORECOVER)\n" );
	}
	if( ( attribute_flags & 0x00800000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_ROLLBACK_RECOVERY)\n" );
	}
	if( ( attribute_flags & 0x01000000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_DELAYED_POSTSNAPSHOT)\n" );
	}
	if( ( attribute_flags & 0x01000000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_TXF_RECOVERY)\n" );
	}
}

/* Prints a FILETIME value
 * Returns 1 if successful or -1 on error
 */
int libvshadow_debug_print_filetime_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	char date_time_string[ 32 ];

	libfdatetime_filetime_t *filetime = NULL;
	static char *function             = "libvshadow_debug_print_filetime_value";

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
	if( libfdatetime_filetime_copy_from_byte_stream(
	     filetime,
	     byte_stream,
	     byte_stream_size,
	     byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy byte stream to filetime.",
		 function );

		goto on_error;
	}
	if( libfdatetime_filetime_copy_to_utf8_string(
	     filetime,
	     (uint8_t *) date_time_string,
	     32,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy filetime to string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s: %s UTC\n",
	 function_name,
	 value_name,
	 date_time_string );

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
	return( 1 );

on_error:
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( -1 );
}

/* Prints a GUID/UUID value
 * Returns 1 if successful or -1 on error
 */
int libvshadow_debug_print_guid_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
        system_character_t guid_string[ 48 ];

        libfguid_identifier_t *guid = NULL;
	static char *function       = "libvshadow_debug_print_guid_value";

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
	if( libfguid_identifier_copy_from_byte_stream(
	     guid,
	     byte_stream,
	     byte_stream_size,
	     byte_order,
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
	if( libfguid_identifier_copy_to_utf8_string(
	     guid,
	     (uint8_t *) guid_string,
	     48,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy GUID to string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s: %s\n",
	 function_name,
	 value_name,
	 guid_string );

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
	return( 1 );

on_error:
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	return( -1 );
}

/* Prints an UTF-16 string value
 * Returns 1 if successful or -1 on error
 */
int libvshadow_debug_print_utf16_string_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	system_character_t *string = NULL;
	static char *function      = "libvshadow_debug_print_utf16_string_value";
	size_t string_size         = 0;
	int result                 = 0;

	if( ( byte_stream == NULL )
	 || ( byte_stream_size == 0 ) )
	{
		libcnotify_printf(
		 "%s: %s: \n",
		 function_name,
		 value_name );

		return( 1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libuna_utf16_string_size_from_utf16_stream(
		  byte_stream,
		  byte_stream_size,
		  byte_order,
		  &string_size,
		  error );
#else
	result = libuna_utf8_string_size_from_utf16_stream(
		  byte_stream,
		  byte_stream_size,
		  byte_order,
		  &string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of string.",
		 function );

		goto on_error;
	}
	if( ( string_size > (size_t) SSIZE_MAX )
	 || ( ( sizeof( system_character_t ) * string_size ) > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		goto on_error;
	}
	string = system_string_allocate(
	          string_size );

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create string.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libuna_utf16_string_copy_from_utf16_stream(
		  (libuna_utf16_character_t *) string,
		  string_size,
		  byte_stream,
		  byte_stream_size,
		  byte_order,
		  error );
#else
	result = libuna_utf8_string_copy_from_utf16_stream(
		  (libuna_utf8_character_t *) string,
		  string_size,
		  byte_stream,
		  byte_stream_size,
		  byte_order,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s: %s\n",
	 function_name,
	 value_name,
	 string );

	memory_free(
	 string );

	return( 1 );

on_error:
	if( string != NULL )
	{
		memory_free(
		 string );
	}
	return( -1 );
}

/* Prints the read offsets
 * Returns 1 if successful or -1 on error
 */
int libvshadow_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_debug_print_read_offsets";
	off64_t offset        = 0;
	size64_t size         = 0;
	int number_of_offsets = 0;
	int offset_iterator   = 0;

	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_number_of_offsets_read(
	     file_io_handle,
	     &number_of_offsets,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of offsets read.",
		 function );

		return( -1 );
	}
	libcnotify_printf(
	 "Offsets read:\n" );

	for( offset_iterator = 0;
	     offset_iterator < number_of_offsets;
	     offset_iterator++ )
	{
		if( libbfio_handle_get_offset_read(
		     file_io_handle,
		     offset_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offset: %d.",
			 function,
			 ( offset_iterator + 1 ) );

			return( -1 );
		}
		libcnotify_printf(
		 "%08" PRIi64 " ( 0x%08" PRIx64 " ) - %08" PRIi64 " ( 0x%08" PRIx64 " ) size: %" PRIu64 "\n",
		 offset,
		 offset,
		 offset + (off64_t) size,
		 offset + (off64_t) size,
		 size );
	}
	libcnotify_printf(
	 "\n" );

	return( 1 );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

