/*
 * OSS-Fuzz target for libvshadow store type
 *
 * Copyright (C) 2011-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libvshadow.h"

#if !defined( LIBVSHADOW_HAVE_BFIO )

/* Opens a volume using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBVSHADOW_EXTERN \
int libvshadow_volume_open_file_io_handle(
     libvshadow_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvshadow_error_t **error );

#endif /* !defined( LIBVSHADOW_HAVE_BFIO ) */

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	uint8_t buffer[ 512 ];
	uint8_t guid[ 16 ];

	libbfio_handle_t *file_io_handle = NULL;
	libvshadow_store_t *store        = NULL;
	libvshadow_volume_t *volume      = NULL;
	off64_t volume_offset            = 0;
	size64_t volume_size             = 0;
	uint64_t value_64bit             = 0;
	uint32_t value_32bit             = 0;
	int number_of_blocks             = 0;
	int number_of_stores             = 0;
	int read_iterator                = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libvshadow_volume_initialize(
	     &volume,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libvshadow_volume_open_file_io_handle(
	     volume,
	     file_io_handle,
	     LIBVSHADOW_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libvshadow_volume;
	}
	if( libvshadow_volume_get_number_of_stores(
	     volume,
	     &number_of_stores,
	     NULL ) != 1 )
	{
		goto on_error_libvshadow_volume;
	}
	if( number_of_stores > 0 )
	{
		if( libvshadow_volume_get_store_identifier(
		     volume,
		     0,
		     guid,
		     16,
		     NULL ) != 1 )
		{
			goto on_error_libvshadow_volume;
		}
		if( libvshadow_volume_get_store(
		     volume,
		     0,
		     &store,
		     NULL ) != 1 )
		{
			goto on_error_libvshadow_volume;
		}
		if( libvshadow_store_get_identifier(
		     store,
		     guid,
		     16,
		     NULL ) != 1 )
		{
			goto on_error_libvshadow_store;
		}
		if( libvshadow_store_get_creation_time(
		     store,
		     &value_64bit,
		     NULL ) != 1 )
		{
			goto on_error_libvshadow_store;
		}
		if( libvshadow_store_get_copy_identifier(
		     store,
		     guid,
		     16,
		     NULL ) != 1 )
		{
			goto on_error_libvshadow_store;
		}
		if( libvshadow_store_get_copy_set_identifier(
		     store,
		     guid,
		     16,
		     NULL ) != 1 )
		{
			goto on_error_libvshadow_store;
		}
		if( libvshadow_store_get_attribute_flags(
		     store,
		     &value_32bit,
		     NULL ) != 1 )
		{
			goto on_error_libvshadow_store;
		}
		if( libvshadow_store_get_number_of_blocks(
		     store,
		     &number_of_blocks,
		     NULL ) != 1 )
		{
			goto on_error_libvshadow_store;
		}
		if( libvshadow_store_get_size(
		     store,
		     &value_64bit,
		     NULL ) != 1 )
		{
			goto on_error_libvshadow_store;
		}
		if( libvshadow_store_get_volume_size(
		     store,
		     &volume_size,
		     NULL ) != 1 )
		{
			goto on_error_libvshadow_store;
		}
		for( read_iterator = 0;
		     read_iterator < 128;
		     read_iterator++ )
		{
			if( volume_offset >= volume_size )
			{
				break;
			}
			if( libvshadow_store_read_buffer_at_offset(
			     store,
			     buffer,
			     497,
			     volume_offset,
			     NULL ) == -1 )
			{
				goto on_error_libvshadow_store;
			}
			volume_offset += 497;
		}
on_error_libvshadow_store:
		libvshadow_store_free(
		 &store,
		 NULL );
	}
	libvshadow_volume_close(
	 volume,
	 NULL );

on_error_libvshadow_volume:
	libvshadow_volume_free(
	 &volume,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */

