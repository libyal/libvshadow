/*
 * Library seek testing program
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
#include <file_stream.h>
#include <system_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vshadow_test_libcerror.h"
#include "vshadow_test_libcsystem.h"
#include "vshadow_test_libvshadow.h"
#include "vshadow_test_unused.h"

/* Define to make vshadow_test_seek generate verbose output
#define VSHADOW_TEST_SEEK_VERBOSE
 */

/* Tests libvshadow_store_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vshadow_test_seek_offset(
     libvshadow_store_t *store,
     off64_t input_offset,
     int input_whence,
     off64_t output_offset )
{
	libcerror_error_t *error  = NULL;
	const char *whence_string = NULL;
	off64_t result_offset     = 0;
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
	 "Testing seek of offset: %" PRIi64 " and whence: %s\t",
	 input_offset,
	 whence_string );

	result_offset = libvshadow_store_seek_offset(
	                 store,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( result_offset == output_offset )
	{
		result = 1;
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

	if( error != NULL )
	{
		if( result != 1 )
		{
			libcerror_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Tests seeking in a store
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vshadow_test_seek(
     libvshadow_store_t *store,
     size64_t volume_size )
{
	int result = 0;

	if( store == NULL )
	{
		return( -1 );
	}
	if( volume_size > (size64_t) INT64_MAX )
	{
		fprintf(
		 stderr,
		 "Volume size exceeds maximum.\n" );

		return( -1 );
	}
	/* Test: SEEK_SET offset: 0
	 * Expected result: 0
	 */
	result = vshadow_test_seek_offset(
	          store,
	          0,
	          SEEK_SET,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <volume_size>
	 * Expected result: <volume_size>
	 */
	result = vshadow_test_seek_offset(
	          store,
	          (off64_t) volume_size,
	          SEEK_SET,
	          (off64_t) volume_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <volume_size / 5>
	 * Expected result: <volume_size / 5>
	 */
	result = vshadow_test_seek_offset(
	          store,
	          (off64_t) ( volume_size / 5 ),
	          SEEK_SET,
	          (off64_t) ( volume_size / 5 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <volume_size + 987>
	 * Expected result: <volume_size + 987>
	 */
	result = vshadow_test_seek_offset(
	          store,
	          (off64_t) ( volume_size + 987 ),
	          SEEK_SET,
	          (off64_t) ( volume_size + 987 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: -987
	 * Expected result: -1
	 */
	result = vshadow_test_seek_offset(
	          store,
	          -987,
	          SEEK_SET,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: 0
	 * Expected result: <volume_size + 987>
	 */
	result = vshadow_test_seek_offset(
	          store,
	          0,
	          SEEK_CUR,
	          (off64_t) ( volume_size + 987 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <-1 * (volume_size + 987)>
	 * Expected result: 0
	 */
	result = vshadow_test_seek_offset(
	          store,
	          -1 * (off64_t) ( volume_size + 987 ),
	          SEEK_CUR,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <volume_size / 3>
	 * Expected result: <volume_size / 3>
	 */
	result = vshadow_test_seek_offset(
	          store,
	          (off64_t) ( volume_size / 3 ),
	          SEEK_CUR,
	          (off64_t) ( volume_size / 3 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	if( volume_size == 0 )
	{
		/* Test: SEEK_CUR offset: <-2 * (volume_size / 3)>
		 * Expected result: 0
		 */
		result = vshadow_test_seek_offset(
		          store,
		          -2 * (off64_t) ( volume_size / 3 ),
		          SEEK_CUR,
		          0 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: SEEK_CUR offset: <-2 * (volume_size / 3)>
		 * Expected result: -1
		 */
		result = vshadow_test_seek_offset(
		          store,
		          -2 * (off64_t) ( volume_size / 3 ),
		          SEEK_CUR,
		          -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	/* Test: SEEK_END offset: 0
	 * Expected result: <volume_size>
	 */
	result = vshadow_test_seek_offset(
	          store,
	          0,
	          SEEK_END,
	          (off64_t) volume_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * volume_size>
	 * Expected result: 0
	 */
	result = vshadow_test_seek_offset(
	          store,
	          -1 * (off64_t) volume_size,
	          SEEK_END,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (volume_size / 4)>
	 * Expected result: <volume_size - (volume_size / 4)>
	 */
	result = vshadow_test_seek_offset(
	          store,
	          -1 * (off64_t) ( volume_size / 4 ),
	          SEEK_END,
	          (off64_t) volume_size - (off64_t) ( volume_size / 4 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: 542
	 * Expected result: <volume_size + 542>
	 */
	result = vshadow_test_seek_offset(
	          store,
	          542,
	          SEEK_END,
	          (off64_t) ( volume_size + 542 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (volume_size + 542)>
	 * Expected result: -1
	 */
	result = vshadow_test_seek_offset(
	          store,
	          -1 * (off64_t) ( volume_size + 542 ),
	          SEEK_END,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: UNKNOWN (88) offset: 0
	 * Expected result: -1
	 */
	result = vshadow_test_seek_offset(
	          store,
	          0,
	          88,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	return( result );
}

/* Tests seeking in a volume
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vshadow_test_seek_volume(
     system_character_t *source,
     libcerror_error_t **error )
{
	libvshadow_store_t *store   = NULL;
	libvshadow_volume_t *volume = NULL;
	size64_t volume_size        = 0;
	int number_of_stores        = 0;
	int result                  = 0;
	int store_index             = 0;

	if( libvshadow_volume_initialize(
	     &volume,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create volume.\n" );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libvshadow_volume_open_wide(
	     volume,
	     source,
	     LIBVSHADOW_OPEN_READ,
	     error ) != 1 )
#else
	if( libvshadow_volume_open(
	     volume,
	     source,
	     LIBVSHADOW_OPEN_READ,
	     error ) != 1 )
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
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve number of stores.\n" );

		goto on_error;
	}
	for( store_index = number_of_stores - 1;
	     store_index >= 0;
	     store_index-- )
	{
		if( libvshadow_volume_get_store(
		     volume,
		     store_index,
		     &store,
		     error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to retrieve store: %d.\n",
			 store_index );

			goto on_error;
		}
		if( libvshadow_store_get_volume_size(
		     store,
		     &volume_size,
		     error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to retrieve volume size.\n" );

			goto on_error;
		}
		fprintf(
		 stdout,
		 "Store: %d volume size: %" PRIu64 " bytes\n",
		 store_index,
		 volume_size );

		result = vshadow_test_seek(
		          store,
		          volume_size );

		if( result == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to seek in store: %d.\n",
			 store_index );

			goto on_error;
		}
		if( libvshadow_store_free(
		     &store,
		     error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to free store: %d.\n",
			 store_index );

			goto on_error;
		}
		if( result == 0 )
		{
			break;
		}
	}
	if( libvshadow_volume_close(
	     volume,
	     error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close volume.\n" );

		goto on_error;
	}
	if( libvshadow_volume_free(
	     &volume,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free volume.\n" );

		goto on_error;
	}
	return( result );

on_error:
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
	return( -1 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error   = NULL;
	system_character_t *source = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file or device.\n" );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

#if defined( HAVE_DEBUG_OUTPUT ) && defined( VSHADOW_TEST_SEEK_VERBOSE )
	libvshadow_notify_set_verbose(
	 1 );
	libvshadow_notify_set_stream(
	 stderr,
	 NULL );
#endif
	result = vshadow_test_seek_volume(
	          source,
	          &error );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek in volume.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );
		libcerror_error_free(
		 &error );
	}
	return( EXIT_FAILURE );
}

