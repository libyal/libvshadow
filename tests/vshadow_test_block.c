/*
 * Library block type test program
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

#include "../libvshadow/libvshadow_block.h"
#include "../libvshadow/libvshadow_block_descriptor.h"

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

/* Tests the libvshadow_block_initialize function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_initialize(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_block_t *block                       = NULL;
	libvshadow_block_descriptor_t *block_descriptor = NULL;
	int result                                      = 0;

#if defined( HAVE_VSHADOW_TEST_MEMORY )
	int number_of_malloc_fail_tests                 = 1;
	int number_of_memset_fail_tests                 = 1;
	int test_number                                 = 0;
#endif

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

	/* Test block initialization
	 */
	result = libvshadow_block_initialize(
	          &block,
	          block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block",
	 block );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_free(
	          &block,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "block",
	 block );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_block_initialize(
	          NULL,
	          block_descriptor,
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

	result = libvshadow_block_initialize(
	          &block,
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

	block = (libvshadow_block_t *) 0x12345678UL;

	result = libvshadow_block_initialize(
	          &block,
	          block_descriptor,
	          &error );

	block = NULL;

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
		/* Test libvshadow_block_initialize with malloc failing
		 */
		vshadow_test_malloc_attempts_before_fail = test_number;

		result = libvshadow_block_initialize(
		          &block,
		          block_descriptor,
		          &error );

		if( vshadow_test_malloc_attempts_before_fail != -1 )
		{
			vshadow_test_malloc_attempts_before_fail = -1;

			if( block != NULL )
			{
				libvshadow_block_free(
				 &block,
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
			 "block",
			 block );

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
		/* Test libvshadow_block_initialize with memset failing
		 */
		vshadow_test_memset_attempts_before_fail = test_number;

		result = libvshadow_block_initialize(
		          &block,
		          block_descriptor,
		          &error );

		if( vshadow_test_memset_attempts_before_fail != -1 )
		{
			vshadow_test_memset_attempts_before_fail = -1;

			if( block != NULL )
			{
				libvshadow_block_free(
				 &block,
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
			 "block",
			 block );

			VSHADOW_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_VSHADOW_TEST_MEMORY ) */

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
	if( block != NULL )
	{
		libvshadow_block_free(
		 &block,
		 NULL );
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

/* Tests the libvshadow_block_free function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvshadow_block_free(
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

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

/* Tests the libvshadow_block_get_original_offset function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_get_original_offset(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_block_t *block                       = NULL;
	libvshadow_block_descriptor_t *block_descriptor = NULL;
	off64_t original_offset                         = 0;
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

	result = libvshadow_block_initialize(
	          &block,
	          block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block",
	 block );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test retrieve original offset
	 */
	result = libvshadow_block_get_original_offset(
	          block,
	          &original_offset,
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
	result = libvshadow_block_get_original_offset(
	          NULL,
	          &original_offset,
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

	result = libvshadow_block_get_original_offset(
	          block,
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

	/* Test error case where internal block descriptor is NULL
	 */
	( (libvshadow_internal_block_t *) block )->block_descriptor = NULL;

	result = libvshadow_block_get_original_offset(
	          block,
	          &original_offset,
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
	result = libvshadow_block_free(
	          &block,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "block",
	 block );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( block != NULL )
	{
		libvshadow_block_free(
		 &block,
		 NULL );
	}
	if( block_descriptor != NULL )
	{
		libvshadow_block_descriptor_free(
		 &block_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_block_get_relative_offset function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_get_relative_offset(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_block_t *block                       = NULL;
	libvshadow_block_descriptor_t *block_descriptor = NULL;
	off64_t relative_offset                         = 0;
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

	result = libvshadow_block_initialize(
	          &block,
	          block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block",
	 block );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test retrieve relative offset
	 */
	result = libvshadow_block_get_relative_offset(
	          block,
	          &relative_offset,
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
	result = libvshadow_block_get_relative_offset(
	          NULL,
	          &relative_offset,
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

	result = libvshadow_block_get_relative_offset(
	          block,
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

	/* Test error case where internal block descriptor is NULL
	 */
	( (libvshadow_internal_block_t *) block )->block_descriptor = NULL;

	result = libvshadow_block_get_relative_offset(
	          block,
	          &relative_offset,
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
	result = libvshadow_block_free(
	          &block,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "block",
	 block );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( block != NULL )
	{
		libvshadow_block_free(
		 &block,
		 NULL );
	}
	if( block_descriptor != NULL )
	{
		libvshadow_block_descriptor_free(
		 &block_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_block_get_offset function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_get_offset(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_block_t *block                       = NULL;
	libvshadow_block_descriptor_t *block_descriptor = NULL;
	off64_t offset                                  = 0;
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

	result = libvshadow_block_initialize(
	          &block,
	          block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block",
	 block );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test retrieve offset
	 */
	result = libvshadow_block_get_offset(
	          block,
	          &offset,
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
	result = libvshadow_block_get_offset(
	          NULL,
	          &offset,
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

	result = libvshadow_block_get_offset(
	          block,
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

	/* Test error case where internal block descriptor is NULL
	 */
	( (libvshadow_internal_block_t *) block )->block_descriptor = NULL;

	result = libvshadow_block_get_offset(
	          block,
	          &offset,
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
	result = libvshadow_block_free(
	          &block,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "block",
	 block );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( block != NULL )
	{
		libvshadow_block_free(
		 &block,
		 NULL );
	}
	if( block_descriptor != NULL )
	{
		libvshadow_block_descriptor_free(
		 &block_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_block_get_values function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_get_values(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_block_t *block                       = NULL;
	libvshadow_block_descriptor_t *block_descriptor = NULL;
	off64_t relative_offset                         = 0;
	off64_t offset                                  = 0;
	off64_t original_offset                         = 0;
	uint32_t bitmap                                 = 0;
	uint32_t flags                                  = 0;
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

	result = libvshadow_block_initialize(
	          &block,
	          block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block",
	 block );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test retrieve values
	 */
	result = libvshadow_block_get_values(
	          block,
	          &original_offset,
	          &relative_offset,
	          &offset,
	          &flags,
	          &bitmap,
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
	result = libvshadow_block_get_values(
	          NULL,
	          &original_offset,
	          &relative_offset,
	          &offset,
	          &flags,
	          &bitmap,
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

	result = libvshadow_block_get_values(
	          block,
	          NULL,
	          &relative_offset,
	          &offset,
	          &flags,
	          &bitmap,
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

	result = libvshadow_block_get_values(
	          block,
	          &original_offset,
	          NULL,
	          &offset,
	          &flags,
	          &bitmap,
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

	result = libvshadow_block_get_values(
	          block,
	          &original_offset,
	          &relative_offset,
	          NULL,
	          &flags,
	          &bitmap,
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

	result = libvshadow_block_get_values(
	          block,
	          &original_offset,
	          &relative_offset,
	          &offset,
	          NULL,
	          &bitmap,
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

	result = libvshadow_block_get_values(
	          block,
	          &original_offset,
	          &relative_offset,
	          &offset,
	          &flags,
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

	/* Test error case where internal block descriptor is NULL
	 */
	( (libvshadow_internal_block_t *) block )->block_descriptor = NULL;

	result = libvshadow_block_get_values(
	          block,
	          &original_offset,
	          &relative_offset,
	          &offset,
	          &flags,
	          &bitmap,
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
	result = libvshadow_block_free(
	          &block,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "block",
	 block );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( block != NULL )
	{
		libvshadow_block_free(
		 &block,
		 NULL );
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
	 "libvshadow_block_initialize",
	 vshadow_test_block_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

	VSHADOW_TEST_RUN(
	 "libvshadow_block_free",
	 vshadow_test_block_free );

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

	VSHADOW_TEST_RUN(
	 "libvshadow_block_get_original_offset",
	 vshadow_test_block_get_original_offset );

	VSHADOW_TEST_RUN(
	 "libvshadow_block_get_relative_offset",
	 vshadow_test_block_get_relative_offset );

	VSHADOW_TEST_RUN(
	 "libvshadow_block_get_offset",
	 vshadow_test_block_get_offset );

	VSHADOW_TEST_RUN(
	 "libvshadow_block_get_values",
	 vshadow_test_block_get_values );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

