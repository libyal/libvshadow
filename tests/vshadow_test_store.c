/*
 * Library store type test program
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vshadow_test_functions.h"
#include "vshadow_test_getopt.h"
#include "vshadow_test_libcerror.h"
#include "vshadow_test_libvshadow.h"
#include "vshadow_test_macros.h"
#include "vshadow_test_memory.h"
#include "vshadow_test_unused.h"

#include "../libvshadow/libvshadow_store.h"
#include "../libvshadow/libvshadow_volume.h"

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

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make vshadow_test_store generate verbose output
#define VSHADOW_TEST_STORE_VERBOSE
 */

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


#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

/* Tests the libvshadow_store_initialize function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libvshadow_store_t *store       = NULL;
	libvshadow_volume_t *volume     = NULL;
	int result                      = 0;

#if defined( HAVE_VSHADOW_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

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

	store = NULL;

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

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

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvshadow_store_initialize with malloc failing
		 */
		vshadow_test_malloc_attempts_before_fail = test_number;

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
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libvshadow_store_initialize with memset failing
		 */
		vshadow_test_memset_attempts_before_fail = test_number;

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

/* Tests the libvshadow_store_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_read_buffer(
     libvshadow_store_t *store )
{
	uint8_t buffer[ 16 ];

	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;
	int result               = 0;

	/* Determine size
	 */
	result = libvshadow_store_get_volume_size(
	          store,
	          &size,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libvshadow_store_seek_offset(
	          store,
	          0,
	          SEEK_SET,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( size > 16 )
	{
		read_count = libvshadow_store_read_buffer(
		              store,
		              buffer,
		              16,
		              &error );

		VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 16 );

		VSHADOW_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
/* TODO read on size boundary */
/* TODO read beyond size boundary */

	/* Reset offset to 0
	 */
	offset = libvshadow_store_seek_offset(
	          store,
	          0,
	          SEEK_SET,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libvshadow_store_read_buffer(
	              NULL,
	              buffer,
	              16,
	              &error );

	VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvshadow_store_read_buffer(
	              store,
	              NULL,
	              16,
	              &error );

	VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvshadow_store_read_buffer(
	              store,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	VSHADOW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

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

/* Tests the libvshadow_store_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_seek_offset(
     libvshadow_store_t *store )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	off64_t offset           = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_store_get_volume_size(
	          store,
	          &size,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvshadow_store_seek_offset(
	          store,
	          1024,
	          SEEK_SET,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 1024 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvshadow_store_seek_offset(
	          store,
	          -512,
	          SEEK_CUR,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 512 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvshadow_store_seek_offset(
	          store,
	          0,
	          SEEK_END,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) size );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvshadow_store_seek_offset(
	          store,
	          (off64_t) ( size + 512 ),
	          SEEK_SET,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) ( size + 512 ) );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libvshadow_store_seek_offset(
	          store,
	          0,
	          SEEK_SET,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VSHADOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libvshadow_store_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libvshadow_store_seek_offset(
	          store,
	          -1,
	          SEEK_SET,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libvshadow_store_seek_offset(
	          store,
	          -1,
	          SEEK_CUR,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VSHADOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	offset = libvshadow_store_seek_offset(
	          store,
	          (off64_t) ( -1 * ( size + 1 ) ),
	          SEEK_END,
	          &error );

	VSHADOW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

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

/* Tests the libvshadow_store_get_offset function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_get_offset(
     libvshadow_store_t *store )
{
	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_store_get_offset(
	          store,
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
	result = libvshadow_store_get_offset(
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

	result = libvshadow_store_get_offset(
	          store,
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

/* Tests the libvshadow_store_get_size function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_get_size(
     libvshadow_store_t *store )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_store_get_size(
	          store,
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
	result = libvshadow_store_get_size(
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

	result = libvshadow_store_get_size(
	          store,
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

/* Tests the libvshadow_store_get_volume_size function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_get_volume_size(
     libvshadow_store_t *store )
{
	libcerror_error_t *error = NULL;
	size64_t volume_size     = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_store_get_volume_size(
	          store,
	          &volume_size,
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
	result = libvshadow_store_get_volume_size(
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

	result = libvshadow_store_get_volume_size(
	          store,
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

/* Tests the libvshadow_store_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_get_identifier(
     libvshadow_store_t *store )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_store_get_identifier(
	          store,
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
	result = libvshadow_store_get_identifier(
	          NULL,
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

	result = libvshadow_store_get_identifier(
	          store,
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

	result = libvshadow_store_get_identifier(
	          store,
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

	result = libvshadow_store_get_identifier(
	          store,
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

/* Tests the libvshadow_store_get_creation_time function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_get_creation_time(
     libvshadow_store_t *store )
{
	libcerror_error_t *error = NULL;
	uint64_t filetime        = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_store_get_creation_time(
	          store,
	          &filetime,
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
	result = libvshadow_store_get_creation_time(
	          NULL,
	          &filetime,
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

	result = libvshadow_store_get_creation_time(
	          store,
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

/* Tests the libvshadow_store_get_copy_identifier function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_get_copy_identifier(
     libvshadow_store_t *store )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_store_get_copy_identifier(
	          store,
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
	result = libvshadow_store_get_copy_identifier(
	          NULL,
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

	result = libvshadow_store_get_copy_identifier(
	          store,
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

	result = libvshadow_store_get_copy_identifier(
	          store,
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

	result = libvshadow_store_get_copy_identifier(
	          store,
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

/* Tests the libvshadow_store_get_copy_set_identifier function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_get_copy_set_identifier(
     libvshadow_store_t *store )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_store_get_copy_set_identifier(
	          store,
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
	result = libvshadow_store_get_copy_set_identifier(
	          NULL,
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

	result = libvshadow_store_get_copy_set_identifier(
	          store,
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

	result = libvshadow_store_get_copy_set_identifier(
	          store,
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

	result = libvshadow_store_get_copy_set_identifier(
	          store,
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

/* Tests the libvshadow_store_get_number_of_blocks function
 * Returns 1 if successful or 0 if not
 */
int vshadow_test_store_get_number_of_blocks(
     libvshadow_store_t *store )
{
	libcerror_error_t *error = NULL;
	int number_of_blocks     = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvshadow_store_get_number_of_blocks(
	          store,
	          &number_of_blocks,
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
	result = libvshadow_store_get_number_of_blocks(
	          NULL,
	          &number_of_blocks,
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

	result = libvshadow_store_get_number_of_blocks(
	          store,
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
	libvshadow_store_t *store         = NULL;
	libvshadow_volume_t *volume       = NULL;
	system_character_t *option_offset = NULL;
	system_character_t *source        = NULL;
	system_integer_t option           = 0;
	size_t string_length              = 0;
	off64_t volume_offset             = 0;
	int number_of_stores              = 0;
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
#if defined( HAVE_DEBUG_OUTPUT ) && defined( VSHADOW_TEST_STORE_VERBOSE )
	libvshadow_notify_set_verbose(
	 1 );
	libvshadow_notify_set_stream(
	 stderr,
	 NULL );
#endif

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

	VSHADOW_TEST_RUN(
	 "libvshadow_store_initialize",
	 vshadow_test_store_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

	VSHADOW_TEST_RUN(
	 "libvshadow_store_free",
	 vshadow_test_store_free );

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

		if( number_of_stores > 0 )
		{
			/* Initialize store for tests
			 */
			result = libvshadow_volume_get_store(
			          volume,
			          number_of_stores - 1,
			          &store,
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

			/* TODO add tests for libvshadow_store_has_in_volume_data */

			/* TODO add tests for libvshadow_internal_store_read_buffer_from_file_io_handle */

			VSHADOW_TEST_RUN_WITH_ARGS(
			 "libvshadow_store_read_buffer",
			 vshadow_test_store_read_buffer,
			 store );

			/* TODO add tests for libvshadow_store_read_buffer_from_file_io_handle */

			/* TODO add tests for libvshadow_store_read_buffer_at_offset */

			/* TODO add tests for libvshadow_internal_store_seek_offset */

			VSHADOW_TEST_RUN_WITH_ARGS(
			 "libvshadow_store_seek_offset",
			 vshadow_test_store_seek_offset,
			 store );

#if defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT )

			VSHADOW_TEST_RUN_WITH_ARGS(
			 "libvshadow_store_get_offset",
			 vshadow_test_store_get_offset,
			 store );

			VSHADOW_TEST_RUN_WITH_ARGS(
			 "libvshadow_store_get_size",
			 vshadow_test_store_get_size,
			 store );

			VSHADOW_TEST_RUN_WITH_ARGS(
			 "libvshadow_store_get_volume_size",
			 vshadow_test_store_get_volume_size,
			 store );

			VSHADOW_TEST_RUN_WITH_ARGS(
			 "libvshadow_store_get_identifier",
			 vshadow_test_store_get_identifier,
			 store );

			VSHADOW_TEST_RUN_WITH_ARGS(
			 "libvshadow_store_get_creation_time",
			 vshadow_test_store_get_creation_time,
			 store );

			VSHADOW_TEST_RUN_WITH_ARGS(
			 "libvshadow_store_get_copy_identifier",
			 vshadow_test_store_get_copy_identifier,
			 store );

			VSHADOW_TEST_RUN_WITH_ARGS(
			 "libvshadow_store_get_copy_set_identifier",
			 vshadow_test_store_get_copy_set_identifier,
			 store );

			/* TODO add tests for libvshadow_store_get_attribute_flags */

			VSHADOW_TEST_RUN_WITH_ARGS(
			 "libvshadow_store_get_number_of_blocks",
			 vshadow_test_store_get_number_of_blocks,
			 store );

			/* TODO add tests for libvshadow_store_get_block_by_index */

#endif /* defined( __GNUC__ ) && !defined( LIBVSHADOW_DLL_IMPORT ) */

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
		}
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
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

