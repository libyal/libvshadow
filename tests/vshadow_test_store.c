/*
 * Library store type test program
 *
 * Copyright (C) 2011-2019, Joachim Metz <joachim.metz@gmail.com>
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

#include "vshadow_test_libcerror.h"
#include "vshadow_test_libvshadow.h"
#include "vshadow_test_macros.h"
#include "vshadow_test_memory.h"
#include "vshadow_test_unused.h"

#include "../libvshadow/libvshadow_store.h"
#include "../libvshadow/libvshadow_volume.h"

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

/* Tests the libvshadow_store_initialize function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_initialize(
     void )
{
	libcerror_error_t *error    = NULL;
	libvshadow_store_t *store   = NULL;
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

#ifdef TODO
/* TODO: add store descriptor for testing */

	/* Test store initialization
	 */
	result = libvshadow_store_initialize(
	          &store,
	          NULL,
	          NULL,
	          (libvshadow_internal_volume_t *) volume,
	          0,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "store",
	 store );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvshadow_store_free(
	          &store,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "store",
	 store );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* TODO */

	/* Test error cases
	 */
	result = libvshadow_store_initialize(
	          NULL,
	          NULL,
	          NULL,
	          (libvshadow_internal_volume_t *) volume,
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

	store = (libvshadow_store_t *) 0x12345678UL;

	result = libvshadow_store_initialize(
	          &store,
	          NULL,
	          NULL,
	          (libvshadow_internal_volume_t *) volume,
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

	store = NULL;

	result = libvshadow_store_initialize(
	          &store,
	          NULL,
	          NULL,
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

#ifdef TODO
/* TODO: add store descriptor for testing */
#if defined( HAVE_VSHADOW_TEST_MEMORY )

	/* Test libvshadow_store_initialize with malloc failing
	 */
	vshadow_test_malloc_attempts_before_fail = 0;

	result = libvshadow_store_initialize(
	          &store,
	          NULL,
	          NULL,
	          (libvshadow_internal_volume_t *) volume,
	          0,
	          &error );

	if( vshadow_test_malloc_attempts_before_fail != -1 )
	{
		vshadow_test_malloc_attempts_before_fail = -1;

		if( store != NULL )
		{
			libvshadow_store_free(
			 &store,
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
		 "store",
		 store );

		VSHADOW_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvshadow_store_initialize with memset failing
	 */
	vshadow_test_memset_attempts_before_fail = 0;

	result = libvshadow_store_initialize(
	          &store,
	          NULL,
	          NULL,
	          (libvshadow_internal_volume_t *) volume,
	          0,
	          &error );

	if( vshadow_test_memset_attempts_before_fail != -1 )
	{
		vshadow_test_memset_attempts_before_fail = -1;

		if( store != NULL )
		{
			libvshadow_store_free(
			 &store,
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
		 "store",
		 store );

		VSHADOW_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSHADOW_TEST_MEMORY ) */
#endif /* TODO */

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
	if( store != NULL )
	{
		libvshadow_store_free(
		 &store,
		 NULL );
	}
	if( volume != NULL )
	{
		libvshadow_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

/* Tests the libvshadow_store_free function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvshadow_store_free(
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
	 "libvshadow_store_initialize",
	 vshadow_test_store_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

	VSHADOW_TEST_RUN(
	 "libvshadow_store_free",
	 vshadow_test_store_free );

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

	/* TODO add tests for libvshadow_store_has_in_volume_data */
	/* TODO add tests for libvshadow_internal_store_read_buffer_from_file_io_handle */
	/* TODO add tests for libvshadow_store_read_buffer */
	/* TODO add tests for libvshadow_store_read_buffer_from_file_io_handle */
	/* TODO add tests for libvshadow_store_read_buffer_at_offset */
	/* TODO add tests for libvshadow_internal_store_seek_offset */
	/* TODO add tests for libvshadow_store_seek_offset */
	/* TODO add tests for libvshadow_store_get_offset */
	/* TODO add tests for libvshadow_store_get_size */
	/* TODO add tests for libvshadow_store_get_volume_size */
	/* TODO add tests for libvshadow_store_get_identifier */
	/* TODO add tests for libvshadow_store_get_creation_time */
	/* TODO add tests for libvshadow_store_get_copy_identifier */
	/* TODO add tests for libvshadow_store_get_copy_set_identifier */
	/* TODO add tests for libvshadow_store_get_attribute_flags */
	/* TODO add tests for libvshadow_store_get_number_of_blocks */
	/* TODO add tests for libvshadow_store_get_block_by_index */

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

