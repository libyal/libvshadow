/*
 * OSS-Fuzz target for the libvshadow store read-buffer (data) path
 *
 * The existing volume_fuzzer only opens and closes the volume, so the
 * per-store block descriptor / diff-area reconstruction logic is never
 * reached. This target additionally enumerates the stores and reads their
 * data so the store reconstruction parsers are exercised.
 */

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libvshadow.h"

#if !defined( LIBVSHADOW_HAVE_BFIO )

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
	libbfio_handle_t *file_io_handle = NULL;
	libvshadow_volume_t *volume      = NULL;
	libvshadow_store_t *store        = NULL;
	int number_of_stores             = 0;
	int store_index                  = 0;

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
		goto on_error_libvshadow;
	}
	if( libvshadow_volume_get_number_of_stores(
	     volume,
	     &number_of_stores,
	     NULL ) != 1 )
	{
		goto on_error_close;
	}
	/* Cap the number of stores examined to bound run time. */
	if( number_of_stores > 16 )
	{
		number_of_stores = 16;
	}
	for( store_index = 0;
	     store_index < number_of_stores;
	     store_index++ )
	{
		if( libvshadow_volume_get_store(
		     volume,
		     store_index,
		     &store,
		     NULL ) != 1 )
		{
			continue;
		}
		/* Read the store to drive the block descriptor reconstruction. */
		{
			size64_t store_size = 0;

			if( libvshadow_store_get_size(
			     store,
			     &store_size,
			     NULL ) == 1 )
			{
				uint8_t buffer[ 4096 ];
				off64_t offset = 0;
				int iterations = 0;

				while( ( offset < (off64_t) store_size )
				    && ( iterations < 1024 ) )
				{
					ssize_t read_count = libvshadow_store_read_buffer_at_offset(
					                      store,
					                      buffer,
					                      sizeof( buffer ),
					                      offset,
					                      NULL );

					if( read_count <= 0 )
					{
						break;
					}
					offset += read_count;
					iterations++;
				}
			}
		}
		libvshadow_store_free(
		 &store,
		 NULL );
	}
on_error_close:
	libvshadow_volume_close(
	 volume,
	 NULL );

on_error_libvshadow:
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
