/*
 * Library block_tree_node type test program
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
#include "../libvshadow/libvshadow_block_tree_node.h"

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

/* Tests the libvshadow_block_tree_node_initialize function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_tree_node_initialize(
     void )
{
	libcerror_error_t *error                      = NULL;
	libvshadow_block_tree_node_t *block_tree_node = NULL;
	int result                                    = 0;

#if defined( HAVE_VSHADOW_TEST_MEMORY )
	int number_of_malloc_fail_tests               = 3;
	int number_of_memset_fail_tests               = 1;
	int test_number                               = 0;
#endif

	/* Test block_tree_node initialization
	 */
	result = libvshadow_block_tree_node_initialize(
	          &block_tree_node,
	          0,
	          1024,
	          256,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block_tree_node",
	 block_tree_node );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_tree_node_free(
	          &block_tree_node,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "block_tree_node",
	 block_tree_node );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_block_tree_node_initialize(
	          NULL,
	          0,
	          1024,
	          256,
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

	block_tree_node = (libvshadow_block_tree_node_t *) 0x12345678UL;

	result = libvshadow_block_tree_node_initialize(
	          &block_tree_node,
	          0,
	          1024,
	          256,
	          &error );

	block_tree_node = NULL;

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvshadow_block_tree_node_initialize(
	          &block_tree_node,
	          -1,
	          1024,
	          256,
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

	result = libvshadow_block_tree_node_initialize(
	          &block_tree_node,
	          0,
	          0,
	          256,
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

	result = libvshadow_block_tree_node_initialize(
	          &block_tree_node,
	          1024,
	          (size64_t) INT64_MAX,
	          256,
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

	result = libvshadow_block_tree_node_initialize(
	          &block_tree_node,
	          0,
	          1024,
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

#if defined( HAVE_VSHADOW_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvshadow_block_tree_node_initialize with malloc failing
		 */
		vshadow_test_malloc_attempts_before_fail = test_number;

		result = libvshadow_block_tree_node_initialize(
		          &block_tree_node,
		          0,
		          1024,
		          256,
		          &error );

		if( vshadow_test_malloc_attempts_before_fail != -1 )
		{
			vshadow_test_malloc_attempts_before_fail = -1;

			if( block_tree_node != NULL )
			{
				libvshadow_block_tree_node_free(
				 &block_tree_node,
				 NULL,
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
			 "block_tree_node",
			 block_tree_node );

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
		/* Test libvshadow_block_tree_node_initialize with memset failing
		 */
		vshadow_test_memset_attempts_before_fail = test_number;

		result = libvshadow_block_tree_node_initialize(
		          &block_tree_node,
		          0,
		          1024,
		          256,
		          &error );

		if( vshadow_test_memset_attempts_before_fail != -1 )
		{
			vshadow_test_memset_attempts_before_fail = -1;

			if( block_tree_node != NULL )
			{
				libvshadow_block_tree_node_free(
				 &block_tree_node,
				 NULL,
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
			 "block_tree_node",
			 block_tree_node );

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
	if( block_tree_node != NULL )
	{
		libvshadow_block_tree_node_free(
		 &block_tree_node,
		 NULL,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_block_tree_node_free function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_tree_node_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvshadow_block_tree_node_free(
	          NULL,
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

/* Tests the libvshadow_block_tree_node_get_sub_node_at_offset and
 * libvshadow_block_tree_node_set_sub_node_at_offset functions
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_tree_node_sub_node_at_offset(
     void )
{
	libcerror_error_t *error                              = NULL;
	libvshadow_block_tree_node_t *branch_node             = NULL;
	libvshadow_block_tree_node_t *leaf_node               = NULL;
	libvshadow_block_tree_node_t *retrieved_sub_node      = NULL;
	libvshadow_block_tree_node_t *sub_node                = NULL;
	int result                                            = 0;

	/* Initialize branch node (size / leaf_value_size > 256) and leaf node
	 */
	result = libvshadow_block_tree_node_initialize(
	          &branch_node,
	          0,
	          0x10000000ULL,
	          0x4000,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "branch_node",
	 branch_node );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_tree_node_initialize(
	          &leaf_node,
	          0,
	          0x40000,
	          0x4000,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "leaf_node",
	 leaf_node );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_tree_node_initialize(
	          &sub_node,
	          0,
	          branch_node->sub_node_size,
	          0x4000,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "sub_node",
	 sub_node );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvshadow_block_tree_node_set_sub_node_at_offset(
	          branch_node,
	          0,
	          sub_node,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	sub_node = NULL;

	result = libvshadow_block_tree_node_get_sub_node_at_offset(
	          branch_node,
	          0,
	          &retrieved_sub_node,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "retrieved_sub_node",
	 retrieved_sub_node );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases for get_sub_node_at_offset
	 */
	result = libvshadow_block_tree_node_get_sub_node_at_offset(
	          NULL,
	          0,
	          &retrieved_sub_node,
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

	result = libvshadow_block_tree_node_get_sub_node_at_offset(
	          leaf_node,
	          0,
	          &retrieved_sub_node,
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

	result = libvshadow_block_tree_node_get_sub_node_at_offset(
	          branch_node,
	          -1,
	          &retrieved_sub_node,
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

	result = libvshadow_block_tree_node_get_sub_node_at_offset(
	          branch_node,
	          0x10000000LL,
	          &retrieved_sub_node,
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

	result = libvshadow_block_tree_node_get_sub_node_at_offset(
	          branch_node,
	          0,
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

	/* Test error cases for set_sub_node_at_offset
	 */
	result = libvshadow_block_tree_node_set_sub_node_at_offset(
	          NULL,
	          0,
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

	result = libvshadow_block_tree_node_set_sub_node_at_offset(
	          leaf_node,
	          0,
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

	result = libvshadow_block_tree_node_set_sub_node_at_offset(
	          branch_node,
	          -1,
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

	result = libvshadow_block_tree_node_set_sub_node_at_offset(
	          branch_node,
	          0x10000000LL,
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

	/* Clean up
	 */
	result = libvshadow_block_tree_node_free(
	          &leaf_node,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "leaf_node",
	 leaf_node );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_tree_node_free(
	          &branch_node,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "branch_node",
	 branch_node );

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
	if( sub_node != NULL )
	{
		libvshadow_block_tree_node_free(
		 &sub_node,
		 NULL,
		 NULL );
	}
	if( leaf_node != NULL )
	{
		libvshadow_block_tree_node_free(
		 &leaf_node,
		 NULL,
		 NULL );
	}
	if( branch_node != NULL )
	{
		libvshadow_block_tree_node_free(
		 &branch_node,
		 NULL,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_block_tree_node_get_leaf_value_at_offset and
 * libvshadow_block_tree_node_set_leaf_value_at_offset functions
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_tree_node_leaf_value_at_offset(
     void )
{
	libcerror_error_t *error                              = NULL;
	libvshadow_block_descriptor_t *block_descriptor       = NULL;
	libvshadow_block_descriptor_t *retrieved_descriptor   = NULL;
	libvshadow_block_tree_node_t *branch_node             = NULL;
	libvshadow_block_tree_node_t *leaf_node               = NULL;
	off64_t block_offset                                  = 0;
	int result                                            = 0;

	/* Initialize test
	 */
	result = libvshadow_block_tree_node_initialize(
	          &branch_node,
	          0,
	          0x10000000ULL,
	          0x4000,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "branch_node",
	 branch_node );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_tree_node_initialize(
	          &leaf_node,
	          0,
	          0x40000,
	          0x4000,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "leaf_node",
	 leaf_node );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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
	result = libvshadow_block_tree_node_set_leaf_value_at_offset(
	          leaf_node,
	          0x4000,
	          block_descriptor,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_tree_node_get_leaf_value_at_offset(
	          leaf_node,
	          0x4123,
	          &retrieved_descriptor,
	          &block_offset,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "retrieved_descriptor",
	 retrieved_descriptor );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "block_offset",
	 block_offset,
	 (int64_t) 0x0123 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases for get_leaf_value_at_offset
	 */
	result = libvshadow_block_tree_node_get_leaf_value_at_offset(
	          NULL,
	          0,
	          &retrieved_descriptor,
	          &block_offset,
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

	result = libvshadow_block_tree_node_get_leaf_value_at_offset(
	          branch_node,
	          0,
	          &retrieved_descriptor,
	          &block_offset,
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

	result = libvshadow_block_tree_node_get_leaf_value_at_offset(
	          leaf_node,
	          -1,
	          &retrieved_descriptor,
	          &block_offset,
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

	result = libvshadow_block_tree_node_get_leaf_value_at_offset(
	          leaf_node,
	          0x40000,
	          &retrieved_descriptor,
	          &block_offset,
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

	result = libvshadow_block_tree_node_get_leaf_value_at_offset(
	          leaf_node,
	          0,
	          &retrieved_descriptor,
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

	result = libvshadow_block_tree_node_get_leaf_value_at_offset(
	          leaf_node,
	          0,
	          NULL,
	          &block_offset,
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

	/* Test error cases for set_leaf_value_at_offset
	 */
	result = libvshadow_block_tree_node_set_leaf_value_at_offset(
	          NULL,
	          0,
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

	result = libvshadow_block_tree_node_set_leaf_value_at_offset(
	          branch_node,
	          0,
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

	result = libvshadow_block_tree_node_set_leaf_value_at_offset(
	          leaf_node,
	          -1,
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

	result = libvshadow_block_tree_node_set_leaf_value_at_offset(
	          leaf_node,
	          0x40000,
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

	/* Clean up
	 */
	result = libvshadow_block_tree_node_free(
	          &leaf_node,
	          (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_block_descriptor_free,
	          &error );

	block_descriptor = NULL;

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "leaf_node",
	 leaf_node );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_tree_node_free(
	          &branch_node,
	          NULL,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "branch_node",
	 branch_node );

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
	if( leaf_node != NULL )
	{
		libvshadow_block_tree_node_free(
		 &leaf_node,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_block_descriptor_free,
		 NULL );
	}
	else if( block_descriptor != NULL )
	{
		libvshadow_block_descriptor_free(
		 &block_descriptor,
		 NULL );
	}
	if( branch_node != NULL )
	{
		libvshadow_block_tree_node_free(
		 &branch_node,
		 NULL,
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
	 "libvshadow_block_tree_node_initialize",
	 vshadow_test_block_tree_node_initialize );

	VSHADOW_TEST_RUN(
	 "libvshadow_block_tree_node_free",
	 vshadow_test_block_tree_node_free );

	VSHADOW_TEST_RUN(
	 "libvshadow_block_tree_node_sub_node_at_offset",
	 vshadow_test_block_tree_node_sub_node_at_offset );

	VSHADOW_TEST_RUN(
	 "libvshadow_block_tree_node_leaf_value_at_offset",
	 vshadow_test_block_tree_node_leaf_value_at_offset );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */
}

