/*
 * Library block_range_descriptor type test program
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vshadow_test_libcerror.h"
#include "vshadow_test_libvshadow.h"
#include "vshadow_test_macros.h"
#include "vshadow_test_memory.h"
#include "vshadow_test_unused.h"

#include "../libvshadow/libvshadow_block_range_descriptor.h"

uint8_t vshadow_test_block_range_descriptor_data[ 24 ] = {
	0x00, 0xc0, 0x28, 0x7e, 0x03, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x40, 0xff, 0x55, 0x00, 0x00, 0x00, 0x00
};

uint8_t vshadow_test_block_range_descriptor_empty_data[ 24 ] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

/* Tests the libvshadow_block_range_descriptor_initialize function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_range_descriptor_initialize(
     void )
{
	libcerror_error_t *error                                    = NULL;
	libvshadow_block_range_descriptor_t *block_range_descriptor = NULL;
	int result                                                  = 0;

#if defined( HAVE_VSHADOW_TEST_MEMORY )
	int number_of_malloc_fail_tests                             = 1;
	int number_of_memset_fail_tests                             = 1;
	int test_number                                             = 0;
#endif

	/* Test block_range_descriptor initialization
	 */
	result = libvshadow_block_range_descriptor_initialize(
	          &block_range_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block_range_descriptor",
	 block_range_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_range_descriptor_free(
	          &block_range_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "block_range_descriptor",
	 block_range_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_block_range_descriptor_initialize(
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

	block_range_descriptor = (libvshadow_block_range_descriptor_t *) 0x12345678UL;

	result = libvshadow_block_range_descriptor_initialize(
	          &block_range_descriptor,
	          &error );

	block_range_descriptor = NULL;

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
		/* Test libvshadow_block_range_descriptor_initialize with malloc failing
		 */
		vshadow_test_malloc_attempts_before_fail = test_number;

		result = libvshadow_block_range_descriptor_initialize(
		          &block_range_descriptor,
		          &error );

		if( vshadow_test_malloc_attempts_before_fail != -1 )
		{
			vshadow_test_malloc_attempts_before_fail = -1;

			if( block_range_descriptor != NULL )
			{
				libvshadow_block_range_descriptor_free(
				 &block_range_descriptor,
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
			 "block_range_descriptor",
			 block_range_descriptor );

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
		/* Test libvshadow_block_range_descriptor_initialize with memset failing
		 */
		vshadow_test_memset_attempts_before_fail = test_number;

		result = libvshadow_block_range_descriptor_initialize(
	          &block_range_descriptor,
	          &error );

		if( vshadow_test_memset_attempts_before_fail != -1 )
		{
			vshadow_test_memset_attempts_before_fail = -1;

			if( block_range_descriptor != NULL )
			{
				libvshadow_block_range_descriptor_free(
				 &block_range_descriptor,
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
			 "block_range_descriptor",
			 block_range_descriptor );

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
	if( block_range_descriptor != NULL )
	{
		libvshadow_block_range_descriptor_free(
		 &block_range_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_block_range_descriptor_free function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_range_descriptor_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvshadow_block_range_descriptor_free(
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

/* Tests the libvshadow_block_range_descriptor_read_data function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_range_descriptor_read_data(
     void )
{
	libcerror_error_t *error                                    = NULL;
	libvshadow_block_range_descriptor_t *block_range_descriptor = NULL;
	int result                                                  = 0;

	/* Initialize test
	 */
	result = libvshadow_block_range_descriptor_initialize(
	          &block_range_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block_range_descriptor",
	 block_range_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvshadow_block_range_descriptor_read_data(
	          block_range_descriptor,
	          vshadow_test_block_range_descriptor_data,
	          24,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_range_descriptor_read_data(
	          block_range_descriptor,
	          vshadow_test_block_range_descriptor_empty_data,
	          24,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_block_range_descriptor_read_data(
	          NULL,
	          vshadow_test_block_range_descriptor_data,
	          24,
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

	result = libvshadow_block_range_descriptor_read_data(
	          block_range_descriptor,
	          NULL,
	          24,
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

	result = libvshadow_block_range_descriptor_read_data(
	          block_range_descriptor,
	          vshadow_test_block_range_descriptor_data,
	          23,
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

	result = libvshadow_block_range_descriptor_read_data(
	          block_range_descriptor,
	          vshadow_test_block_range_descriptor_data,
	          (size_t) SSIZE_MAX + 1,
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
	result = libvshadow_block_range_descriptor_free(
	          &block_range_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "block_range_descriptor",
	 block_range_descriptor );

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
	if( block_range_descriptor != NULL )
	{
		libvshadow_block_range_descriptor_free(
		 &block_range_descriptor,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc VSHADOW_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] VSHADOW_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc VSHADOW_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] VSHADOW_TEST_ATTRIBUTE_UNUSED )
#endif
{
	VSHADOW_TEST_UNREFERENCED_PARAMETER( argc )
	VSHADOW_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

	VSHADOW_TEST_RUN(
	 "libvshadow_block_range_descriptor_initialize",
	 vshadow_test_block_range_descriptor_initialize );

	VSHADOW_TEST_RUN(
	 "libvshadow_block_range_descriptor_free",
	 vshadow_test_block_range_descriptor_free );

	VSHADOW_TEST_RUN(
	 "libvshadow_block_range_descriptor_read_data",
	 vshadow_test_block_range_descriptor_read_data );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */
}

