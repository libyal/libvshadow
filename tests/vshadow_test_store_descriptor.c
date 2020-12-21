/*
 * Library store_descriptor type test program
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

#include "../libvshadow/libvshadow_store_descriptor.h"

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

/* Tests the libvshadow_store_descriptor_initialize function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_descriptor_initialize(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_store_descriptor_t *store_descriptor = NULL;
	int result                                      = 0;

#if defined( HAVE_VSHADOW_TEST_MEMORY )
	int number_of_malloc_fail_tests                 = 1;
	int number_of_memset_fail_tests                 = 1;
	int test_number                                 = 0;
#endif

	/* Test regular cases
	 */
	result = libvshadow_store_descriptor_initialize(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "store_descriptor",
	 store_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_store_descriptor_free(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "store_descriptor",
	 store_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_store_descriptor_initialize(
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

	store_descriptor = (libvshadow_store_descriptor_t *) 0x12345678UL;

	result = libvshadow_store_descriptor_initialize(
	          &store_descriptor,
	          &error );

	store_descriptor = NULL;

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
		/* Test libvshadow_store_descriptor_initialize with malloc failing
		 */
		vshadow_test_malloc_attempts_before_fail = test_number;

		result = libvshadow_store_descriptor_initialize(
		          &store_descriptor,
		          &error );

		if( vshadow_test_malloc_attempts_before_fail != -1 )
		{
			vshadow_test_malloc_attempts_before_fail = -1;

			if( store_descriptor != NULL )
			{
				libvshadow_store_descriptor_free(
				 &store_descriptor,
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
			 "store_descriptor",
			 store_descriptor );

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
		/* Test libvshadow_store_descriptor_initialize with memset failing
		 */
		vshadow_test_memset_attempts_before_fail = test_number;

		result = libvshadow_store_descriptor_initialize(
		          &store_descriptor,
		          &error );

		if( vshadow_test_memset_attempts_before_fail != -1 )
		{
			vshadow_test_memset_attempts_before_fail = -1;

			if( store_descriptor != NULL )
			{
				libvshadow_store_descriptor_free(
				 &store_descriptor,
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
			 "store_descriptor",
			 store_descriptor );

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
	if( store_descriptor != NULL )
	{
		libvshadow_store_descriptor_free(
		 &store_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_store_descriptor_free function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_descriptor_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvshadow_store_descriptor_free(
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

/* Tests the libvshadow_store_descriptor_get_volume_size function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_descriptor_get_volume_size(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_store_descriptor_t *store_descriptor = NULL;
	size64_t volume_size                            = 0;
	int result                                      = 0;
	int volume_size_is_set                          = 0;

	/* Initialize test
	 */
	result = libvshadow_store_descriptor_initialize(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "store_descriptor",
	 store_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvshadow_store_descriptor_get_volume_size(
	          store_descriptor,
	          &volume_size,
	          &error );

	VSHADOW_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	volume_size_is_set = result;

	/* Test error cases
	 */
	result = libvshadow_store_descriptor_get_volume_size(
	          NULL,
	          &volume_size,
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

	if( volume_size_is_set != 0 )
	{
		result = libvshadow_store_descriptor_get_volume_size(
		          store_descriptor,
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
	}
	/* Clean up
	 */
	result = libvshadow_store_descriptor_free(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "store_descriptor",
	 store_descriptor );

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
	if( store_descriptor != NULL )
	{
		libvshadow_store_descriptor_free(
		 &store_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_store_descriptor_get_creation_time function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_descriptor_get_creation_time(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_store_descriptor_t *store_descriptor = NULL;
	uint64_t creation_time                          = 0;
	int creation_time_is_set                        = 0;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libvshadow_store_descriptor_initialize(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "store_descriptor",
	 store_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvshadow_store_descriptor_get_creation_time(
	          store_descriptor,
	          &creation_time,
	          &error );

	VSHADOW_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	creation_time_is_set = result;

	/* Test error cases
	 */
	result = libvshadow_store_descriptor_get_creation_time(
	          NULL,
	          &creation_time,
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

	if( creation_time_is_set != 0 )
	{
		result = libvshadow_store_descriptor_get_creation_time(
		          store_descriptor,
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
	}
	/* Clean up
	 */
	result = libvshadow_store_descriptor_free(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "store_descriptor",
	 store_descriptor );

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
	if( store_descriptor != NULL )
	{
		libvshadow_store_descriptor_free(
		 &store_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_store_descriptor_get_attribute_flags function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_descriptor_get_attribute_flags(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_store_descriptor_t *store_descriptor = NULL;
	uint32_t attribute_flags                        = 0;
	int attribute_flags_is_set                      = 0;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libvshadow_store_descriptor_initialize(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "store_descriptor",
	 store_descriptor );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvshadow_store_descriptor_get_attribute_flags(
	          store_descriptor,
	          &attribute_flags,
	          &error );

	VSHADOW_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	attribute_flags_is_set = result;

	/* Test error cases
	 */
	result = libvshadow_store_descriptor_get_attribute_flags(
	          NULL,
	          &attribute_flags,
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

	if( attribute_flags_is_set != 0 )
	{
		result = libvshadow_store_descriptor_get_attribute_flags(
		          store_descriptor,
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
	}
	/* Clean up
	 */
	result = libvshadow_store_descriptor_free(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "store_descriptor",
	 store_descriptor );

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
	if( store_descriptor != NULL )
	{
		libvshadow_store_descriptor_free(
		 &store_descriptor,
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
	 "libvshadow_store_descriptor_initialize",
	 vshadow_test_store_descriptor_initialize );

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_free",
	 vshadow_test_store_descriptor_free );

	/* TODO: add tests for libvshadow_store_descriptor_has_in_volume_data */

	/* TODO: add tests for libvshadow_store_descriptor_compare_by_creation_time */

	/* TODO: add tests for libvshadow_store_descriptor_compare_by_identifier */

	/* TODO: add tests for libvshadow_store_descriptor_read_catalog_entry */

	/* TODO: add tests for libvshadow_store_descriptor_read_store_header */

	/* TODO: add tests for libvshadow_store_descriptor_read_store_bitmap */

	/* TODO: add tests for libvshadow_store_descriptor_read_store_block_list */

	/* TODO: add tests for libvshadow_store_descriptor_read_store_block_range_list */

	/* TODO: add tests for libvshadow_store_descriptor_read_block_descriptors */

	/* TODO: add tests for libvshadow_store_descriptor_read_buffer */

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_get_volume_size",
	 vshadow_test_store_descriptor_get_volume_size );

	/* TODO: add tests for libvshadow_store_descriptor_get_identifier */

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_get_creation_time",
	 vshadow_test_store_descriptor_get_creation_time );

	/* TODO: add tests for libvshadow_store_descriptor_get_copy_identifier */

	/* TODO: add tests for libvshadow_store_descriptor_get_copy_set_identifier */

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_get_attribute_flags",
	 vshadow_test_store_descriptor_get_attribute_flags );

	/* TODO: add tests for libvshadow_store_descriptor_get_number_of_blocks */

	/* TODO: add tests for libvshadow_store_descriptor_get_block_descriptor_by_index */

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

