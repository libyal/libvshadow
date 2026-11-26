/*
 * Library volume type test program
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

#include <common.h>
#include <byte_stream.h>
#include <file_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vshadow_test_functions.h"
#include "vshadow_test_getopt.h"
#include "vshadow_test_libbfio.h"
#include "vshadow_test_libcerror.h"
#include "vshadow_test_libvshadow.h"
#include "vshadow_test_macros.h"
#include "vshadow_test_memory.h"

#include "../libvshadow/libvshadow_definitions.h"
#include "../libvshadow/libvshadow_io_handle.h"
#include "../libvshadow/libvshadow_ntfs_volume_header.h"
#include "../libvshadow/libvshadow_volume.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make vshadow_test_volume generate verbose output
#define VSHADOW_TEST_VOLUME_VERBOSE
 */

#if !defined( LIBVSHADOW_HAVE_BFIO )

LIBVSHADOW_EXTERN \
int libvshadow_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBVSHADOW_EXTERN \
int libvshadow_volume_open_file_io_handle(
     libvshadow_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvshadow_error_t **error );

#endif /* !defined( LIBVSHADOW_HAVE_BFIO ) */

/* Creates and opens a source volume
 * Returns 1 if successful or -1 on error
 */
int vshadow_test_volume_open_source(
     libvshadow_volume_t **volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "vshadow_test_volume_open_source";
	int result            = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
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
	if( libvshadow_volume_initialize(
	     volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize volume.",
		 function );

		goto on_error;
	}
	result = libvshadow_volume_open_file_io_handle(
	          *volume,
	          file_io_handle,
	          LIBVSHADOW_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *volume != NULL )
	{
		libvshadow_volume_free(
		 volume,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source volume
 * Returns 1 if successful or -1 on error
 */
int vshadow_test_volume_close_source(
     libvshadow_volume_t **volume,
     libcerror_error_t **error )
{
	static char *function = "vshadow_test_volume_close_source";
	int result            = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	if( libvshadow_volume_close(
	     *volume,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close volume.",
		 function );

		result = -1;
	}
	if( libvshadow_volume_free(
	     volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free volume.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libvshadow_volume_initialize function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libvshadow_volume_t *volume     = NULL;
	int result                      = 0;

#if defined( HAVE_VSHADOW_TEST_MEMORY )
	int number_of_malloc_fail_tests = 4;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libvshadow_volume_initialize(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_volume_free(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_volume_initialize(
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	volume = (libvshadow_volume_t *) 0x12345678UL;

	result = libvshadow_volume_initialize(
	          &volume,
	          &error );

	volume = NULL;

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSHADOW_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvshadow_volume_initialize with malloc failing
		 */
		vshadow_test_malloc_attempts_before_fail = test_number;

		result = libvshadow_volume_initialize(
		          &volume,
		          &error );

		if( vshadow_test_malloc_attempts_before_fail != -1 )
		{
			vshadow_test_malloc_attempts_before_fail = -1;

			if( volume != NULL )
			{
				libvshadow_volume_free(
				 &volume,
				 NULL );
			}
		}
		else
		{
			VSHADOW_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSHADOW_TEST_ASSERT_IS_NULL(
			 "volume",
			 volume );

			VSHADOW_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libvshadow_volume_initialize with memset failing
		 */
		vshadow_test_memset_attempts_before_fail = test_number;

		result = libvshadow_volume_initialize(
		          &volume,
		          &error );

		if( vshadow_test_memset_attempts_before_fail != -1 )
		{
			vshadow_test_memset_attempts_before_fail = -1;

			if( volume != NULL )
			{
				libvshadow_volume_free(
				 &volume,
				 NULL );
			}
		}
		else
		{
			VSHADOW_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSHADOW_TEST_ASSERT_IS_NULL(
			 "volume",
			 volume );

			VSHADOW_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_VSHADOW_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvshadow_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_volume_free function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvshadow_volume_free(
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvshadow_volume_open function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error    = NULL;
	libvshadow_volume_t *volume = NULL;
	int result                  = 0;

	/* Initialize test
	 */
	result = vshadow_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_volume_initialize(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvshadow_volume_open(
	          volume,
	          narrow_source,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_volume_open(
	          NULL,
	          narrow_source,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open(
	          volume,
	          NULL,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open(
	          volume,
	          narrow_source,
	          -1,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open(
	          volume,
	          narrow_source,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open(
	          volume,
	          narrow_source,
	          LIBVSHADOW_ACCESS_FLAG_WRITE,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libvshadow_volume_open(
	          volume,
	          narrow_source,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libvshadow_volume_free(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvshadow_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libvshadow_volume_open_wide function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error    = NULL;
	libvshadow_volume_t *volume = NULL;
	int result                  = 0;

	/* Initialize test
	 */
	result = vshadow_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_volume_initialize(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvshadow_volume_open_wide(
	          volume,
	          wide_source,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_volume_open_wide(
	          NULL,
	          wide_source,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open_wide(
	          volume,
	          NULL,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open_wide(
	          volume,
	          wide_source,
	          -1,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open_wide(
	          volume,
	          wide_source,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open_wide(
	          volume,
	          wide_source,
	          LIBVSHADOW_ACCESS_FLAG_WRITE,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libvshadow_volume_open_wide(
	          volume,
	          wide_source,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libvshadow_volume_free(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvshadow_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libvshadow_volume_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libvshadow_volume_t *volume      = NULL;
	size_t string_length             = 0;
	int result                       = 0;

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "source",
	 source );

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_volume_initialize(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvshadow_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_volume_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open_file_io_handle(
	          volume,
	          NULL,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          -1,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          LIBVSHADOW_ACCESS_FLAG_WRITE,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libvshadow_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libvshadow_volume_free(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "file_io_handle",
	 file_io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvshadow_volume_free(
		 &volume,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_volume_close function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_close(
     void )
{
	libcerror_error_t *error    = NULL;
	libvshadow_volume_t *volume = NULL;
	int result                  = 0;

	/* Test error cases
	 */
	result = libvshadow_volume_close(
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test closing an unopened volume
	 */
	result = libvshadow_volume_initialize(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_volume_close(
	          volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_free(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvshadow_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_volume_open and libvshadow_volume_close functions
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error    = NULL;
	libvshadow_volume_t *volume = NULL;
	int result                  = 0;

	/* Initialize test
	 */
	result = libvshadow_volume_initialize(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvshadow_volume_open_wide(
	          volume,
	          source,
	          LIBVSHADOW_OPEN_READ,
	          &error );
#else
	result = libvshadow_volume_open(
	          volume,
	          source,
	          LIBVSHADOW_OPEN_READ,
	          &error );
#endif

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_volume_close(
	          volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvshadow_volume_open_wide(
	          volume,
	          source,
	          LIBVSHADOW_OPEN_READ,
	          &error );
#else
	result = libvshadow_volume_open(
	          volume,
	          source,
	          LIBVSHADOW_OPEN_READ,
	          &error );
#endif

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_volume_close(
	          volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libvshadow_volume_free(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvshadow_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_volume_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_signal_abort(
     libvshadow_volume_t *volume )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_volume_signal_abort(
	          volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_volume_signal_abort(
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvshadow_volume_get_size function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_get_size(
     libvshadow_volume_t *volume )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_volume_get_size(
	          volume,
	          &size,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_volume_get_size(
	          NULL,
	          &size,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_get_size(
	          volume,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvshadow_volume_get_number_of_stores function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_get_number_of_stores(
     libvshadow_volume_t *volume )
{
	libcerror_error_t *error = NULL;
	int number_of_stores     = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_volume_get_number_of_stores(
	          volume,
	          &number_of_stores,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_volume_get_number_of_stores(
	          NULL,
	          &number_of_stores,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_get_number_of_stores(
	          volume,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvshadow_volume_get_store function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_get_store(
     libvshadow_volume_t *volume )
{
	libcerror_error_t *error  = NULL;
	libvshadow_store_t *store = NULL;
	int result                = 0;

	/* Test regular cases
	 */
	result = libvshadow_volume_get_store(
	          volume,
	          0,
	          &store,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "store",
	 store );

	/* Test error case where *store is already set
	 */
	result = libvshadow_volume_get_store(
	          volume,
	          0,
	          &store,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_free(
	          &store,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_volume_get_store(
	          NULL,
	          0,
	          &store,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "store",
	 store );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_get_store(
	          volume,
	          -1,
	          &store,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "store",
	 store );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_get_store(
	          volume,
	          0,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "store",
	 store );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( store != NULL )
	{
		libvshadow_store_free(
		 &store,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_volume_get_store_identifier function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_get_store_identifier(
     libvshadow_volume_t *volume )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_volume_get_store_identifier(
	          volume,
	          0,
	          guid_data,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_volume_get_store_identifier(
	          NULL,
	          0,
	          guid_data,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_get_store_identifier(
	          volume,
	          -1,
	          guid_data,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_get_store_identifier(
	          volume,
	          0,
	          NULL,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_get_store_identifier(
	          volume,
	          0,
	          guid_data,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_get_store_identifier(
	          volume,
	          0,
	          guid_data,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

/* Helper to populate a valid 512-byte NTFS volume header buffer
 */
static void vshadow_test_volume_fill_ntfs_header(
             uint8_t *header_data,
             uint16_t bytes_per_sector,
             uint8_t sectors_per_cluster,
             uint64_t total_sectors,
             uint32_t mft_entry_size,
             uint32_t index_entry_size )
{
	memory_set(
	 header_data,
	 0,
	 512 );

	memory_copy(
	 &( header_data[ 3 ] ),
	 "NTFS    ",
	 8 );

	byte_stream_copy_from_uint16_little_endian(
	 &( header_data[ 11 ] ),
	 bytes_per_sector );

	header_data[ 13 ] = sectors_per_cluster;

	byte_stream_copy_from_uint64_little_endian(
	 &( header_data[ 40 ] ),
	 total_sectors );

	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 64 ] ),
	 mft_entry_size );

	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 68 ] ),
	 index_entry_size );

	header_data[ 510 ] = 0x55;
	header_data[ 511 ] = 0xaa;
}

/* Tests the libvshadow_ntfs_volume_header functions
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_ntfs_volume_header(
     void )
{
	uint8_t header_data[ 512 ];

	libbfio_handle_t *file_io_handle                    = NULL;
	libcerror_error_t *error                            = NULL;
	libvshadow_ntfs_volume_header_t *ntfs_volume_header = NULL;
	int result                                          = 0;

#if defined( HAVE_VSHADOW_TEST_MEMORY )
	int number_of_malloc_fail_tests                     = 1;
	int number_of_memset_fail_tests                     = 1;
	int test_number                                     = 0;
#endif

	/* Test initialize and free
	 */
	result = libvshadow_ntfs_volume_header_initialize(
	          &ntfs_volume_header,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "ntfs_volume_header",
	 ntfs_volume_header );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_ntfs_volume_header_free(
	          &ntfs_volume_header,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "ntfs_volume_header",
	 ntfs_volume_header );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test initialize & free error cases
	 */
	result = libvshadow_ntfs_volume_header_initialize(
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	ntfs_volume_header = (libvshadow_ntfs_volume_header_t *) 0x12345678UL;

	result = libvshadow_ntfs_volume_header_initialize(
	          &ntfs_volume_header,
	          &error );

	ntfs_volume_header = NULL;

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_ntfs_volume_header_free(
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSHADOW_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		vshadow_test_malloc_attempts_before_fail = test_number;

		result = libvshadow_ntfs_volume_header_initialize(
		          &ntfs_volume_header,
		          &error );

		if( vshadow_test_malloc_attempts_before_fail != -1 )
		{
			vshadow_test_malloc_attempts_before_fail = -1;

			if( ntfs_volume_header != NULL )
			{
				libvshadow_ntfs_volume_header_free(
				 &ntfs_volume_header,
				 NULL );
			}
		}
		else
		{
			VSHADOW_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSHADOW_TEST_ASSERT_IS_NULL(
			 "ntfs_volume_header",
			 ntfs_volume_header );

			VSHADOW_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		vshadow_test_memset_attempts_before_fail = test_number;

		result = libvshadow_ntfs_volume_header_initialize(
		          &ntfs_volume_header,
		          &error );

		if( vshadow_test_memset_attempts_before_fail != -1 )
		{
			vshadow_test_memset_attempts_before_fail = -1;

			if( ntfs_volume_header != NULL )
			{
				libvshadow_ntfs_volume_header_free(
				 &ntfs_volume_header,
				 NULL );
			}
		}
		else
		{
			VSHADOW_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSHADOW_TEST_ASSERT_IS_NULL(
			 "ntfs_volume_header",
			 ntfs_volume_header );

			VSHADOW_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_VSHADOW_TEST_MEMORY ) */

	result = libvshadow_ntfs_volume_header_initialize(
	          &ntfs_volume_header,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test read_data with standard values (cluster=8*512, mft=246 -> 1024, index=1 -> 4096)
	 */
	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 8,
	 1023,
	 246,
	 1 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT64(
	 "volume_size",
	 ntfs_volume_header->volume_size,
	 (uint64_t) ( 1024 * 512 ) );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test read_data with negative-power sectors_per_cluster (>128), positive mft_entry_size (<128),
	 * and negative-power index_entry_size (>=128)
	 */
	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 253,
	 1023,
	 1,
	 244 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test read_data error cases
	 */
	result = libvshadow_ntfs_volume_header_read_data(
	          NULL,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          NULL,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          511,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Bad file system signature
	 */
	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 8,
	 1023,
	 246,
	 1 );
	header_data[ 3 ] = 'X';

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Unsupported bytes_per_sector
	 */
	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 128,
	 8,
	 1023,
	 246,
	 1 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Cluster block size shift out of bounds (>128, 256 - val > 12)
	 */
	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 200,
	 1023,
	 246,
	 1 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Unsupported cluster block size (3 * 512 = 1536)
	 */
	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 3,
	 1023,
	 246,
	 1 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Unsupported MFT entry size (0 and >255)
	 */
	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 8,
	 1023,
	 0,
	 1 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 8,
	 1023,
	 256,
	 1 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* MFT entry size shift >= 32 (256 - 200 = 56 >= 32)
	 */
	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 8,
	 1023,
	 200,
	 1 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* MFT entry size < 42 (256 - 251 = 5 -> 32 < 42)
	 */
	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 8,
	 1023,
	 251,
	 1 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Unsupported index entry size (0, >255, shift >= 32, < 32)
	 */
	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 8,
	 1023,
	 246,
	 0 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 8,
	 1023,
	 246,
	 200 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 8,
	 1023,
	 246,
	 252 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Volume size overflow
	 */
	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 8,
	 UINT64_MAX,
	 246,
	 1 );

	result = libvshadow_ntfs_volume_header_read_data(
	          ntfs_volume_header,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test read_file_io_handle
	 */
	vshadow_test_volume_fill_ntfs_header(
	 header_data,
	 512,
	 8,
	 1023,
	 246,
	 1 );

	result = libbfio_memory_range_initialize(
	          &file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_memory_range_set(
	          file_io_handle,
	          header_data,
	          512,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_open(
	          file_io_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_ntfs_volume_header_read_file_io_handle(
	          ntfs_volume_header,
	          file_io_handle,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_ntfs_volume_header_read_file_io_handle(
	          NULL,
	          file_io_handle,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_ntfs_volume_header_read_file_io_handle(
	          ntfs_volume_header,
	          NULL,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	header_data[ 3 ] = 'X';

	result = libvshadow_ntfs_volume_header_read_file_io_handle(
	          ntfs_volume_header,
	          file_io_handle,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libbfio_handle_close(
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_ntfs_volume_header_free(
	          &ntfs_volume_header,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( ntfs_volume_header != NULL )
	{
		libvshadow_ntfs_volume_header_free(
		 &ntfs_volume_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_volume_open_read and libvshadow_volume_open_read_ntfs_volume_headers functions
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_volume_open_read(
     void )
{
	libbfio_handle_t *file_io_handle              = NULL;
	libcerror_error_t *error                      = NULL;
	libvshadow_internal_volume_t *internal_volume = NULL;
	libvshadow_volume_t *volume                   = NULL;
	uint8_t *volume_data                          = NULL;
	size_t volume_data_size                       = 0x10000;
	int result                                    = 0;

	volume_data = (uint8_t *) memory_allocate(
	                           volume_data_size );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "volume_data",
	 volume_data );

	memory_set(
	 volume_data,
	 0,
	 volume_data_size );

	/* Primary NTFS header at 0, backup NTFS header at 0xfe00 (total_sectors = 127 -> volume_size = 0x10000)
	 */
	vshadow_test_volume_fill_ntfs_header(
	 volume_data,
	 512,
	 8,
	 127,
	 246,
	 1 );

	vshadow_test_volume_fill_ntfs_header(
	 &( volume_data[ 0xfe00 ] ),
	 512,
	 8,
	 127,
	 246,
	 1 );

	/* Valid VSS volume header at 0x1e00 with catalog_offset = 0
	 */
	memory_copy(
	 &( volume_data[ 0x1e00 ] ),
	 vshadow_vss_identifier,
	 16 );
	byte_stream_copy_from_uint32_little_endian(
	 &( volume_data[ 0x1e00 + 16 ] ),
	 1 );
	byte_stream_copy_from_uint32_little_endian(
	 &( volume_data[ 0x1e00 + 20 ] ),
	 LIBVSHADOW_RECORD_TYPE_VOLUME_HEADER );

	result = libbfio_memory_range_initialize(
	          &file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_memory_range_set(
	          file_io_handle,
	          volume_data,
	          volume_data_size,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_open(
	          file_io_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_volume_initialize(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	internal_volume = (libvshadow_internal_volume_t *) volume;

	/* Test valid open_read with catalog_offset == 0
	 */
	result = libvshadow_volume_open_read(
	          internal_volume,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT64(
	 "internal_volume->size",
	 internal_volume->size,
	 (uint64_t) volume_data_size );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases: NULL internal_volume, NULL file_io_handle
	 */
	result = libvshadow_volume_open_read(
	          NULL,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open_read(
	          internal_volume,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_volume_open_read_ntfs_volume_headers(
	          NULL,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test error case: mismatched NTFS backup volume size
	 */
	vshadow_test_volume_fill_ntfs_header(
	 &( volume_data[ 0xfe00 ] ),
	 512,
	 8,
	 120,
	 246,
	 1 );

	result = libvshadow_volume_open_read(
	          internal_volume,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test error case: invalid backup NTFS volume header
	 */
	volume_data[ 0xfe00 + 3 ] = 'X';

	result = libvshadow_volume_open_read(
	          internal_volume,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Restore backup header, corrupt primary NTFS header
	 */
	vshadow_test_volume_fill_ntfs_header(
	 &( volume_data[ 0xfe00 ] ),
	 512,
	 8,
	 127,
	 246,
	 1 );
	volume_data[ 3 ] = 'X';

	result = libvshadow_volume_open_read(
	          internal_volume,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Restore primary NTFS header, corrupt VSS volume header
	 */
	volume_data[ 3 ] = 'N';
	volume_data[ 0x1e00 ] ^= 0xff;

	result = libvshadow_volume_open_read(
	          internal_volume,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Restore VSS header, point catalog_offset to invalid catalog block
	 */
	volume_data[ 0x1e00 ] ^= 0xff;
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x1e00 + 48 ] ),
	 0x4000ULL );

	result = libvshadow_volume_open_read(
	          internal_volume,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libvshadow_volume_free(
	          &volume,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_close(
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	memory_free(
	 volume_data );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvshadow_volume_free(
		 &volume,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( volume_data != NULL )
	{
		memory_free(
		 volume_data );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle  = NULL;
	libcerror_error_t *error          = NULL;
	libvshadow_volume_t *volume       = NULL;
	system_character_t *option_offset = NULL;
	system_character_t *source        = NULL;
	system_integer_t option           = 0;
	size_t string_length              = 0;
	off64_t volume_offset             = 0;
	int result                        = 0;

	while( ( option = vshadow_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "o:" ) ) ) != (system_integer_t) -1 )
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

			case (system_integer_t) 'o':
				option_offset = optarg;

				break;
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
	if( option_offset != NULL )
	{
		string_length = system_string_length(
		                 option_offset );

		result = vshadow_test_system_string_copy_from_64_bit_in_decimal(
		          option_offset,
		          string_length + 1,
		          (uint64_t *) &volume_offset,
		          &error );

		VSHADOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        VSHADOW_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( VSHADOW_TEST_VOLUME_VERBOSE )
	libvshadow_notify_set_verbose(
	 1 );
	libvshadow_notify_set_stream(
	 stderr,
	 NULL );
#endif

	VSHADOW_TEST_RUN(
	 "libvshadow_volume_initialize",
	 vshadow_test_volume_initialize );

	VSHADOW_TEST_RUN(
	 "libvshadow_volume_free",
	 vshadow_test_volume_free );

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

	VSHADOW_TEST_RUN(
	 "libvshadow_ntfs_volume_header",
	 vshadow_test_ntfs_volume_header );

	VSHADOW_TEST_RUN(
	 "libvshadow_volume_open_read",
	 vshadow_test_volume_open_read );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_range_initialize(
		          &file_io_handle,
		          &error );

		VSHADOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	         "file_io_handle",
	         file_io_handle );

	        VSHADOW_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_range_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_range_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		VSHADOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        VSHADOW_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libbfio_file_range_set(
		          file_io_handle,
		          volume_offset,
		          0,
		          &error );

		VSHADOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        VSHADOW_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libvshadow_check_volume_signature_file_io_handle(
		          file_io_handle,
		          &error );

		VSHADOW_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSHADOW_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( ( result != 0 )
	 && ( volume_offset == 0 ) )
	{
		VSHADOW_TEST_RUN_WITH_ARGS(
		 "libvshadow_volume_open",
		 vshadow_test_volume_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		VSHADOW_TEST_RUN_WITH_ARGS(
		 "libvshadow_volume_open_wide",
		 vshadow_test_volume_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		VSHADOW_TEST_RUN_WITH_ARGS(
		 "libvshadow_volume_open_file_io_handle",
		 vshadow_test_volume_open_file_io_handle,
		 source );

		VSHADOW_TEST_RUN(
		 "libvshadow_volume_close",
		 vshadow_test_volume_close );

		VSHADOW_TEST_RUN_WITH_ARGS(
		 "libvshadow_volume_open_close",
		 vshadow_test_volume_open_close,
		 source );

	}
	if( result != 0 )
	{
		/* Initialize volume for tests
		 */
		result = vshadow_test_volume_open_source(
		          &volume,
		          file_io_handle,
		          &error );

		VSHADOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSHADOW_TEST_ASSERT_IS_NOT_NULL(
		 "volume",
		 volume );

		VSHADOW_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		VSHADOW_TEST_RUN_WITH_ARGS(
		 "libvshadow_volume_signal_abort",
		 vshadow_test_volume_signal_abort,
		 volume );

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

		/* TODO: add tests for libvshadow_volume_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

		VSHADOW_TEST_RUN_WITH_ARGS(
		 "libvshadow_volume_get_size",
		 vshadow_test_volume_get_size,
		 volume );

		VSHADOW_TEST_RUN_WITH_ARGS(
		 "libvshadow_volume_get_number_of_stores",
		 vshadow_test_volume_get_number_of_stores,
		 volume );

		VSHADOW_TEST_RUN_WITH_ARGS(
		 "libvshadow_volume_get_store",
		 vshadow_test_volume_get_store,
		 volume );

		VSHADOW_TEST_RUN_WITH_ARGS(
		 "libvshadow_volume_get_store_identifier",
		 vshadow_test_volume_get_store_identifier,
		 volume );

		/* Clean up
		 */
		result = vshadow_test_volume_close_source(
		          &volume,
		          &error );

		VSHADOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		VSHADOW_TEST_ASSERT_IS_NULL(
		 "volume",
		 volume );

		VSHADOW_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( file_io_handle != NULL )
	{
		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		VSHADOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSHADOW_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        VSHADOW_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvshadow_volume_free(
		 &volume,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

