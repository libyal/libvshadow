/*
 * Library read testing program
 *
 * Copyright (c) 2011-2013, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "vshadow_test_libcstring.h"
#include "vshadow_test_libvshadow.h"

/* Define to make vshadow_test_read generate verbose output
#define VSHADOW_TEST_READ_VERBOSE
 */

#define VSHADOW_TEST_READ_BUFFER_SIZE	4096

/* Tests libvshadow_store_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vshadow_test_seek_offset(
     libvshadow_store_t *store,
     off64_t input_offset,
     int input_whence,
     off64_t output_offset )
{
	libvshadow_error_t *error = NULL;
	off64_t result_offset     = 0;
	int result                = 0;

	if( store == NULL )
	{
		return( -1 );
	}
	result_offset = libvshadow_store_seek_offset(
	                 store,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( result_offset == -1 )
	{
		libvshadow_error_backtrace_fprint(
		 error,
		 stderr );

		libvshadow_error_free(
		 &error );
	}
	if( result_offset == -1 )
	{
		libvshadow_error_backtrace_fprint(
		 error,
		 stderr );

		libvshadow_error_free(
		 &error );
	}
	if( result_offset != output_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected result offset: %" PRIi64 "\n",
		 result_offset );
	}
	else
	{
		result = 1;
	}
	return( result );
}

/* Tests libvshadow_store_read_buffer
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vshadow_test_read_buffer(
     libvshadow_store_t *store,
     size64_t input_size,
     size64_t output_size )
{
	uint8_t buffer[ VSHADOW_TEST_READ_BUFFER_SIZE ];

	libvshadow_error_t *error = NULL;
	size64_t remaining_size   = 0;
	size64_t result_size      = 0;
	size_t read_size          = 0;
	ssize_t read_count        = 0;
	int result                = 0;

	if( store == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	while( remaining_size > 0 )
	{
		read_size = VSHADOW_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libvshadow_store_read_buffer(
			      store,
			      buffer,
			      read_size,
			      &error );

		if( read_count < 0 )
		{
			libvshadow_error_backtrace_fprint(
			 error,
			 stderr );

			libvshadow_error_free(
			 &error );

			break;
		}
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( output_size == result_size )
	{
		result = 1;
	}
	else
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	return( result );
}

/* Tests reading data at a specific offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vshadow_test_read(
     libvshadow_store_t *store,
     off64_t input_offset,
     int input_whence,
     size64_t input_size,
     off64_t output_offset,
     size64_t output_size )
{
	const char *whence_string = NULL;
	int result                = 0;

	if( store == NULL )
	{
		return( -1 );
	}
	if( input_whence == SEEK_CUR )
	{
		whence_string = "SEEK_CUR";
	}
	else if( input_whence == SEEK_END )
	{
		whence_string = "SEEK_END";
	}
	else if( input_whence == SEEK_SET )
	{
		whence_string = "SEEK_SET";
	}
	else
	{
		whence_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing reading range with offset: %" PRIi64 ", whence: %s and size: %" PRIu64 "\t",
	 input_offset,
	 whence_string,
	 input_size );

	result = vshadow_test_seek_offset(
	          store,
	          input_offset,
	          input_whence,
	          output_offset );

	if( result == 1 )
	{
		if( input_offset >= 0 )
		{
			result = vshadow_test_read_buffer(
				  store,
				  input_size,
				  output_size );
		}
	}
	if( result != 0 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	return( result );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libvshadow_error_t *error   = NULL;
	libvshadow_store_t *store   = NULL;
	libvshadow_volume_t *volume = NULL;
	size64_t volume_size        = 0;
	int number_of_stores        = 0;

	if( argc < 2 )
	{
		fprintf(
		 stderr,
		 "Missing filename.\n" );

		return( EXIT_FAILURE );
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( VSHADOW_TEST_READ_VERBOSE )
	libvshadow_notify_set_verbose(
	 1 );
	libvshadow_notify_set_stream(
	 stderr,
	 NULL );
#endif
	/* Initialization
	 */
	if( libvshadow_volume_initialize(
	     &volume,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create volume.\n" );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libvshadow_volume_open_wide(
	     volume,
	     argv[ 1 ],
	     LIBVSHADOW_OPEN_READ,
	     &error ) != 1 )
