/*
 * Store block functions
 *
 * Copyright (C) 2011-2015, Joachim Metz <joachim.metz@gmail.com>
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libvshadow_libbfio.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_libcnotify.h"
#include "libvshadow_libcstring.h"
#include "libvshadow_libfguid.h"
#include "libvshadow_io_handle.h"
#include "libvshadow_store_block.h"

#include "vshadow_store.h"

/* Creates a store block
 * Make sure the value store_block is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvshadow_store_block_initialize(
     libvshadow_store_block_t **store_block,
     size_t block_size,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_store_block_initialize";

	if( store_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store block.",
		 function );

		return( -1 );
	}
	if( *store_block != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid store block value already set.",
		 function );

		return( -1 );
	}
	if( block_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid block size value exceeds maximum.",
		 function );

		return( -1 );
	}
	*store_block = memory_allocate_structure(
	                libvshadow_store_block_t );

	if( store_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create store block.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *store_block,
	     0,
	     sizeof( libvshadow_store_block_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear store block.",
		 function );

		goto on_error;
	}
	( *store_block )->data = (uint8_t *) memory_allocate(
	                                      sizeof( uint8_t ) * block_size );

	if( ( *store_block )->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create store block data.",
		 function );

		goto on_error;
	}
	( *store_block )->data_size = block_size;

	return( 1 );

on_error:
	if( *store_block != NULL )
	{
		memory_free(
		 *store_block );

		*store_block = NULL;
	}
	return( -1 );
}

/* Frees a store block
 * Returns 1 if successful or -1 on error
 */
int libvshadow_store_block_free(
     libvshadow_store_block_t **store_block,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_store_block_free";

	if( store_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store block.",
		 function );

		return( -1 );
	}
	if( *store_block != NULL )
	{
		memory_free(
		 ( *store_block )->data );
		memory_free(
		 *store_block );

		*store_block = NULL;
	}
	return( 1 );
}

/* Reads the store block
 * Returns 1 if successful or -1 on error
 */
int libvshadow_store_block_read(
     libvshadow_store_block_t *store_block,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	static char *function       = "libvshadow_store_block_read";
	ssize_t read_count          = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t guid_string[ 48 ];

	libfguid_identifier_t *guid = NULL;
	uint64_t value_64bit        = 0;
	int result                  = 0;
#endif

	if( store_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store block.",
		 function );

		return( -1 );
	}
	if( store_block->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid store block - missing data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading store block at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek store block offset: %" PRIi64 ".",
		 function,
		 file_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              store_block->data,
	              store_block->data_size,
	              error );

	if( read_count != (ssize_t) store_block->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: store block header:\n",
		 function );
		libcnotify_print_data(
		 store_block->data,
		 sizeof( vshadow_store_block_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (vshadow_store_block_header_t *) store_block->data )->identifier,
	     vshadow_vss_identifier,
	     8 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid store block list header identifier.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (vshadow_store_block_header_t *) store_block->data )->version,
	 store_block->version );

	byte_stream_copy_to_uint32_little_endian(
	 ( (vshadow_store_block_header_t *) store_block->data )->record_type,
	 store_block->record_type );

	byte_stream_copy_to_uint64_little_endian(
	 ( (vshadow_store_block_header_t *) store_block->data )->relative_offset,
	 store_block->relative_offset );

	byte_stream_copy_to_uint64_little_endian(
	 ( (vshadow_store_block_header_t *) store_block->data )->offset,
	 store_block->offset );

	byte_stream_copy_to_uint64_little_endian(
	 ( (vshadow_store_block_header_t *) store_block->data )->next_offset,
	 store_block->next_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
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

			return( -1 );
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     ( (vshadow_store_block_header_t *) store_block->data )->identifier,
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

			return( -1 );
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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

			return( -1 );
		}
		libcnotify_printf(
		 "%s: identifier\t\t\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 guid_string );

		libcnotify_printf(
		 "%s: version\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 store_block->version );

		libcnotify_printf(
		 "%s: record type\t\t\t\t: %" PRIu32 "\n",
		 function,
		 store_block->record_type );

		libcnotify_printf(
		 "%s: relative offset\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 store_block->relative_offset );

		libcnotify_printf(
		 "%s: offset\t\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 store_block->offset );

		libcnotify_printf(
		 "%s: next offset\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 store_block->next_offset );

		byte_stream_copy_to_uint64_little_endian(
		 ( (vshadow_store_block_header_t *) store_block->data )->unknown1,
		 value_64bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: unknown2:\n",
		 function );
		libcnotify_print_data(
		 ( (vshadow_store_block_header_t *) store_block->data )->unknown2,
		 72,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

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

			return( -1 );
		}
	}
#endif
	if( store_block->version != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported version: %" PRIu32 ".",
		 function,
		 store_block->version );

		return( -1 );
	}
	return( 1 );
}

