/*
 * Library block_descriptor type test program
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

#include "../libvshadow/libvshadow_block_descriptor.h"

uint8_t vshadow_test_block_descriptor_data[ 32 ] = {
	0x00, 0x80, 0xfc, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x2c, 0x7e, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00
};

uint8_t vshadow_test_block_descriptor_empty_data[ 32 ] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

uint8_t vshadow_test_block_descriptor_error_data[ 32 ] = {
	0x00, 0x80, 0xfc, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x2c, 0x7e, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00
};

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

/* Tests the libvshadow_block_descriptor_initialize function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_descriptor_initialize(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_block_descriptor_t *block_descriptor = NULL;
	int result                                      = 0;

#if defined( HAVE_VSHADOW_TEST_MEMORY )
	int number_of_malloc_fail_tests                 = 1;
	int number_of_memset_fail_tests                 = 1;
	int test_number                                 = 0;
#endif

	/* Test regular cases
	 */
	result = libvshadow_block_descriptor_initialize(
	          &block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block_descriptor",
	 block_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_descriptor_free(
	          &block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "block_descriptor",
	 block_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_block_descriptor_initialize(
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

	block_descriptor = (libvshadow_block_descriptor_t *) 0x12345678UL;

	result = libvshadow_block_descriptor_initialize(
	          &block_descriptor,
	          &error );

	block_descriptor = NULL;

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
		/* Test libvshadow_block_descriptor_initialize with malloc failing
		 */
		vshadow_test_malloc_attempts_before_fail = test_number;

		result = libvshadow_block_descriptor_initialize(
		          &block_descriptor,
		          &error );

		if( vshadow_test_malloc_attempts_before_fail != -1 )
		{
			vshadow_test_malloc_attempts_before_fail = -1;

			if( block_descriptor != NULL )
			{
				libvshadow_block_descriptor_free(
				 &block_descriptor,
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
			 "block_descriptor",
			 block_descriptor );

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
		/* Test libvshadow_block_descriptor_initialize with memset failing
		 */
		vshadow_test_memset_attempts_before_fail = test_number;

		result = libvshadow_block_descriptor_initialize(
		          &block_descriptor,
		          &error );

		if( vshadow_test_memset_attempts_before_fail != -1 )
		{
			vshadow_test_memset_attempts_before_fail = -1;

			if( block_descriptor != NULL )
			{
				libvshadow_block_descriptor_free(
				 &block_descriptor,
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
			 "block_descriptor",
			 block_descriptor );

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
	if( block_descriptor != NULL )
	{
		libvshadow_block_descriptor_free(
		 &block_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_block_descriptor_free function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_descriptor_free(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_block_descriptor_t *block_descriptor = NULL;
	int result                                      = 0;

	/* Test regular cases
	 */
	result = libvshadow_block_descriptor_initialize(
	          &block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block_descriptor",
	 block_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_descriptor_initialize(
	          &( block_descriptor->overlay ),
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block_descriptor->overlay",
	 block_descriptor->overlay );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_descriptor_free(
	          &block_descriptor,
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
	result = libvshadow_block_descriptor_free(
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

/* TODO cause free of overlay to fail */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( block_descriptor != NULL )
	{
		libvshadow_block_descriptor_free(
		 &block_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_block_descriptor_free_reverse function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_descriptor_free_reverse(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_block_descriptor_t *block_descriptor = NULL;
	int result                                      = 0;

	/* Test regular cases
	 */
	result = libvshadow_block_descriptor_initialize(
	          &block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block_descriptor",
	 block_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_descriptor_initialize(
	          &( block_descriptor->overlay ),
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block_descriptor->overlay",
	 block_descriptor->overlay );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_descriptor_free_reverse(
	          &block_descriptor,
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
	result = libvshadow_block_descriptor_free_reverse(
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
	if( block_descriptor != NULL )
	{
		libvshadow_block_descriptor_free(
		 &block_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_block_descriptor_clone function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_descriptor_clone(
     void )
{
	libcerror_error_t *error                                    = NULL;
	libvshadow_block_descriptor_t *destination_block_descriptor = NULL;
	libvshadow_block_descriptor_t *source_block_descriptor      = NULL;
	int result                                                  = 0;

#if defined( HAVE_VSHADOW_TEST_MEMORY )
#if defined( OPTIMIZATION_DISABLED )
	int number_of_memcpy_fail_tests                             = 1;
#endif
	int number_of_malloc_fail_tests                             = 1;
	int test_number                                             = 0;
#endif

	/* Initialize test
	 */
	result = libvshadow_block_descriptor_initialize(
	          &source_block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "source_block_descriptor",
	 source_block_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvshadow_block_descriptor_clone(
	          &destination_block_descriptor,
	          source_block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "destination_block_descriptor",
	 destination_block_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_descriptor_free(
	          &destination_block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "destination_block_descriptor",
	 destination_block_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_descriptor_clone(
	          &destination_block_descriptor,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "destination_block_descriptor",
	 destination_block_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_block_descriptor_clone(
	          NULL,
	          source_block_descriptor,
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

	destination_block_descriptor = (libvshadow_block_descriptor_t *) 0x12345678UL;

	result = libvshadow_block_descriptor_clone(
	          &destination_block_descriptor,
	          source_block_descriptor,
	          &error );

	destination_block_descriptor = NULL;

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
		/* Test libvshadow_block_descriptor_clone with malloc failing
		 */
		vshadow_test_malloc_attempts_before_fail = test_number;

		result = libvshadow_block_descriptor_clone(
		          &destination_block_descriptor,
		          source_block_descriptor,
		          &error );

		if( vshadow_test_malloc_attempts_before_fail != -1 )
		{
			vshadow_test_malloc_attempts_before_fail = -1;

			if( destination_block_descriptor != NULL )
			{
				libvshadow_block_descriptor_free(
				 &destination_block_descriptor,
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
			 "destination_block_descriptor",
			 destination_block_descriptor );

			VSHADOW_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#if defined( OPTIMIZATION_DISABLED )

	for( test_number = 0;
	     test_number < number_of_memcpy_fail_tests;
	     test_number++ )
	{
		/* Test libvshadow_block_descriptor_clone with memcpy failing
		 */
		vshadow_test_memcpy_attempts_before_fail = 0;

		result = libvshadow_block_descriptor_clone(
		          &destination_block_descriptor,
		          source_block_descriptor,
		          &error );

		if( vshadow_test_memcpy_attempts_before_fail != -1 )
		{
			vshadow_test_memcpy_attempts_before_fail = -1;

			if( destination_block_descriptor != NULL )
			{
				libvshadow_block_descriptor_free(
				 &destination_block_descriptor,
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
			 "destination_block_descriptor",
			 destination_block_descriptor );

			VSHADOW_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( OPTIMIZATION_DISABLED ) */

/* TODO cause libvshadow_block_descriptor_clone of overlay to fail */

#endif /* defined( HAVE_VSHADOW_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libvshadow_block_descriptor_free(
	          &source_block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "source_block_descriptor",
	 source_block_descriptor );

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
	if( destination_block_descriptor != NULL )
	{
		libvshadow_block_descriptor_free(
		 &destination_block_descriptor,
		 NULL );
	}
	if( source_block_descriptor != NULL )
	{
		libvshadow_block_descriptor_free(
		 &source_block_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_block_descriptor_read_data function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_descriptor_read_data(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_block_descriptor_t *block_descriptor = NULL;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libvshadow_block_descriptor_initialize(
	          &block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block_descriptor",
	 block_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvshadow_block_descriptor_read_data(
	          block_descriptor,
	          vshadow_test_block_descriptor_data,
	          32,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_descriptor_read_data(
	          block_descriptor,
	          vshadow_test_block_descriptor_empty_data,
	          32,
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
	result = libvshadow_block_descriptor_read_data(
	          NULL,
	          vshadow_test_block_descriptor_data,
	          32,
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

	result = libvshadow_block_descriptor_read_data(
	          block_descriptor,
	          NULL,
	          32,
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

	result = libvshadow_block_descriptor_read_data(
	          block_descriptor,
	          vshadow_test_block_descriptor_data,
	          31,
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

	result = libvshadow_block_descriptor_read_data(
	          block_descriptor,
	          vshadow_test_block_descriptor_data,
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

	/* Test error case where forwarder flag is set and offset is not 0
	 */
	result = libvshadow_block_descriptor_read_data(
	          block_descriptor,
	          vshadow_test_block_descriptor_error_data,
	          32,
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
	result = libvshadow_block_descriptor_free(
	          &block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "block_descriptor",
	 block_descriptor );

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
	if( block_descriptor != NULL )
	{
		libvshadow_block_descriptor_free(
		 &block_descriptor,
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
	 "libvshadow_block_descriptor_initialize",
	 vshadow_test_block_descriptor_initialize );

	VSHADOW_TEST_RUN(
	 "libvshadow_block_descriptor_free",
	 vshadow_test_block_descriptor_free );

	VSHADOW_TEST_RUN(
	 "libvshadow_block_descriptor_free_reverse",
	 vshadow_test_block_descriptor_free_reverse );

	VSHADOW_TEST_RUN(
	 "libvshadow_block_descriptor_clone",
	 vshadow_test_block_descriptor_clone );

	VSHADOW_TEST_RUN(
	 "libvshadow_block_descriptor_read_data",
	 vshadow_test_block_descriptor_read_data );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */
}

