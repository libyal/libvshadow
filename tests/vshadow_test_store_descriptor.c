/*
 * Library store_descriptor type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vshadow_test_libbfio.h"
#include "vshadow_test_libcdata.h"
#include "vshadow_test_libcerror.h"
#include "vshadow_test_libvshadow.h"
#include "vshadow_test_macros.h"
#include "vshadow_test_memory.h"
#include "vshadow_test_unused.h"

#include "../libvshadow/libvshadow_block_descriptor.h"
#include "../libvshadow/libvshadow_block_tree.h"
#include "../libvshadow/libvshadow_definitions.h"
#include "../libvshadow/libvshadow_io_handle.h"
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
	int number_of_malloc_fail_tests                 = 5;
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

	/* Test regular cases (has_in_volume_store_data == 0 and == 1)
	 */
	result = libvshadow_store_descriptor_get_attribute_flags(
	          store_descriptor,
	          &attribute_flags,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	store_descriptor->has_in_volume_store_data = 1;
	store_descriptor->attribute_flags          = 0x12345678UL;

	result = libvshadow_store_descriptor_get_attribute_flags(
	          store_descriptor,
	          &attribute_flags,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT32(
	 "attribute_flags",
	 attribute_flags,
	 (uint32_t) 0x12345678UL );

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

/* Helper to initialize a 128-byte VSS store block header
 */
static void vshadow_test_store_descriptor_fill_block_header(
             uint8_t *block_data,
             uint32_t record_type,
             uint64_t next_offset )
{
	memory_copy(
	 block_data,
	 vshadow_vss_identifier,
	 16 );
	byte_stream_copy_from_uint32_little_endian(
	 &( block_data[ 16 ] ),
	 1 );
	byte_stream_copy_from_uint32_little_endian(
	 &( block_data[ 20 ] ),
	 record_type );
	byte_stream_copy_from_uint64_little_endian(
	 &( block_data[ 40 ] ),
	 next_offset );
}

/* Tests the libvshadow_store_descriptor_has_in_volume_data function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_descriptor_has_in_volume_data(
     void )
{
	libcerror_error_t *error                        = NULL;
	libvshadow_store_descriptor_t *store_descriptor = NULL;
	int result                                      = 0;

	result = libvshadow_store_descriptor_initialize(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_store_descriptor_has_in_volume_data(
	          store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	store_descriptor->has_in_volume_store_data = 1;

	result = libvshadow_store_descriptor_has_in_volume_data(
	          store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_store_descriptor_has_in_volume_data(
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

	result = libvshadow_store_descriptor_free(
	          &store_descriptor,
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
	if( store_descriptor != NULL )
	{
		libvshadow_store_descriptor_free(
		 &store_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_store_descriptor_compare_by_creation_time function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_descriptor_compare_by_creation_time(
     void )
{
	libcerror_error_t *error                               = NULL;
	libvshadow_store_descriptor_t *first_store_descriptor  = NULL;
	libvshadow_store_descriptor_t *second_store_descriptor = NULL;
	int result                                             = 0;

	result = libvshadow_store_descriptor_initialize(
	          &first_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_store_descriptor_initialize(
	          &second_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	first_store_descriptor->creation_time  = 100;
	second_store_descriptor->creation_time = 200;

	result = libvshadow_store_descriptor_compare_by_creation_time(
	          first_store_descriptor,
	          second_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBCDATA_COMPARE_LESS );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_store_descriptor_compare_by_creation_time(
	          second_store_descriptor,
	          first_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBCDATA_COMPARE_GREATER );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	second_store_descriptor->creation_time = 100;

	result = libvshadow_store_descriptor_compare_by_creation_time(
	          first_store_descriptor,
	          second_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBCDATA_COMPARE_EQUAL );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_store_descriptor_compare_by_creation_time(
	          NULL,
	          second_store_descriptor,
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

	result = libvshadow_store_descriptor_compare_by_creation_time(
	          first_store_descriptor,
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

	result = libvshadow_store_descriptor_free(
	          &second_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libvshadow_store_descriptor_free(
	          &first_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( second_store_descriptor != NULL )
	{
		libvshadow_store_descriptor_free(
		 &second_store_descriptor,
		 NULL );
	}
	if( first_store_descriptor != NULL )
	{
		libvshadow_store_descriptor_free(
		 &first_store_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_store_descriptor_compare_by_identifier function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_descriptor_compare_by_identifier(
     void )
{
	libcerror_error_t *error                               = NULL;
	libvshadow_store_descriptor_t *first_store_descriptor  = NULL;
	libvshadow_store_descriptor_t *second_store_descriptor = NULL;
	int result                                             = 0;

	result = libvshadow_store_descriptor_initialize(
	          &first_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libvshadow_store_descriptor_initialize(
	          &second_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	first_store_descriptor->identifier[ 0 ]  = 0x10;
	second_store_descriptor->identifier[ 0 ] = 0x20;

	result = libvshadow_store_descriptor_compare_by_identifier(
	          first_store_descriptor,
	          second_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBCDATA_COMPARE_LESS );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_store_descriptor_compare_by_identifier(
	          second_store_descriptor,
	          first_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBCDATA_COMPARE_GREATER );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	second_store_descriptor->identifier[ 0 ] = 0x10;

	result = libvshadow_store_descriptor_compare_by_identifier(
	          first_store_descriptor,
	          second_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBCDATA_COMPARE_EQUAL );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_store_descriptor_compare_by_identifier(
	          NULL,
	          second_store_descriptor,
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

	result = libvshadow_store_descriptor_compare_by_identifier(
	          first_store_descriptor,
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

	result = libvshadow_store_descriptor_free(
	          &second_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libvshadow_store_descriptor_free(
	          &first_store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( second_store_descriptor != NULL )
	{
		libvshadow_store_descriptor_free(
		 &second_store_descriptor,
		 NULL );
	}
	if( first_store_descriptor != NULL )
	{
		libvshadow_store_descriptor_free(
		 &first_store_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_store_descriptor_read_catalog_entry function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_descriptor_read_catalog_entry(
     void )
{
	uint8_t entry_data[ 128 ];

	libcerror_error_t *error                        = NULL;
	libvshadow_store_descriptor_t *store_descriptor = NULL;
	uint64_t entry_type                             = 0;
	int offset_field_index                          = 0;
	int result                                      = 0;

	const size_t offset_fields[ 5 ] = { 8, 32, 40, 48, 72 };

	result = libvshadow_store_descriptor_initialize(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	memory_set(
	 entry_data,
	 0,
	 128 );

	/* Test entry types 0, 1, 2, 3
	 */
	result = libvshadow_store_descriptor_read_catalog_entry(
	          store_descriptor,
	          entry_data,
	          128,
	          &entry_type,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT64(
	 "entry_type",
	 entry_type,
	 (uint64_t) 0 );

	byte_stream_copy_from_uint64_little_endian(
	 entry_data,
	 (uint64_t) 1ULL );

	result = libvshadow_store_descriptor_read_catalog_entry(
	          store_descriptor,
	          entry_data,
	          128,
	          &entry_type,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT64(
	 "entry_type",
	 entry_type,
	 (uint64_t) 1 );

	byte_stream_copy_from_uint64_little_endian(
	 entry_data,
	 (uint64_t) 2ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( entry_data[ 8 ] ),
	 (uint64_t) 0x80000ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( entry_data[ 48 ] ),
	 (uint64_t) 123456ULL );

	result = libvshadow_store_descriptor_read_catalog_entry(
	          store_descriptor,
	          entry_data,
	          128,
	          &entry_type,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT64(
	 "entry_type",
	 entry_type,
	 (uint64_t) 2 );

	memory_set(
	 entry_data,
	 0,
	 128 );
	byte_stream_copy_from_uint64_little_endian(
	 entry_data,
	 (uint64_t) 3ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( entry_data[ 8 ] ),
	 0x4000ULL );

	result = libvshadow_store_descriptor_read_catalog_entry(
	          store_descriptor,
	          entry_data,
	          128,
	          &entry_type,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT64(
	 "entry_type",
	 entry_type,
	 (uint64_t) 3 );

	/* Test error cases
	 */
	result = libvshadow_store_descriptor_read_catalog_entry(
	          NULL,
	          entry_data,
	          128,
	          &entry_type,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_catalog_entry(
	          store_descriptor,
	          NULL,
	          128,
	          &entry_type,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_catalog_entry(
	          store_descriptor,
	          entry_data,
	          127,
	          &entry_type,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_catalog_entry(
	          store_descriptor,
	          entry_data,
	          (size_t) SSIZE_MAX + 1,
	          &entry_type,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_catalog_entry(
	          store_descriptor,
	          entry_data,
	          128,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	/* Unsupported entry type
	 */
	byte_stream_copy_from_uint64_little_endian(
	 entry_data,
	 (uint64_t) 4ULL );

	result = libvshadow_store_descriptor_read_catalog_entry(
	          store_descriptor,
	          entry_data,
	          128,
	          &entry_type,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	/* Out-of-bounds offset fields for entry type 3
	 */
	for( offset_field_index = 0;
	     offset_field_index < 5;
	     offset_field_index++ )
	{
		memory_set(
		 entry_data,
		 0,
		 128 );
		byte_stream_copy_from_uint64_little_endian(
		 entry_data,
		 (uint64_t) 3ULL );
		byte_stream_copy_from_uint64_little_endian(
		 &( entry_data[ offset_fields[ offset_field_index ] ] ),
		 (uint64_t) INT64_MAX + 1 );

		result = libvshadow_store_descriptor_read_catalog_entry(
		          store_descriptor,
		          entry_data,
		          128,
		          &entry_type,
		          &error );

		VSHADOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_VSHADOW_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED )

	memory_set(
	 entry_data,
	 0,
	 128 );
	byte_stream_copy_from_uint64_little_endian(
	 entry_data,
	 (uint64_t) 2ULL );

	vshadow_test_memcpy_attempts_before_fail = 0;

	result = libvshadow_store_descriptor_read_catalog_entry(
	          store_descriptor,
	          entry_data,
	          128,
	          &entry_type,
	          &error );

	if( vshadow_test_memcpy_attempts_before_fail != -1 )
	{
		vshadow_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		VSHADOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		libcerror_error_free(
		 &error );
	}
#endif

	result = libvshadow_store_descriptor_free(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

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

/* Tests the libvshadow_store_descriptor_read_store_header function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_descriptor_read_store_header(
     void )
{
	libbfio_handle_t *file_io_handle                = NULL;
	libcerror_error_t *error                        = NULL;
	libvshadow_store_descriptor_t *store_descriptor = NULL;
	uint8_t *block_data                             = NULL;
	int result                                      = 0;

	block_data = (uint8_t *) memory_allocate(
	                          0x4000 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block_data",
	 block_data );

	memory_set(
	 block_data,
	 0,
	 0x4000 );

	vshadow_test_store_descriptor_fill_block_header(
	 block_data,
	 LIBVSHADOW_RECORD_TYPE_STORE_HEADER,
	 0 );

	/* Populate operating machine string ("A", 4 bytes UTF-16LE with NUL) and service machine string ("B", 4 bytes)
	 * store_header is 128 bytes, store_information is 64 bytes -> strings start at offset 192
	 */
	byte_stream_copy_from_uint16_little_endian(
	 &( block_data[ 192 ] ),
	 4 );
	block_data[ 194 ] = 'A';
	byte_stream_copy_from_uint16_little_endian(
	 &( block_data[ 198 ] ),
	 4 );
	block_data[ 200 ] = 'B';

	result = libbfio_memory_range_initialize(
	          &file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libbfio_memory_range_set(
	          file_io_handle,
	          block_data,
	          0x4000,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libbfio_handle_open(
	          file_io_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libvshadow_store_descriptor_initialize(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Test regular case
	 */
	result = libvshadow_store_descriptor_read_store_header(
	          store_descriptor,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Freeing store_descriptor also covers freeing operating_machine_string & service_machine_string
	 */
	result = libvshadow_store_descriptor_free(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Test error cases
	 */
	result = libvshadow_store_descriptor_initialize(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libvshadow_store_descriptor_read_store_header(
	          NULL,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_store_header(
	          store_descriptor,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	/* Wrong record type
	 */
	byte_stream_copy_from_uint32_little_endian(
	 &( block_data[ 20 ] ),
	 LIBVSHADOW_RECORD_TYPE_STORE_INDEX );

	result = libvshadow_store_descriptor_read_store_header(
	          store_descriptor,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	byte_stream_copy_from_uint32_little_endian(
	 &( block_data[ 20 ] ),
	 LIBVSHADOW_RECORD_TYPE_STORE_HEADER );

	/* Operating machine string size out of bounds
	 */
	byte_stream_copy_from_uint16_little_endian(
	 &( block_data[ 192 ] ),
	 0xffff );

	result = libvshadow_store_descriptor_read_store_header(
	          store_descriptor,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	/* Service machine string size out of bounds
	 */
	byte_stream_copy_from_uint16_little_endian(
	 &( block_data[ 192 ] ),
	 0 );
	byte_stream_copy_from_uint16_little_endian(
	 &( block_data[ 194 ] ),
	 0xffff );

	result = libvshadow_store_descriptor_read_store_header(
	          store_descriptor,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	/* Store header data offset out of bounds before reading service string size
	 */
	byte_stream_copy_from_uint16_little_endian(
	 &( block_data[ 192 ] ),
	 (uint16_t) ( 0x4000 - 128 - 64 - 2 ) );

	result = libvshadow_store_descriptor_read_store_header(
	          store_descriptor,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_free(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libbfio_handle_close(
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	memory_free(
	 block_data );

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
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( block_data != NULL )
	{
		memory_free(
		 block_data );
	}
	return( 0 );
}

/* Tests the libvshadow_store_descriptor_read_store_bitmap,
 * libvshadow_store_descriptor_read_store_block_list,
 * libvshadow_store_descriptor_read_store_block_range_list,
 * libvshadow_store_descriptor_read_block_descriptors,
 * libvshadow_store_descriptor_read_buffer,
 * libvshadow_store_descriptor_get_number_of_blocks, and
 * libvshadow_store_descriptor_get_block_descriptor_by_index functions
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_descriptor_read_and_query(
     void )
{
	uint8_t read_buffer[ 0x4000 ];

	libbfio_handle_t *file_io_handle                    = NULL;
	libcerror_error_t *error                            = NULL;
	libvshadow_block_descriptor_t *block_descriptor     = NULL;
	libvshadow_io_handle_t *io_handle                   = NULL;
	libvshadow_store_descriptor_t *next_store_desc      = NULL;
	libvshadow_store_descriptor_t *store_descriptor     = NULL;
	uint8_t *volume_data                                = NULL;
	size_t volume_data_size                             = 0x40000;
	off64_t bitmap_offset                               = 0;
	off64_t next_offset                                 = 0;
	ssize_t read_count                                  = 0;
	int number_of_blocks                                = 0;
	int result                                          = 0;

	/* Synthetic 256 KiB (16 x 16 KiB blocks) volume layout:
	 * 0x00000: base volume data (filled with 0x11)
	 * 0x04000: store0 data block for direct block (filled with 0x22)
	 * 0x08000: store0 data block for overlay (filled with 0x33)
	 * 0x0c000: store1 data block for forwarded block (filled with 0x44)
	 * 0x10000: store0 bitmap block (bits 0,1 set and last bit set for trailing-run test)
	 * 0x14000: store0 previous bitmap block (bit 0 set)
	 * 0x18000: store0 block list (direct @0x04000, overlay @0x08000, forwarder @0x0c000 -> 0x10000)
	 * 0x1c000: store0 block range list (1 valid entry)
	 * 0x20000: store1 bitmap block (bit 5 set -> offset 0x14000 zero-filled when in both bitmaps!)
	 * 0x24000: store1 previous bitmap block (bit 5 set)
	 * 0x28000: store1 block list (direct @0x10000 -> data @0x0c000, plus base @0x18000)
	 */
	volume_data = (uint8_t *) memory_allocate(
	                           volume_data_size );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "volume_data",
	 volume_data );

	memory_set(
	 volume_data,
	 0,
	 volume_data_size );

	memory_set(
	 &( volume_data[ 0x00000 ] ),
	 0x11,
	 0x4000 );
	memory_set(
	 &( volume_data[ 0x04000 ] ),
	 0x22,
	 0x4000 );
	memory_set(
	 &( volume_data[ 0x08000 ] ),
	 0x33,
	 0x4000 );
	memory_set(
	 &( volume_data[ 0x0c000 ] ),
	 0x44,
	 0x4000 );

	/* store0 bitmap at 0x10000: bit 0 (offset 0x00000), bit 1 (0x04000), and last bit of block
	 */
	vshadow_test_store_descriptor_fill_block_header(
	 &( volume_data[ 0x10000 ] ),
	 LIBVSHADOW_RECORD_TYPE_STORE_BITMAP,
	 0 );
	volume_data[ 0x10000 + 128 ] = 0x03;
	volume_data[ 0x13fff ]       = 0x80;

	/* store0 previous bitmap at 0x14000
	 */
	vshadow_test_store_descriptor_fill_block_header(
	 &( volume_data[ 0x14000 ] ),
	 LIBVSHADOW_RECORD_TYPE_STORE_BITMAP,
	 0 );
	volume_data[ 0x14000 + 128 ] = 0x01;

	/* store0 block list at 0x18000
	 */
	vshadow_test_store_descriptor_fill_block_header(
	 &( volume_data[ 0x18000 ] ),
	 LIBVSHADOW_RECORD_TYPE_STORE_INDEX,
	 0 );
	/* Entry 0 (offset 128): direct block orig=0x00000, rel=0x04000, off=0x04000, flags=0
	 */
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x18000 + 128 + 0 ] ),
	 0x00000ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x18000 + 128 + 8 ] ),
	 0x04000ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x18000 + 128 + 16 ] ),
	 0x04000ULL );

	/* Entry 1 (offset 160): overlay block orig=0x08000, rel=0x08000, off=0x08000, flags=2 (IS_OVERLAY), bitmap=0x00000005 (sectors 0 & 2)
	 */
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x18000 + 160 + 0 ] ),
	 0x08000ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x18000 + 160 + 8 ] ),
	 0x08000ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x18000 + 160 + 16 ] ),
	 0x08000ULL );
	byte_stream_copy_from_uint32_little_endian(
	 &( volume_data[ 0x18000 + 160 + 24 ] ),
	 LIBVSHADOW_BLOCK_FLAG_IS_OVERLAY );
	byte_stream_copy_from_uint32_little_endian(
	 &( volume_data[ 0x18000 + 160 + 28 ] ),
	 0x00000005UL );

	/* Entry 2 (offset 192): forwarder block orig=0x0c000, rel=0x10000, off=0, flags=1 (IS_FORWARDER)
	 */
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x18000 + 192 + 0 ] ),
	 (uint64_t) 0x0c000ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x18000 + 192 + 8 ] ),
	 (uint64_t) 0x10000ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x18000 + 192 + 16 ] ),
	 (uint64_t) 0ULL );
	byte_stream_copy_from_uint32_little_endian(
	 &( volume_data[ 0x18000 + 192 + 24 ] ),
	 LIBVSHADOW_BLOCK_FLAG_IS_FORWARDER );

	/* store0 block range list at 0x1c000
	 */
	vshadow_test_store_descriptor_fill_block_header(
	 &( volume_data[ 0x1c000 ] ),
	 LIBVSHADOW_RECORD_TYPE_STORE_BLOCK_RANGE,
	 0 );
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x1c000 + 128 + 0 ] ),
	 0x04000ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x1c000 + 128 + 8 ] ),
	 0x04000ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x1c000 + 128 + 16 ] ),
	 0x4000ULL );

	/* store1 bitmap at 0x20000 and previous bitmap at 0x24000: bit 5 -> offset 0x14000
	 */
	vshadow_test_store_descriptor_fill_block_header(
	 &( volume_data[ 0x20000 ] ),
	 LIBVSHADOW_RECORD_TYPE_STORE_BITMAP,
	 0 );
	volume_data[ 0x20000 + 128 ] = 0x20;

	vshadow_test_store_descriptor_fill_block_header(
	 &( volume_data[ 0x24000 ] ),
	 LIBVSHADOW_RECORD_TYPE_STORE_BITMAP,
	 0 );
	volume_data[ 0x24000 + 128 ] = 0x20;

	/* store1 block list at 0x28000: direct block orig=0x10000 -> data @0x0c000 (0x44)
	 */
	vshadow_test_store_descriptor_fill_block_header(
	 &( volume_data[ 0x28000 ] ),
	 LIBVSHADOW_RECORD_TYPE_STORE_INDEX,
	 0 );
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x28000 + 128 + 0 ] ),
	 0x10000ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x28000 + 128 + 8 ] ),
	 0x0c000ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( volume_data[ 0x28000 + 128 + 16 ] ),
	 0x0c000ULL );

	result = libbfio_memory_range_initialize(
	          &file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libbfio_memory_range_set(
	          file_io_handle,
	          volume_data,
	          volume_data_size,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libbfio_handle_open(
	          file_io_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libvshadow_io_handle_initialize(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	io_handle->volume_size = volume_data_size;

	result = libvshadow_store_descriptor_initialize(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libvshadow_store_descriptor_initialize(
	          &next_store_desc,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	store_descriptor->index                         = 0;
	store_descriptor->volume_size                   = volume_data_size;
	store_descriptor->has_in_volume_store_data      = 1;
	store_descriptor->store_bitmap_offset           = 0x10000;
	store_descriptor->store_previous_bitmap_offset  = 0x14000;
	store_descriptor->store_block_list_offset       = 0x18000;
	store_descriptor->store_block_range_list_offset = 0x1c000;
	store_descriptor->next_store_descriptor         = next_store_desc;

	next_store_desc->index                         = 1;
	next_store_desc->volume_size                   = volume_data_size;
	next_store_desc->has_in_volume_store_data      = 1;
	next_store_desc->store_bitmap_offset           = 0x20000;
	next_store_desc->store_previous_bitmap_offset  = 0x24000;
	next_store_desc->store_block_list_offset       = 0x28000;
	next_store_desc->previous_store_descriptor     = store_descriptor;

	/* Test get_number_of_blocks and get_block_descriptor_by_index (triggers read_block_descriptors)
	 */
	result = libvshadow_store_descriptor_get_number_of_blocks(
	          store_descriptor,
	          io_handle,
	          file_io_handle,
	          &number_of_blocks,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "number_of_blocks",
	 number_of_blocks,
	 3 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_store_descriptor_get_block_descriptor_by_index(
	          store_descriptor,
	          io_handle,
	          file_io_handle,
	          0,
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

	/* Test read_buffer: direct block (0x00000 -> 0x22) and cached current_block_descriptor hit
	 */
	read_count = libvshadow_store_descriptor_read_buffer(
	              store_descriptor,
	              io_handle,
	              file_io_handle,
	              read_buffer,
	              512,
	              0x00000,
	              0,
	              &error );

	VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 512 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT8(
	 "read_buffer[0]",
	 read_buffer[ 0 ],
	 (uint8_t) 0x22 );

	read_count = libvshadow_store_descriptor_read_buffer(
	              store_descriptor,
	              io_handle,
	              file_io_handle,
	              read_buffer,
	              512,
	              0x00200,
	              0,
	              &error );

	VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 512 );

	/* Test read_buffer: overlay block (active store index 0) across sectors 0 (set), 1 (clear), 2 (set)
	 */
	read_count = libvshadow_store_descriptor_read_buffer(
	              store_descriptor,
	              io_handle,
	              file_io_handle,
	              read_buffer,
	              1536,
	              0x08000,
	              0,
	              &error );

	VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 1536 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT8(
	 "read_buffer[0]",
	 read_buffer[ 0 ],
	 (uint8_t) 0x33 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT8(
	 "read_buffer[1024]",
	 read_buffer[ 1024 ],
	 (uint8_t) 0x33 );

	/* Test read_buffer: overlay block with non-active store index (skips overlay)
	 */
	read_count = libvshadow_store_descriptor_read_buffer(
	              store_descriptor,
	              io_handle,
	              file_io_handle,
	              read_buffer,
	              512,
	              0x08000,
	              1,
	              &error );

	VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 512 );

	/* Test read_buffer: forwarder block (0x0c000 -> next_store @ 0x10000 -> data @ 0x0c000 = 0x44)
	 */
	read_count = libvshadow_store_descriptor_read_buffer(
	              store_descriptor,
	              io_handle,
	              file_io_handle,
	              read_buffer,
	              512,
	              0x0c000,
	              0,
	              &error );

	VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 512 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT8(
	 "read_buffer[0]",
	 read_buffer[ 0 ],
	 (uint8_t) 0x44 );

	/* Test read_buffer on next_store_desc (most recent store):
	 * offset 0x14000 is in both current and previous bitmap -> zero-filled!
	 */
	memory_set(
	 read_buffer,
	 0xaa,
	 512 );

	read_count = libvshadow_store_descriptor_read_buffer(
	              next_store_desc,
	              io_handle,
	              file_io_handle,
	              read_buffer,
	              512,
	              0x14000,
	              1,
	              &error );

	VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 512 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT8(
	 "read_buffer[0]",
	 read_buffer[ 0 ],
	 (uint8_t) 0x00 );

	/* Test read_buffer on next_store_desc: fallback read from base volume (offset 0x00000 = 0x11)
	 */
	read_count = libvshadow_store_descriptor_read_buffer(
	              next_store_desc,
	              io_handle,
	              file_io_handle,
	              read_buffer,
	              512,
	              0x00000,
	              1,
	              &error );

	VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 512 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT8(
	 "read_buffer[0]",
	 read_buffer[ 0 ],
	 (uint8_t) 0x11 );

	/* Test error cases for read_store_bitmap, read_store_block_list, read_store_block_range_list,
	 * read_block_descriptors, read_buffer, get_number_of_blocks, get_block_descriptor_by_index
	 */
	result = libvshadow_store_descriptor_read_store_bitmap(
	          NULL,
	          file_io_handle,
	          0x10000,
	          store_descriptor->block_offset_list,
	          &bitmap_offset,
	          &next_offset,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_store_bitmap(
	          store_descriptor,
	          file_io_handle,
	          0x10000,
	          store_descriptor->block_offset_list,
	          NULL,
	          &next_offset,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_store_bitmap(
	          store_descriptor,
	          file_io_handle,
	          0x10000,
	          store_descriptor->block_offset_list,
	          &bitmap_offset,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_store_bitmap(
	          store_descriptor,
	          file_io_handle,
	          0x18000,
	          store_descriptor->block_offset_list,
	          &bitmap_offset,
	          &next_offset,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_store_block_list(
	          NULL,
	          file_io_handle,
	          0x18000,
	          &next_offset,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_store_block_list(
	          store_descriptor,
	          file_io_handle,
	          0x18000,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_store_block_list(
	          store_descriptor,
	          file_io_handle,
	          0x10000,
	          &next_offset,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_store_block_range_list(
	          NULL,
	          file_io_handle,
	          0x1c000,
	          &next_offset,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_store_block_range_list(
	          store_descriptor,
	          file_io_handle,
	          0x1c000,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_store_block_range_list(
	          store_descriptor,
	          file_io_handle,
	          0x10000,
	          &next_offset,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_block_descriptors(
	          NULL,
	          io_handle,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_read_block_descriptors(
	          store_descriptor,
	          NULL,
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	read_count = libvshadow_store_descriptor_read_buffer(
	              NULL,
	              io_handle,
	              file_io_handle,
	              read_buffer,
	              512,
	              0,
	              0,
	              &error );

	VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	libcerror_error_free(
	 &error );

	store_descriptor->has_in_volume_store_data = 0;

	read_count = libvshadow_store_descriptor_read_buffer(
	              store_descriptor,
	              io_handle,
	              file_io_handle,
	              read_buffer,
	              512,
	              0,
	              0,
	              &error );

	VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_number_of_blocks(
	          NULL,
	          io_handle,
	          file_io_handle,
	          &number_of_blocks,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_number_of_blocks(
	          store_descriptor,
	          io_handle,
	          file_io_handle,
	          &number_of_blocks,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_block_descriptor_by_index(
	          NULL,
	          io_handle,
	          file_io_handle,
	          0,
	          &block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_block_descriptor_by_index(
	          store_descriptor,
	          io_handle,
	          file_io_handle,
	          0,
	          &block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	store_descriptor->has_in_volume_store_data = 1;

	result = libvshadow_store_descriptor_get_number_of_blocks(
	          store_descriptor,
	          NULL,
	          file_io_handle,
	          &number_of_blocks,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_number_of_blocks(
	          store_descriptor,
	          io_handle,
	          file_io_handle,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_block_descriptor_by_index(
	          store_descriptor,
	          NULL,
	          file_io_handle,
	          0,
	          &block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_block_descriptor_by_index(
	          store_descriptor,
	          io_handle,
	          file_io_handle,
	          -1,
	          &block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_block_descriptor_by_index(
	          store_descriptor,
	          io_handle,
	          file_io_handle,
	          0,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libvshadow_store_descriptor_free(
	          &next_store_desc,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libvshadow_store_descriptor_free(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libvshadow_io_handle_free(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libbfio_handle_close(
	          file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	memory_free(
	 volume_data );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( next_store_desc != NULL )
	{
		libvshadow_store_descriptor_free(
		 &next_store_desc,
		 NULL );
	}
	if( store_descriptor != NULL )
	{
		libvshadow_store_descriptor_free(
		 &store_descriptor,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libvshadow_io_handle_free(
		 &io_handle,
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

/* Tests the libvshadow_store_descriptor_get_identifier,
 * libvshadow_store_descriptor_get_copy_identifier, and
 * libvshadow_store_descriptor_get_copy_set_identifier functions
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_descriptor_get_identifiers(
     void )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error                        = NULL;
	libvshadow_store_descriptor_t *store_descriptor = NULL;
	int result                                      = 0;

	result = libvshadow_store_descriptor_initialize(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Test get_identifier
	 */
	result = libvshadow_store_descriptor_get_identifier(
	          store_descriptor,
	          guid_data,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libvshadow_store_descriptor_get_identifier(
	          NULL,
	          guid_data,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_identifier(
	          store_descriptor,
	          NULL,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_identifier(
	          store_descriptor,
	          guid_data,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_identifier(
	          store_descriptor,
	          guid_data,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	/* Test get_copy_identifier (has_in_volume_store_data == 0 and == 1)
	 */
	result = libvshadow_store_descriptor_get_copy_identifier(
	          store_descriptor,
	          guid_data,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	store_descriptor->has_in_volume_store_data = 1;

	result = libvshadow_store_descriptor_get_copy_identifier(
	          store_descriptor,
	          guid_data,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libvshadow_store_descriptor_get_copy_identifier(
	          NULL,
	          guid_data,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_copy_identifier(
	          store_descriptor,
	          NULL,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_copy_identifier(
	          store_descriptor,
	          guid_data,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_copy_identifier(
	          store_descriptor,
	          guid_data,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	/* Test get_copy_set_identifier (has_in_volume_store_data == 0 and == 1)
	 */
	store_descriptor->has_in_volume_store_data = 0;

	result = libvshadow_store_descriptor_get_copy_set_identifier(
	          store_descriptor,
	          guid_data,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	store_descriptor->has_in_volume_store_data = 1;

	result = libvshadow_store_descriptor_get_copy_set_identifier(
	          store_descriptor,
	          guid_data,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libvshadow_store_descriptor_get_copy_set_identifier(
	          NULL,
	          guid_data,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_copy_set_identifier(
	          store_descriptor,
	          NULL,
	          16,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_copy_set_identifier(
	          store_descriptor,
	          guid_data,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

	result = libvshadow_store_descriptor_get_copy_set_identifier(
	          store_descriptor,
	          guid_data,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSHADOW_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED )

	vshadow_test_memcpy_attempts_before_fail = 0;
	result = libvshadow_store_descriptor_get_identifier(
	          store_descriptor,
	          guid_data,
	          16,
	          &error );
	if( vshadow_test_memcpy_attempts_before_fail != -1 )
	{
		vshadow_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		VSHADOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		libcerror_error_free(
		 &error );
	}
	vshadow_test_memcpy_attempts_before_fail = 0;
	result = libvshadow_store_descriptor_get_copy_identifier(
	          store_descriptor,
	          guid_data,
	          16,
	          &error );
	if( vshadow_test_memcpy_attempts_before_fail != -1 )
	{
		vshadow_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		VSHADOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		libcerror_error_free(
		 &error );
	}
	vshadow_test_memcpy_attempts_before_fail = 0;
	result = libvshadow_store_descriptor_get_copy_set_identifier(
	          store_descriptor,
	          guid_data,
	          16,
	          &error );
	if( vshadow_test_memcpy_attempts_before_fail != -1 )
	{
		vshadow_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		VSHADOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		libcerror_error_free(
		 &error );
	}
#endif

	result = libvshadow_store_descriptor_free(
	          &store_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

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

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_has_in_volume_data",
	 vshadow_test_store_descriptor_has_in_volume_data );

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_compare_by_creation_time",
	 vshadow_test_store_descriptor_compare_by_creation_time );

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_compare_by_identifier",
	 vshadow_test_store_descriptor_compare_by_identifier );

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_read_catalog_entry",
	 vshadow_test_store_descriptor_read_catalog_entry );

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_read_store_header",
	 vshadow_test_store_descriptor_read_store_header );

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_read_and_query",
	 vshadow_test_store_descriptor_read_and_query );

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_get_volume_size",
	 vshadow_test_store_descriptor_get_volume_size );

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_get_creation_time",
	 vshadow_test_store_descriptor_get_creation_time );

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_get_identifiers",
	 vshadow_test_store_descriptor_get_identifiers );

	VSHADOW_TEST_RUN(
	 "libvshadow_store_descriptor_get_attribute_flags",
	 vshadow_test_store_descriptor_get_attribute_flags );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */
}