#else
	if( libvshadow_volume_open(
	     volume,
	     argv[ 1 ],
	     LIBVSHADOW_OPEN_READ,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to open volume.\n" );

		goto on_error;
	}
	if( libvshadow_volume_get_number_of_stores(
	     volume,
	     &number_of_stores,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve number of stores.\n" );

		goto on_error;
	}
	if( libvshadow_volume_get_store(
	     volume,
	     number_of_stores - 1,
	     &store,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve store: %d.\n",
		 number_of_stores - 1 );

		goto on_error;
	}
	if( libvshadow_volume_get_size(
	     volume,
	     &volume_size,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve volume size.\n" );

		goto on_error;
	}
	if( volume_size > (size64_t) INT64_MAX )
	{
		fprintf(
		 stderr,
		 "Media size exceeds maximum.\n" );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "Media size: %" PRIu64 " bytes\n",
	 volume_size );

	/* Case 0: test full read
	 */

	/* Test: offset: 0 size: <volume_size>
	 * Expected result: offset: 0 size: <volume_size>
	 */
	if( vshadow_test_read(
	     store,
	     0,
	     SEEK_SET,
	     volume_size,
	     0,
	     volume_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}
	/* Test: offset: 0 size: <volume_size>
	 * Expected result: offset: 0 size: <volume_size>
	 */
	if( vshadow_test_read(
	     store,
	     0,
	     SEEK_SET,
	     volume_size,
	     0,
	     volume_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}

	/* Case 1: test random read
	 */

	/* Test: offset: <volume_size / 7> size: <volume_size / 2>
	 * Expected result: offset: <volume_size / 7> size: <volume_size / 2>
	 */
	if( vshadow_test_read(
	     store,
	     (off64_t) ( volume_size / 7 ),
	     SEEK_SET,
	     volume_size / 2,
	     (off64_t) ( volume_size / 7 ),
	     volume_size / 2 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}
	/* Test: offset: <volume_size / 7> size: <volume_size / 2>
	 * Expected result: offset: <volume_size / 7> size: <volume_size / 2>
	 */
	if( vshadow_test_read(
	     store,
	     (off64_t) ( volume_size / 7 ),
	     SEEK_SET,
	     volume_size / 2,
	     (off64_t) ( volume_size / 7 ),
	     volume_size / 2 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}

	/* Case 2: test read beyond volume size
	 */

	if( volume_size < 1024 )
	{
		/* Test: offset: <volume_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		if( vshadow_test_read(
		     store,
		     (off64_t) ( volume_size - 1024 ),
		     SEEK_SET,
		     4096,
		     -1,
		     (size64_t) -1 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			goto on_error;
		}
		/* Test: offset: <volume_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		if( vshadow_test_read(
		     store,
		     (off64_t) ( volume_size - 1024 ),
		     SEEK_SET,
		     4096,
		     -1,
		     (size64_t) -1 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			goto on_error;
		}
	}
	else
	{
		/* Test: offset: <volume_size - 1024> size: 4096
		 * Expected result: offset: <volume_size - 1024> size: 1024
		 */
		if( vshadow_test_read(
		     store,
		     (off64_t) ( volume_size - 1024 ),
		     SEEK_SET,
		     4096,
		     (off64_t) ( volume_size - 1024 ),
		     1024 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			goto on_error;
		}
		/* Test: offset: <volume_size - 1024> size: 4096
		 * Expected result: offset: <volume_size - 1024> size: 1024
		 */
		if( vshadow_test_read(
		     store,
		     (off64_t) ( volume_size - 1024 ),
		     SEEK_SET,
		     4096,
		     (off64_t) ( volume_size - 1024 ),
		     1024 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			goto on_error;
		}
	}
	/* Clean up
	 */
	if( libvshadow_store_free(
	     &store,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free store.\n" );

		goto on_error;
	}
	if( libvshadow_volume_close(
	     volume,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close volume.\n" );

		goto on_error;
	}
	if( libvshadow_volume_free(
	     &volume,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free volume.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libvshadow_error_backtrace_fprint(
		 error,
		 stderr );
		libvshadow_error_free(
		 &error );
	}
	if( store != NULL )
	{
		libvshadow_store_free(
		 &store,
		 NULL );
	}
	if( volume != NULL )
	{
		libvshadow_volume_close(
		 volume,
		 NULL );
		libvshadow_volume_free(
		 &volume,
		 NULL );
	}
	return( EXIT_FAILURE );
}

