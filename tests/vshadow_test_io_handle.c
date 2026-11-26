/*
 * Library io_handle type test program
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

/* Tests the libvshadow_io_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_io_handle_initialize(
     void )
{
	libcerror_error_t *error          = NULL;
	libvshadow_io_handle_t *io_handle = NULL;
	int result                        = 0;

#if defined( HAVE_VSHADOW_TEST_MEMORY )
	int number_of_malloc_fail_tests   = 1;
	int number_of_memset_fail_tests   = 1;
	int test_number                   = 0;
#endif

	/* Test regular cases
	 */
	result = libvshadow_io_handle_initialize(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_io_handle_free(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_io_handle_initialize(
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

	io_handle = (libvshadow_io_handle_t *) 0x12345678UL;

	result = libvshadow_io_handle_initialize(
	          &io_handle,
	          &error );

	io_handle = NULL;

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
		/* Test libvshadow_io_handle_initialize with malloc failing
		 */
		vshadow_test_malloc_attempts_before_fail = test_number;

		result = libvshadow_io_handle_initialize(
		          &io_handle,
		          &error );

		if( vshadow_test_malloc_attempts_before_fail != -1 )
		{
			vshadow_test_malloc_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				libvshadow_io_handle_free(
				 &io_handle,
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
			 "io_handle",
			 io_handle );

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
		/* Test libvshadow_io_handle_initialize with memset failing
		 */
		vshadow_test_memset_attempts_before_fail = test_number;

		result = libvshadow_io_handle_initialize(
		          &io_handle,
		          &error );

		if( vshadow_test_memset_attempts_before_fail != -1 )
		{
			vshadow_test_memset_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				libvshadow_io_handle_free(
				 &io_handle,
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
			 "io_handle",
			 io_handle );

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
	if( io_handle != NULL )
	{
		libvshadow_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_io_handle_free function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_io_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvshadow_io_handle_free(
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

/* Tests the libvshadow_io_handle_clear function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_io_handle_clear(
     void )
{
	libcerror_error_t *error          = NULL;
	libvshadow_io_handle_t *io_handle = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libvshadow_io_handle_initialize(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvshadow_io_handle_clear(
	          io_handle,
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
	result = libvshadow_io_handle_clear(
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

	/* Test libvshadow_io_handle_clear with memset failing
	 */
	vshadow_test_memset_attempts_before_fail = 0;

	result = libvshadow_io_handle_clear(
	          io_handle,
	          &error );

	if( vshadow_test_memset_attempts_before_fail != -1 )
	{
		vshadow_test_memset_attempts_before_fail = -1;
	}
	else
	{
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
#endif /* defined( HAVE_VSHADOW_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libvshadow_io_handle_free(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( io_handle != NULL )
	{
		libvshadow_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_io_handle_check_if_block_first_read function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_io_handle_check_if_block_first_read(
     void )
{
	libcerror_error_t *error            = NULL;
	libvshadow_block_tree_t *block_tree = NULL;
	libvshadow_io_handle_t *io_handle   = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libvshadow_io_handle_initialize(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_block_tree_initialize(
	          &block_tree,
	          0x100000ULL,
	          0x4000,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "block_tree",
	 block_tree );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular case: first read
	 */
	result = libvshadow_io_handle_check_if_block_first_read(
	          io_handle,
	          block_tree,
	          0x4000,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error case: duplicate read (already exists)
	 */
	result = libvshadow_io_handle_check_if_block_first_read(
	          io_handle,
	          block_tree,
	          0x4000,
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

	/* Test error cases
	 */
	result = libvshadow_io_handle_check_if_block_first_read(
	          NULL,
	          block_tree,
	          0x8000,
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

	result = libvshadow_io_handle_check_if_block_first_read(
	          io_handle,
	          NULL,
	          0x8000,
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

	result = libvshadow_io_handle_check_if_block_first_read(
	          io_handle,
	          block_tree,
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

#if defined( HAVE_VSHADOW_TEST_MEMORY )

	/* Test libvshadow_io_handle_check_if_block_first_read with malloc failing
	 */
	vshadow_test_malloc_attempts_before_fail = 0;

	result = libvshadow_io_handle_check_if_block_first_read(
	          io_handle,
	          block_tree,
	          0x8000,
	          &error );

	if( vshadow_test_malloc_attempts_before_fail != -1 )
	{
		vshadow_test_malloc_attempts_before_fail = -1;
	}
	else
	{
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
#endif /* defined( HAVE_VSHADOW_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libvshadow_block_tree_free(
	          &block_tree,
	          (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_block_descriptor_free,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "block_tree",
	 block_tree );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_io_handle_free(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( block_tree != NULL )
	{
		libvshadow_block_tree_free(
		 &block_tree,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_block_descriptor_free,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libvshadow_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_io_handle_read_volume_header_data function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_io_handle_read_volume_header_data(
     void )
{
	uint8_t header_data[ 512 ];

	libcerror_error_t *error          = NULL;
	libvshadow_io_handle_t *io_handle = NULL;
	off64_t catalog_offset            = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libvshadow_io_handle_initialize(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	memory_set(
	 header_data,
	 0,
	 512 );

	memory_copy(
	 header_data,
	 vshadow_vss_identifier,
	 16 );

	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 16 ] ),
	 1 );

	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 20 ] ),
	 LIBVSHADOW_RECORD_TYPE_VOLUME_HEADER );

	byte_stream_copy_from_uint64_little_endian(
	 &( header_data[ 48 ] ),
	 0x8000ULL );

	/* Test regular cases (version 1 and version 2)
	 */
	result = libvshadow_io_handle_read_volume_header_data(
	          io_handle,
	          header_data,
	          512,
	          &catalog_offset,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "catalog_offset",
	 catalog_offset,
	 (int64_t) 0x8000 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 16 ] ),
	 2 );

	result = libvshadow_io_handle_read_volume_header_data(
	          io_handle,
	          header_data,
	          512,
	          &catalog_offset,
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
	result = libvshadow_io_handle_read_volume_header_data(
	          NULL,
	          header_data,
	          512,
	          &catalog_offset,
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

	result = libvshadow_io_handle_read_volume_header_data(
	          io_handle,
	          NULL,
	          512,
	          &catalog_offset,
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

	result = libvshadow_io_handle_read_volume_header_data(
	          io_handle,
	          header_data,
	          511,
	          &catalog_offset,
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

	result = libvshadow_io_handle_read_volume_header_data(
	          io_handle,
	          header_data,
	          (size_t) SSIZE_MAX + 1,
	          &catalog_offset,
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

	result = libvshadow_io_handle_read_volume_header_data(
	          io_handle,
	          header_data,
	          512,
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

	/* Unsupported version
	 */
	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 16 ] ),
	 3 );

	result = libvshadow_io_handle_read_volume_header_data(
	          io_handle,
	          header_data,
	          512,
	          &catalog_offset,
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

	/* Unsupported record type
	 */
	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 16 ] ),
	 1 );

	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 20 ] ),
	 99 );

	result = libvshadow_io_handle_read_volume_header_data(
	          io_handle,
	          header_data,
	          512,
	          &catalog_offset,
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

	/* Invalid identifier
	 */
	header_data[ 0 ] ^= 0xff;

	result = libvshadow_io_handle_read_volume_header_data(
	          io_handle,
	          header_data,
	          512,
	          &catalog_offset,
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
	result = libvshadow_io_handle_free(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( io_handle != NULL )
	{
		libvshadow_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_io_handle_read_volume_header function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_io_handle_read_volume_header(
     void )
{
	uint8_t header_data[ 512 ];

	libbfio_handle_t *file_io_handle  = NULL;
	libcerror_error_t *error          = NULL;
	libvshadow_io_handle_t *io_handle = NULL;
	off64_t catalog_offset            = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libvshadow_io_handle_initialize(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	memory_set(
	 header_data,
	 0,
	 512 );

	memory_copy(
	 header_data,
	 vshadow_vss_identifier,
	 16 );

	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 16 ] ),
	 1 );

	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 20 ] ),
	 LIBVSHADOW_RECORD_TYPE_VOLUME_HEADER );

	byte_stream_copy_from_uint64_little_endian(
	 &( header_data[ 48 ] ),
	 0x4000ULL );

	result = libbfio_memory_range_initialize(
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

	/* Test regular case
	 */
	result = libvshadow_io_handle_read_volume_header(
	          io_handle,
	          file_io_handle,
	          0,
	          &catalog_offset,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "catalog_offset",
	 catalog_offset,
	 (int64_t) 0x4000 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_io_handle_read_volume_header(
	          NULL,
	          file_io_handle,
	          0,
	          &catalog_offset,
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

	result = libvshadow_io_handle_read_volume_header(
	          io_handle,
	          NULL,
	          0,
	          &catalog_offset,
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

	result = libvshadow_io_handle_read_volume_header(
	          io_handle,
	          file_io_handle,
	          -1,
	          &catalog_offset,
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

	/* Invalid header data inside file
	 */
	header_data[ 0 ] ^= 0xff;

	result = libvshadow_io_handle_read_volume_header(
	          io_handle,
	          file_io_handle,
	          0,
	          &catalog_offset,
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
	 "file_io_handle",
	 file_io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_io_handle_free(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( io_handle != NULL )
	{
		libvshadow_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_io_handle_read_catalog_header_data function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_io_handle_read_catalog_header_data(
     void )
{
	uint8_t header_data[ 128 ];

	libcerror_error_t *error          = NULL;
	libvshadow_io_handle_t *io_handle = NULL;
	off64_t next_offset               = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libvshadow_io_handle_initialize(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	memory_set(
	 header_data,
	 0,
	 128 );

	memory_copy(
	 header_data,
	 vshadow_vss_identifier,
	 16 );

	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 16 ] ),
	 1 );

	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 20 ] ),
	 LIBVSHADOW_RECORD_TYPE_CATALOG );

	byte_stream_copy_from_uint64_little_endian(
	 &( header_data[ 40 ] ),
	 0x4000ULL );

	/* Test regular case
	 */
	result = libvshadow_io_handle_read_catalog_header_data(
	          io_handle,
	          header_data,
	          128,
	          &next_offset,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "next_offset",
	 next_offset,
	 (int64_t) 0x4000 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvshadow_io_handle_read_catalog_header_data(
	          NULL,
	          header_data,
	          128,
	          &next_offset,
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

	result = libvshadow_io_handle_read_catalog_header_data(
	          io_handle,
	          NULL,
	          128,
	          &next_offset,
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

	result = libvshadow_io_handle_read_catalog_header_data(
	          io_handle,
	          header_data,
	          127,
	          &next_offset,
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

	result = libvshadow_io_handle_read_catalog_header_data(
	          io_handle,
	          header_data,
	          (size_t) SSIZE_MAX + 1,
	          &next_offset,
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

	result = libvshadow_io_handle_read_catalog_header_data(
	          io_handle,
	          header_data,
	          128,
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

	/* Next offset exceeds INT64_MAX
	 */
	byte_stream_copy_from_uint64_little_endian(
	 &( header_data[ 40 ] ),
	 (uint64_t) INT64_MAX + 1 );

	result = libvshadow_io_handle_read_catalog_header_data(
	          io_handle,
	          header_data,
	          128,
	          &next_offset,
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

	byte_stream_copy_from_uint64_little_endian(
	 &( header_data[ 40 ] ),
	 (uint64_t) 0ULL );

	/* Unsupported record type
	 */
	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 20 ] ),
	 99 );

	result = libvshadow_io_handle_read_catalog_header_data(
	          io_handle,
	          header_data,
	          128,
	          &next_offset,
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

	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 20 ] ),
	 LIBVSHADOW_RECORD_TYPE_CATALOG );

	/* Unsupported version
	 */
	byte_stream_copy_from_uint32_little_endian(
	 &( header_data[ 16 ] ),
	 2 );

	result = libvshadow_io_handle_read_catalog_header_data(
	          io_handle,
	          header_data,
	          128,
	          &next_offset,
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

	/* Invalid identifier
	 */
	header_data[ 0 ] ^= 0xff;

	result = libvshadow_io_handle_read_catalog_header_data(
	          io_handle,
	          header_data,
	          128,
	          &next_offset,
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
	result = libvshadow_io_handle_free(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( io_handle != NULL )
	{
		libvshadow_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvshadow_io_handle_read_catalog function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_io_handle_read_catalog(
     void )
{
	libbfio_handle_t *file_io_handle          = NULL;
	libcdata_array_t *store_descriptors_array = NULL;
	libcerror_error_t *error                  = NULL;
	libvshadow_io_handle_t *io_handle         = NULL;
	uint8_t *catalog_data                     = NULL;
	size64_t volume_size                      = 0;
	int number_of_entries                     = 0;
	int result                                = 0;

	/* Initialize test with 2 chained 16 KiB catalog blocks
	 */
	catalog_data = (uint8_t *) memory_allocate(
	                            0x8000 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "catalog_data",
	 catalog_data );

	memory_set(
	 catalog_data,
	 0,
	 0x8000 );

	/* Block 0 header at offset 0 -> next_offset = 0x4000
	 */
	memory_copy(
	 catalog_data,
	 vshadow_vss_identifier,
	 16 );
	byte_stream_copy_from_uint32_little_endian(
	 &( catalog_data[ 16 ] ),
	 1 );
	byte_stream_copy_from_uint32_little_endian(
	 &( catalog_data[ 20 ] ),
	 LIBVSHADOW_RECORD_TYPE_CATALOG );
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 40 ] ),
	 0x4000ULL );

	/* Entry 0 (offset 128): type 1 (unused)
	 */
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 128 ] ),
	 (uint64_t) 1ULL );

	/* Entry 1 (offset 256): type 2 (store descriptor #1, id[0]=0x11, creation_time=100)
	 */
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 256 ] ),
	 (uint64_t) 2ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 256 + 8 ] ),
	 (uint64_t) 0x100000ULL );
	catalog_data[ 256 + 16 ] = 0x11;
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 256 + 48 ] ),
	 (uint64_t) 100ULL );

	/* Entry 2 (offset 384): type 2 (store descriptor #2, id[0]=0x22, creation_time=200)
	 */
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 384 ] ),
	 (uint64_t) 2ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 384 + 8 ] ),
	 (uint64_t) 0x100000ULL );
	catalog_data[ 384 + 16 ] = 0x22;
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 384 + 48 ] ),
	 (uint64_t) 200ULL );

	/* Entry 3 (offset 512): type 3 matching store #1 (forces lookup by identifier)
	 */
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 512 ] ),
	 (uint64_t) 3ULL );
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 512 + 8 ] ),
	 0x8000ULL );
	catalog_data[ 512 + 16 ] = 0x11;
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 512 + 32 ] ),
	 0xc000ULL );

	/* Block 1 header at offset 0x4000 -> next_offset = 0
	 */
	memory_copy(
	 &( catalog_data[ 0x4000 ] ),
	 vshadow_vss_identifier,
	 16 );
	byte_stream_copy_from_uint32_little_endian(
	 &( catalog_data[ 0x4000 + 16 ] ),
	 1 );
	byte_stream_copy_from_uint32_little_endian(
	 &( catalog_data[ 0x4000 + 20 ] ),
	 LIBVSHADOW_RECORD_TYPE_CATALOG );

	result = libvshadow_io_handle_initialize(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->volume_size = 0x100000ULL;

	result = libcdata_array_initialize(
	          &store_descriptors_array,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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
	          catalog_data,
	          0x8000,
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

	/* Test regular case
	 */
	result = libvshadow_io_handle_read_catalog(
	          io_handle,
	          file_io_handle,
	          0,
	          &volume_size,
	          store_descriptors_array,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_UINT64(
	 "volume_size",
	 volume_size,
	 (uint64_t) 0x100000ULL );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdata_array_get_number_of_entries(
	          store_descriptors_array,
	          &number_of_entries,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "number_of_entries",
	 number_of_entries,
	 2 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Empty array for error cases
	 */
	result = libcdata_array_empty(
	          store_descriptors_array,
	          (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_store_descriptor_free,
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
	result = libvshadow_io_handle_read_catalog(
	          NULL,
	          file_io_handle,
	          0,
	          &volume_size,
	          store_descriptors_array,
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

	result = libvshadow_io_handle_read_catalog(
	          io_handle,
	          file_io_handle,
	          0,
	          NULL,
	          store_descriptors_array,
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

	result = libvshadow_io_handle_read_catalog(
	          io_handle,
	          NULL,
	          0,
	          &volume_size,
	          store_descriptors_array,
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

	/* Cycle detection: block 1 points back to offset 0x4000
	 */
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 0x4000 + 40 ] ),
	 0x4000ULL );

	result = libvshadow_io_handle_read_catalog(
	          io_handle,
	          file_io_handle,
	          0,
	          &volume_size,
	          store_descriptors_array,
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

	libcdata_array_empty(
	 store_descriptors_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_store_descriptor_free,
	 NULL );

	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 0x4000 + 40 ] ),
	 (uint64_t) 0ULL );

	/* Unsupported catalog entry type
	 */
	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 0x4000 + 128 ] ),
	 (uint64_t) 99ULL );

	result = libvshadow_io_handle_read_catalog(
	          io_handle,
	          file_io_handle,
	          0,
	          &volume_size,
	          store_descriptors_array,
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

	libcdata_array_empty(
	 store_descriptors_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_store_descriptor_free,
	 NULL );

	byte_stream_copy_from_uint64_little_endian(
	 &( catalog_data[ 0x4000 + 128 ] ),
	 (uint64_t) 0ULL );

	/* Invalid catalog header on block 1
	 */
	catalog_data[ 0x4000 ] ^= 0xff;

	result = libvshadow_io_handle_read_catalog(
	          io_handle,
	          file_io_handle,
	          0,
	          &volume_size,
	          store_descriptors_array,
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

	libcdata_array_empty(
	 store_descriptors_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_store_descriptor_free,
	 NULL );

	catalog_data[ 0x4000 ] ^= 0xff;

	/* Invalid volume_size == 0 causes catalog_block_tree initialization failure
	 */
	io_handle->volume_size = 0;

	result = libvshadow_io_handle_read_catalog(
	          io_handle,
	          file_io_handle,
	          0,
	          &volume_size,
	          store_descriptors_array,
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

	io_handle->volume_size = 0x100000ULL;

#if defined( HAVE_VSHADOW_TEST_MEMORY )

	/* Test libvshadow_io_handle_read_catalog with malloc failing
	 */
	vshadow_test_malloc_attempts_before_fail = 0;

	result = libvshadow_io_handle_read_catalog(
	          io_handle,
	          file_io_handle,
	          0,
	          &volume_size,
	          store_descriptors_array,
	          &error );

	if( vshadow_test_malloc_attempts_before_fail != -1 )
	{
		vshadow_test_malloc_attempts_before_fail = -1;
	}
	else
	{
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
#endif /* defined( HAVE_VSHADOW_TEST_MEMORY ) */

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
	 "file_io_handle",
	 file_io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdata_array_free(
	          &store_descriptors_array,
	          (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_store_descriptor_free,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "store_descriptors_array",
	 store_descriptors_array );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_io_handle_free(
	          &io_handle,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	memory_free(
	 catalog_data );

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
	if( store_descriptors_array != NULL )
	{
		libcdata_array_free(
		 &store_descriptors_array,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libvshadow_store_descriptor_free,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libvshadow_io_handle_free(
		 &io_handle,
		 NULL );
	}
	if( catalog_data != NULL )
	{
		memory_free(
		 catalog_data );
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
	 "libvshadow_io_handle_initialize",
	 vshadow_test_io_handle_initialize );

	VSHADOW_TEST_RUN(
	 "libvshadow_io_handle_free",
	 vshadow_test_io_handle_free );

	VSHADOW_TEST_RUN(
	 "libvshadow_io_handle_clear",
	 vshadow_test_io_handle_clear );

	VSHADOW_TEST_RUN(
	 "libvshadow_io_handle_check_if_block_first_read",
	 vshadow_test_io_handle_check_if_block_first_read );

	VSHADOW_TEST_RUN(
	 "libvshadow_io_handle_read_volume_header_data",
	 vshadow_test_io_handle_read_volume_header_data );

	VSHADOW_TEST_RUN(
	 "libvshadow_io_handle_read_volume_header",
	 vshadow_test_io_handle_read_volume_header );

	VSHADOW_TEST_RUN(
	 "libvshadow_io_handle_read_catalog_header_data",
	 vshadow_test_io_handle_read_catalog_header_data );

	VSHADOW_TEST_RUN(
	 "libvshadow_io_handle_read_catalog",
	 vshadow_test_io_handle_read_catalog );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */
}

