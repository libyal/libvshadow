/*
 * Block descriptor functions
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

#include "libvshadow_block_descriptor.h"
#include "libvshadow_debug.h"
#include "libvshadow_definitions.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_libcnotify.h"
#include "libvshadow_unused.h"

#include "vshadow_store.h"

const uint8_t vshadow_empty_store_block_list_entry[ 32 ] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/* Creates a block descriptor
 * Make sure the value block_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_descriptor_initialize(
     libvshadow_block_descriptor_t **block_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_block_descriptor_initialize";

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	if( *block_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block descriptor value already set.",
		 function );

		return( -1 );
	}
	*block_descriptor = memory_allocate_structure(
	                     libvshadow_block_descriptor_t );

	if( *block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *block_descriptor,
	     0,
	     sizeof( libvshadow_block_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block descriptor.",
		 function );

		goto on_error;
	}
	( *block_descriptor )->index         = -1;
	( *block_descriptor )->reverse_index = -1;

	return( 1 );

on_error:
	if( *block_descriptor != NULL )
	{
		memory_free(
		 *block_descriptor );

		*block_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a block descriptor
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_descriptor_free(
     libvshadow_block_descriptor_t **block_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_block_descriptor_free";
	int result            = 1;

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	if( *block_descriptor != NULL )
	{
		if( ( *block_descriptor )->overlay != NULL )
		{
			if( libvshadow_block_descriptor_free(
			     &( ( *block_descriptor )->overlay ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free overlay block descriptor.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *block_descriptor );

		*block_descriptor = NULL;
	}
	return( result );
}

/* Frees a block descriptor if stored in the reverse block tree only
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_descriptor_free_reverse(
     libvshadow_block_descriptor_t **block_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_block_descriptor_free_reverse";
	int result            = 1;

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	if( ( *block_descriptor != NULL )
	 && ( ( *block_descriptor )->index == -1 ) )
	{
		if( ( *block_descriptor )->overlay != NULL )
		{
			if( libvshadow_block_descriptor_free(
			     &( ( *block_descriptor )->overlay ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free overlay block descriptor.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *block_descriptor );

		*block_descriptor = NULL;
	}
	return( result );
}

/* Clones a block descriptor
 * Make sure the value destination_block_descriptor is pointing to is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_descriptor_clone(
     libvshadow_block_descriptor_t **destination_block_descriptor,
     libvshadow_block_descriptor_t *source_block_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_block_descriptor_clone";

	if( destination_block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination block descriptor.",
		 function );

		return( -1 );
	}
	if( *destination_block_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid destination block descriptor value already set.",
		 function );

		return( -1 );
	}
	if( source_block_descriptor == NULL )
	{
		*destination_block_descriptor = NULL;

		return( 1 );
	}
	*destination_block_descriptor = memory_allocate_structure(
	                                 libvshadow_block_descriptor_t );

	if( *destination_block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create destination block descriptor.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     *destination_block_descriptor,
	     source_block_descriptor,
	     sizeof( libvshadow_block_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy block descriptor.",
		 function );

		goto on_error;
	}
	if( source_block_descriptor->overlay != NULL )
	{
		if( libvshadow_block_descriptor_clone(
		     &( ( *destination_block_descriptor )->overlay ),
		     source_block_descriptor->overlay,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create destination overlay block descriptor.",
			 function );

			goto on_error;
		}
	}
	( *destination_block_descriptor )->index         = -1;
	( *destination_block_descriptor )->reverse_index = -1;

	return( 1 );

on_error:
	if( *destination_block_descriptor != NULL )
	{
		memory_free(
		 *destination_block_descriptor );

		*destination_block_descriptor = NULL;
	}
	return( -1 );
}

/* Reads the block descriptor
 * Returns 1 if successful, 0 if block list entry is empty or -1 on error
 */
int libvshadow_block_descriptor_read_data(
     libvshadow_block_descriptor_t *block_descriptor,
     const uint8_t *data,
     size_t data_size,
     int store_index LIBVSHADOW_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_block_descriptor_read_data";

	LIBVSHADOW_UNREFERENCED_PARAMETER( store_index )

	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size < sizeof( vshadow_store_block_list_entry_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( memory_compare(
	     data,
             vshadow_empty_store_block_list_entry,
             sizeof( vshadow_store_block_list_entry_t ) ) == 0 )
	{
		return( 0 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: store: %02d data:\n",
		 function,
		 store_index );
		libcnotify_print_data(
		 data,
		 sizeof( vshadow_store_block_list_entry_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint64_little_endian(
	 ( (vshadow_store_block_list_entry_t *) data )->original_offset,
	 block_descriptor->original_offset );

	byte_stream_copy_to_uint64_little_endian(
	 ( (vshadow_store_block_list_entry_t *) data )->relative_offset,
	 block_descriptor->relative_offset );

	byte_stream_copy_to_uint64_little_endian(
	 ( (vshadow_store_block_list_entry_t *) data )->offset,
	 block_descriptor->offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (vshadow_store_block_list_entry_t *) data )->flags,
	 block_descriptor->flags );

	byte_stream_copy_to_uint32_little_endian(
	 ( (vshadow_store_block_list_entry_t *) data )->allocation_bitmap,
	 block_descriptor->bitmap );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: store: %02d original offset\t: 0x%08" PRIx64 "\n",
		 function,
		 store_index,
		 block_descriptor->original_offset );

		libcnotify_printf(
		 "%s: store: %02d relative offset\t: 0x%08" PRIx64 "\n",
		 function,
		 store_index,
		 block_descriptor->relative_offset );

		libcnotify_printf(
		 "%s: store: %02d offset\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 store_index,
		 block_descriptor->offset );

		libcnotify_printf(
		 "%s: store: %02d flags\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 store_index,
		 block_descriptor->flags );

		libcnotify_printf(
		 "%s: store: %02d allocation bitmap\t: 0x%08" PRIx32 "\n",
		 function,
		 store_index,
		 block_descriptor->bitmap );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( ( block_descriptor->flags & LIBVSHADOW_BLOCK_FLAG_IS_FORWARDER ) != 0 )
	{
		if( block_descriptor->offset != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported offset - value not zero.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

