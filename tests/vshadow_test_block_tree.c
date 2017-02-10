/*
 * Library block_tree functions testing program
 *
 * Copyright (C) 2011-2017, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vshadow_test_libcdata.h"
#include "vshadow_test_libcerror.h"
#include "vshadow_test_libvshadow.h"
#include "vshadow_test_macros.h"
#include "vshadow_test_memory.h"
#include "vshadow_test_unused.h"

#include "../libvshadow/libvshadow_block_descriptor.h"
#include "../libvshadow/libvshadow_block_tree.h"
#include "../libvshadow/libvshadow_definitions.h"

#if defined( __GNUC__ )

/* Tests the libvshadow_block_tree_insert function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_block_tree_insert(
     void )
{
	libcdata_btree_t *forward_block_tree            = NULL;
	libcdata_btree_t *reverse_block_tree            = NULL;
	libcerror_error_t *error                        = NULL;
	libvshadow_block_descriptor_t *block_descriptor = NULL;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libcdata_btree_initialize(
	          &forward_block_tree,
	          LIBVSHADOW_BLOCK_DESCRIPTORS_TREE_MAXIMUM_NUMBER_OF_SUB_NODES,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NOT_NULL(
         "forward_block_tree",
         forward_block_tree );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libcdata_btree_initialize(
	          &reverse_block_tree,
	          LIBVSHADOW_BLOCK_DESCRIPTORS_TREE_MAXIMUM_NUMBER_OF_SUB_NODES,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NOT_NULL(
         "reverse_block_tree",
         reverse_block_tree );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

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

	/* Test insert of block descriptor
	 */
	block_descriptor->original_offset = 0xc0008000;
	block_descriptor->relative_offset = 0x0419c000;
	block_descriptor->offset          = 0x38241c000;
	block_descriptor->flags           = 0x00000000;
	block_descriptor->bitmap          = 0x00000000;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test insert of block descriptor: flags 0x00000088
	 */
	block_descriptor->original_offset = 0xb7f20000;
	block_descriptor->relative_offset = 0x0006c000;
	block_descriptor->offset          = 0x37e2ec000;
	block_descriptor->flags           = 0x00000088;
	block_descriptor->bitmap          = 0x00000000;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test insert of block descriptor: is overlay flag
	 */
	block_descriptor->original_offset = 0xb7f1c000;
	block_descriptor->relative_offset = 0x0004c000;
	block_descriptor->offset          = 0x37e2cc000;
	block_descriptor->flags           = 0x00000002;
	block_descriptor->bitmap          = 0xff000000;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test insert of block descriptor: is overlay flag, overlapping offset range, alternating bitmap
	 */
	block_descriptor->original_offset = 0xb7f1c000;
	block_descriptor->relative_offset = 0x00000001;
	block_descriptor->offset          = 0x37e2cc000;
	block_descriptor->flags           = 0x00000002;
	block_descriptor->bitmap          = 0x00ff0000;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test insert of block descriptor: replace existing
	 */
	block_descriptor->original_offset = 0xb7f1c000;
	block_descriptor->relative_offset = 0x04184000;
	block_descriptor->offset          = 0x382404000;
	block_descriptor->flags           = 0x00000000;
	block_descriptor->bitmap          = 0x00000000;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test insert of block descriptor: extend existing with overlay
	 */
	block_descriptor->original_offset = 0xb7f20000;
	block_descriptor->relative_offset = 0x00050000;
	block_descriptor->offset          = 0x37e2d0000;
	block_descriptor->flags           = 0x00000002;
	block_descriptor->bitmap          = 0x000000ff;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test insert of block descriptor: extend existing with overlay
	 */
	block_descriptor->original_offset = 0xb7f20000;
	block_descriptor->relative_offset = 0x00000001;
	block_descriptor->offset          = 0x37e2d0000;
	block_descriptor->flags           = 0x00000002;
	block_descriptor->bitmap          = 0x0000ff00;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test insert of block descriptor: is forwarder flag, original_offset equals relative_offset
	 */
	block_descriptor->original_offset = 0xbbed8000;
	block_descriptor->relative_offset = 0xbbed8000;
	block_descriptor->offset          = 0x3823b8000;
	block_descriptor->flags           = 0x00000001;
	block_descriptor->bitmap          = 0x00000000;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test insert of block descriptor: is forwarder flag
	 */
	block_descriptor->original_offset = 0xb7f1c000;
	block_descriptor->relative_offset = 0x0004c000;
	block_descriptor->offset          = 0x37e2cc000;
	block_descriptor->flags           = 0x00000001;
	block_descriptor->bitmap          = 0x00000000;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test insert of block descriptor: is forwarder flag, override existing forwarder
	 */
	block_descriptor->original_offset = 0x0004c000;
	block_descriptor->relative_offset = 0xb7f1c000;
	block_descriptor->offset          = 0x37e2cc000;
	block_descriptor->flags           = 0x00000001;
	block_descriptor->bitmap          = 0x00000000;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test insert of block descriptor: is forwarder flag
	 */
	block_descriptor->original_offset = 0xb7f38000;
	block_descriptor->relative_offset = 0x00084000;
	block_descriptor->offset          = 0x37e304000;
	block_descriptor->flags           = 0x00000001;
	block_descriptor->bitmap          = 0x00000000;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test insert of block descriptor: is forwarder flag, replaces existing forwarder
	 */
	block_descriptor->original_offset = 0xb7f44000;
	block_descriptor->relative_offset = 0x00084000;
	block_descriptor->offset          = 0x37e310000;
	block_descriptor->flags           = 0x00000001;
	block_descriptor->bitmap          = 0x00000000;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test insert of block descriptor: not used flag
	 */
	block_descriptor->original_offset = 0x00001000;
	block_descriptor->relative_offset = 0x00001000;
	block_descriptor->offset          = 0x00001000;
	block_descriptor->flags           = 0x00000004;
	block_descriptor->bitmap          = 0x00000000;

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
	          block_descriptor,
	          0,
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
	result = libvshadow_block_tree_insert(
	          NULL,
	          reverse_block_tree,
	          block_descriptor,
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

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          NULL,
	          block_descriptor,
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

	result = libvshadow_block_tree_insert(
	          forward_block_tree,
	          reverse_block_tree,
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

	/* Clean up
	 */
	result = libcdata_btree_free(
	          &reverse_block_tree,
	          (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_block_descriptor_free_reverse,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "reverse_block_tree",
         reverse_block_tree );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libcdata_btree_free(
	          &forward_block_tree,
	          (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_block_descriptor_free,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        VSHADOW_TEST_ASSERT_IS_NULL(
         "forward_block_tree",
         forward_block_tree );

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
	if( reverse_block_tree != NULL )
	{
		libcdata_btree_free(
		 &reverse_block_tree,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_block_descriptor_free_reverse,
		 NULL );
	}
	if( forward_block_tree != NULL )
	{
		libcdata_btree_free(
		 &forward_block_tree,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_block_descriptor_free,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) */

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

#if defined( __GNUC__ )

	VSHADOW_TEST_RUN(
	 "libvshadow_block_tree_insert",
	 vshadow_test_block_tree_insert );

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

