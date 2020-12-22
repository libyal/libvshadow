/*
 * Block range descriptor functions
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

#include "libvshadow_block_range_descriptor.h"
#include "libvshadow_debug.h"
#include "libvshadow_definitions.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_libcnotify.h"
#include "libvshadow_unused.h"

#include "vshadow_store.h"

const uint8_t vshadow_empty_store_block_range_list_entry[ 24 ] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0 };

/* Creates a block range descriptor
 * Make sure the value block_range_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_range_descriptor_initialize(
     libvshadow_block_range_descriptor_t **block_range_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_block_range_descriptor_initialize";

	if( block_range_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block range descriptor.",
		 function );

		return( -1 );
	}
	if( *block_range_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block range descriptor value already set.",
		 function );

		return( -1 );
	}
	*block_range_descriptor = memory_allocate_structure(
	                           libvshadow_block_range_descriptor_t );

	if( *block_range_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block range descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *block_range_descriptor,
	     0,
	     sizeof( libvshadow_block_range_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block range descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *block_range_descriptor != NULL )
	{
		memory_free(
		 *block_range_descriptor );

		*block_range_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a block range descriptor
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_range_descriptor_free(
     libvshadow_block_range_descriptor_t **block_range_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_block_range_descriptor_free";

	if( block_range_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block range descriptor.",
		 function );

		return( -1 );
	}
	if( *block_range_descriptor != NULL )
	{
		memory_free(
		 *block_range_descriptor );

		*block_range_descriptor = NULL;
	}
	return( 1 );
}

/* Reads the block range descriptor
 * Returns 1 if successful, 0 if block list entry is empty or -1 on error
 */
int libvshadow_block_range_descriptor_read_data(
     libvshadow_block_range_descriptor_t *block_range_descriptor,
     const uint8_t *data,
     size_t data_size,
     int store_index LIBVSHADOW_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_block_range_descriptor_read_data";

	LIBVSHADOW_UNREFERENCED_PARAMETER( store_index )

	if( block_range_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block range descriptor.",
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
	if( ( data_size < sizeof( vshadow_store_block_range_list_entry_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_compare(
	     data,
             vshadow_empty_store_block_range_list_entry,
             sizeof( vshadow_store_block_range_list_entry_t ) ) == 0 )
	{
		return( 0 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: store: %02d block range list entry data:\n",
		 function,
		 store_index );
		libcnotify_print_data(
		 data,
		 sizeof( vshadow_store_block_range_list_entry_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint64_little_endian(
	 ( (vshadow_store_block_range_list_entry_t *) data )->offset,
	 block_range_descriptor->offset );

	byte_stream_copy_to_uint64_little_endian(
	 ( (vshadow_store_block_range_list_entry_t *) data )->relative_offset,
	 block_range_descriptor->relative_offset );

	byte_stream_copy_to_uint64_little_endian(
	 ( (vshadow_store_block_range_list_entry_t *) data )->size,
	 block_range_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: store: %02d offset\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 store_index,
		 block_range_descriptor->offset );

		libcnotify_printf(
		 "%s: store: %02d relative offset\t\t: 0x%08" PRIx64 "\n",
		 function,
		 store_index,
		 block_range_descriptor->relative_offset );

		libcnotify_printf(
		 "%s: store: %02d size\t\t\t: %" PRIu64 "\n",
		 function,
		 store_index,
		 block_range_descriptor->size );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

