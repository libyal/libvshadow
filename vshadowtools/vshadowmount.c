/*
 * Mounts a Windows NT Volume Shadow Snapshot (VSS) volume
 *
 * Copyright (C) 2011-2013, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#include <stdio.h>

#if defined( HAVE_ERRNO_H )
#include <errno.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if !defined( WINAPI ) || defined( USE_CRT_FUNCTIONS )
#if defined( TIME_WITH_SYS_TIME )
#include <sys/time.h>
#include <time.h>
#elif defined( HAVE_SYS_TIME_H )
#include <sys/time.h>
#else
#include <time.h>
#endif
#endif

#if defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE )
#define FUSE_USE_VERSION	26

#if defined( HAVE_LIBFUSE )
#include <fuse.h>

#elif defined( HAVE_LIBOSXFUSE )
#include <osxfuse/fuse.h>
#endif

#elif defined( HAVE_LIBDOKAN )
#include <dokan.h>
#endif

#include "mount_handle.h"
#include "vshadowoutput.h"
#include "vshadowtools_libcerror.h"
#include "vshadowtools_libclocale.h"
#include "vshadowtools_libcnotify.h"
#include "vshadowtools_libcstring.h"
#include "vshadowtools_libcsystem.h"
#include "vshadowtools_libvshadow.h"

mount_handle_t *vshadowmount_mount_handle = NULL;
int vshadowmount_abort                    = 0;

/* Prints the executable usage mountrmation
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use vshadowmount to mount a Windows NT Volume Shadow Snapshot (VSS)\n"
	                 "volume\n\n" );

	fprintf( stream, "Usage: vshadowmount [ -o offset ] [ -X extended_options ]\n"
	                 "                    [ -hvV ] source mount_point\n\n" );

	fprintf( stream, "\tsource:      the source file or device\n" );
	fprintf( stream, "\tmount_point: the directory to serve as mount point\n\n" );

	fprintf( stream, "\t-h:          shows this help\n" );
	fprintf( stream, "\t-o:          specify the volume offset\n" );
	fprintf( stream, "\t-v:          verbose output to stderr\n"
	                 "\t             vshadowmount will remain running in the foreground\n" );
	fprintf( stream, "\t-V:          print version\n" );
	fprintf( stream, "\t-X:          extended options to pass to sub system\n" );
}

/* Signal handler for vshadowmount
 */
void vshadowmount_signal_handler(
      libcsystem_signal_t signal LIBCSYSTEM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_signal_handler";

	LIBCSYSTEM_UNREFERENCED_PARAMETER( signal )

	vshadowmount_abort = 1;

	if( vshadowmount_mount_handle != NULL )
	{
		if( mount_handle_signal_abort(
		     vshadowmount_mount_handle,
		     &error ) != 1 )
		{
			libcnotify_printf(
			 "%s: unable to signal mount handle to abort.\n",
			 function );

			libcnotify_print_error_backtrace(
			 error );
			libcerror_error_free(
			 &error );
		}
	}
	/* Force stdin to close otherwise any function reading it will remain blocked
	 */
	if( libcsystem_file_io_close(
	     0 ) != 0 )
	{
		libcnotify_printf(
		 "%s: unable to close stdin.\n",
		 function );
	}
}

#if defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE )

#if ( SIZEOF_OFF_T != 8 ) && ( SIZEOF_OFF_T != 4 )
#error Size of off_t not supported
#endif

static char *vshadowmount_fuse_path_prefix         = "/vss";
static size_t vshadowmount_fuse_path_prefix_length = 4;

/* Opens a file
 * Returns 0 if successful or a negative errno value otherwise
 */
int vshadowmount_fuse_open(
     const char *path,
     struct fuse_file_info *file_info )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_fuse_open";
	size_t path_length       = 0;
	int result               = 0;

	if( path == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		result = -EINVAL;

		goto on_error;
	}
	if( file_info == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file info.",
		 function );

		result = -EINVAL;

		goto on_error;
	}
	path_length = libcstring_narrow_string_length(
	               path );

	if( ( path_length <= vshadowmount_fuse_path_prefix_length )
	 || ( path_length > ( vshadowmount_fuse_path_prefix_length + 3 ) )
	 || ( libcstring_narrow_string_compare(
	       path,
	       vshadowmount_fuse_path_prefix,
	       vshadowmount_fuse_path_prefix_length ) != 0 ) )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported path.",
		 function );

		result = -ENOENT;

		goto on_error;
	}
	if( ( file_info->flags & 0x03 ) != O_RDONLY )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		result = -EACCES;

		goto on_error;
	}
	return( 0 );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Reads a buffer of data at the specified offset
 * Returns number of bytes read if successful or a negative errno value otherwise
 */
int vshadowmount_fuse_read(
     const char *path,
     char *buffer,
     size_t size,
     off_t offset,
     struct fuse_file_info *file_info )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_fuse_read";
	size_t path_length       = 0;
	ssize_t read_count       = 0;
	int result               = 0;
	int store_index          = 0;
	int string_index         = 0;

	if( path == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		result = -EINVAL;

		goto on_error;
	}
	if( size > (size_t) INT_MAX )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		result = -EINVAL;

		goto on_error;
	}
	if( file_info == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file info.",
		 function );

		result = -EINVAL;

		goto on_error;
	}
	path_length = libcstring_narrow_string_length(
	               path );

	if( ( path_length <= vshadowmount_fuse_path_prefix_length )
	 || ( path_length > ( vshadowmount_fuse_path_prefix_length + 3 ) )
	 || ( libcstring_narrow_string_compare(
	       path,
	       vshadowmount_fuse_path_prefix,
	       vshadowmount_fuse_path_prefix_length ) != 0 ) )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported path.",
		 function );

		result = -ENOENT;

		goto on_error;
	}
	string_index = vshadowmount_fuse_path_prefix_length;

	store_index = path[ string_index++ ] - '0';

	if( string_index < (int) path_length )
	{
		store_index *= 10;
		store_index += path[ string_index++ ] - '0';
	}
	if( string_index < (int) path_length )
	{
		store_index *= 10;
		store_index += path[ string_index++ ] - '0';
	}
	store_index -= 1;

	if( mount_handle_seek_offset(
	     vshadowmount_mount_handle,
	     store_index,
	     (off64_t) offset,
	     SEEK_SET,
	     &error ) == -1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset in mount handle.",
		 function );

		result = -EIO;

		goto on_error;
	}
	read_count = mount_handle_read_buffer(
	              vshadowmount_mount_handle,
	              store_index,
	              (uint8_t *) buffer,
	              size,
	              &error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from mount handle.",
		 function );

		result = -EIO;

		goto on_error;
	}
	return( (int) read_count );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Reads a directory
 * Returns 0 if successful or a negative errno value otherwise
 */
int vshadowmount_fuse_readdir(
     const char *path,
     void *buffer,
     fuse_fill_dir_t filler,
     off_t offset LIBCSYSTEM_ATTRIBUTE_UNUSED,
     struct fuse_file_info *file_info LIBCSYSTEM_ATTRIBUTE_UNUSED )
{
	char vshadowmount_fuse_path[ 9 ];

	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_fuse_readdir";
	size_t path_length       = 0;
	int number_of_stores     = 0;
	int result               = 0;
	int store_index          = 0;
	int string_index         = 0;

	LIBCSYSTEM_UNREFERENCED_PARAMETER( offset )
	LIBCSYSTEM_UNREFERENCED_PARAMETER( file_info )

	if( path == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		result = -EINVAL;

		goto on_error;
	}
	path_length = libcstring_narrow_string_length(
	               path );

	if( ( path_length != 1 )
	 || ( path[ 0 ] != '/' ) )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported path.",
		 function );

		result = -ENOENT;

		goto on_error;
	}
	if( memory_copy(
	     vshadowmount_fuse_path,
	     vshadowmount_fuse_path_prefix,
	     vshadowmount_fuse_path_prefix_length ) == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy fuse path prefix.",
		 function );

		result = -errno;

		goto on_error;
	}
	if( mount_handle_get_number_of_stores(
	     vshadowmount_mount_handle,
	     &number_of_stores,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of stores.",
		 function );

		result = -EIO;

		goto on_error;
	}
	if( ( number_of_stores < 0 )
	 || ( number_of_stores > 255 ) )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported number of stores.",
		 function );

		result = -ENOENT;

		goto on_error;
	}
	if( filler(
	     buffer,
	     ".",
	     NULL,
	     0 ) == 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set directory entry.",
		 function );

		result = -EIO;

		goto on_error;
	}
	if( filler(
	     buffer,
	     "..",
	     NULL,
	     0 ) == 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set directory entry.",
		 function );

		result = -EIO;

		goto on_error;
	}
	for( store_index = 1;
	     store_index <= number_of_stores;
	     store_index++ )
	{
		string_index = vshadowmount_fuse_path_prefix_length;

		if( store_index >= 100 )
		{
			vshadowmount_fuse_path[ string_index++ ] = '0' + (char) ( store_index / 100 );
		}
		if( store_index >= 10 )
		{
			vshadowmount_fuse_path[ string_index++ ] = '0' + (char) ( store_index / 10 );
		}
		vshadowmount_fuse_path[ string_index++ ] = '0' + (char) ( store_index % 10 );
		vshadowmount_fuse_path[ string_index++ ] = 0;

		if( filler(
		     buffer,
		     &( vshadowmount_fuse_path[ 1 ] ),
		     NULL,
		     0 ) == 1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set directory entry.",
			 function );

			result = -EIO;

			goto on_error;
		}
	}
	return( 0 );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Retrieves the file stat info
 * Returns 0 if successful or a negative errno value otherwise
 */
int vshadowmount_fuse_getattr(
     const char *path,
     struct stat *stat_info )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_fuse_getattr";
	size64_t volume_size     = 0;
	size_t path_length       = 0;
	int result               = -ENOENT;

#if defined( HAVE_TIME )
	time_t timestamp         = 0;
#endif

	if( path == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		result = -EINVAL;

		goto on_error;
	}
	if( stat_info == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stat info.",
		 function );

		result = -EINVAL;

		goto on_error;
	}
	if( memory_set(
	     stat_info,
	     0,
	     sizeof( struct stat ) ) == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stat info.",
		 function );

		result = errno;

		goto on_error;
	}
	path_length = libcstring_narrow_string_length(
	               path );

	if( path_length == 1 )
	{
		if( path[ 0 ] == '/' )
		{
			stat_info->st_mode  = S_IFDIR | 0755;
			stat_info->st_nlink = 2;

			result = 0;
		}
	}
	else if( ( path_length > vshadowmount_fuse_path_prefix_length )
	      && ( path_length <= ( vshadowmount_fuse_path_prefix_length + 3 ) ) )
	{
		if( libcstring_narrow_string_compare(
		     path,
		     vshadowmount_fuse_path_prefix,
		     vshadowmount_fuse_path_prefix_length ) == 0 )
		{
			stat_info->st_mode  = S_IFREG | 0444;
			stat_info->st_nlink = 1;

			if( mount_handle_get_size(
			     vshadowmount_mount_handle,
			     &volume_size,
			     &error ) != 1 )
			{
				libcerror_error_set(
				 &error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unsupported to retrieve volume size.",
				 function );

				result = -EIO;

				goto on_error;
			}
#if SIZEOF_OFF_T == 4
			if( volume_size > (size64_t) UINT32_MAX )
			{
				libcerror_error_set(
				 &error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: unsupported to volume size value out of bounds.",
				 function );

				result = -ERANGE;

				goto on_error;
			}
#endif
			stat_info->st_size = (off_t) volume_size;

			result = 0;
		}
	}
	if( result == 0 )
	{
#if defined( HAVE_TIME )
		if( time( &timestamp ) == (time_t) -1 )
		{
			timestamp = 0;
		}
#endif
		stat_info->st_atime = timestamp;
		stat_info->st_mtime = timestamp;
		stat_info->st_ctime = timestamp;

#if defined( HAVE_GETEUID )
		stat_info->st_uid = geteuid();
#else
		stat_info->st_uid = 0;
#endif
#if defined( HAVE_GETEGID )
		stat_info->st_gid = getegid();
#else
		stat_info->st_gid = 0;
#endif
	}
	return( result );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Cleans up when fuse is done
 */
void vshadowmount_fuse_destroy(
      void *private_data LIBCSYSTEM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_fuse_destroy";

	LIBCSYSTEM_UNREFERENCED_PARAMETER( private_data )

	if( vshadowmount_mount_handle != NULL )
	{
		if( mount_handle_free(
		     &vshadowmount_mount_handle,
		     &error ) != 1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free mount handle.",
			 function );

			goto on_error;
		}
	}
	return;

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	return;
}

#elif defined( HAVE_LIBDOKAN )

static wchar_t *vshadowmount_dokan_path_prefix      = L"\\VSS";
static size_t vshadowmount_dokan_path_prefix_length = 4;

/* Opens a file or directory
 * Returns 0 if successful or a negative error code otherwise
 */
int __stdcall vshadowmount_dokan_CreateFile(
               const wchar_t *path,
               DWORD desired_access,
               DWORD share_mode LIBCSYSTEM_ATTRIBUTE_UNUSED,
               DWORD creation_disposition,
               DWORD attribute_flags LIBCSYSTEM_ATTRIBUTE_UNUSED,
               DOKAN_FILE_INFO *file_info )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_dokan_CreateFile";
	size_t path_length       = 0;
	int result               = 0;

	LIBCSYSTEM_UNREFERENCED_PARAMETER( share_mode )
	LIBCSYSTEM_UNREFERENCED_PARAMETER( attribute_flags )

	if( path == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		result = -ERROR_BAD_ARGUMENTS;

		goto on_error;
	}
	if( ( desired_access & GENERIC_WRITE ) != 0 )
	{
		return( -ERROR_WRITE_PROTECT );
	}
	/* Ignore the share_mode
	 */
	if( creation_disposition == CREATE_NEW )
	{
		return( -ERROR_FILE_EXISTS );
	}
	else if( creation_disposition == CREATE_ALWAYS )
	{
		return( -ERROR_ALREADY_EXISTS );
	}
	else if( creation_disposition == OPEN_ALWAYS )
	{
		return( -ERROR_FILE_NOT_FOUND );
	}
	else if( creation_disposition == TRUNCATE_EXISTING )
	{
		return( -ERROR_FILE_NOT_FOUND );
	}
	else if( creation_disposition != OPEN_EXISTING )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid creation disposition.",
		 function );

		result = -ERROR_BAD_ARGUMENTS;

		goto on_error;
	}
	if( file_info == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file info.",
		 function );

		result = -ERROR_BAD_ARGUMENTS;

		goto on_error;
	}
	path_length = libcstring_wide_string_length(
	               path );

	if( path_length == 1 )
	{
		if( path[ 0 ] != (wchar_t) '\\' )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported path: %ls.",
			 function,
			 path );

			result = -ERROR_FILE_NOT_FOUND;

			goto on_error;
		}
	}
	else
	{
		if( ( path_length <= vshadowmount_dokan_path_prefix_length )
		 || ( path_length > ( vshadowmount_fuse_path_prefix_length + 3 ) )
		 || ( libcstring_wide_string_compare(
		       path,
		       vshadowmount_dokan_path_prefix,
		       vshadowmount_dokan_path_prefix_length ) != 0 ) )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported path: %ls.",
			 function,
			 path );

			result = -ERROR_FILE_NOT_FOUND;

			goto on_error;
		}
	}
	return( 0 );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Opens a directory
 * Returns 0 if successful or a negative error code otherwise
 */
int __stdcall vshadowmount_dokan_OpenDirectory(
               const wchar_t *path,
               DOKAN_FILE_INFO *file_info LIBCSYSTEM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_dokan_OpenDirectory";
	size_t path_length       = 0;
	int result               = 0;

	LIBCSYSTEM_UNREFERENCED_PARAMETER( file_info )

	if( path == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		result = -ERROR_BAD_ARGUMENTS;

		goto on_error;
	}
	path_length = libcstring_wide_string_length(
	               path );

	if( ( path_length != 1 )
	 || ( path[ 0 ] != (wchar_t) '\\' ) )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported path: %ls.",
		 function,
		 path );

		result = -ERROR_FILE_NOT_FOUND;

		goto on_error;
	}
	return( 0 );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Closes a file or direcotry
 * Returns 0 if successful or a negative error code otherwise
 */
int __stdcall vshadowmount_dokan_CloseFile(
               const wchar_t *path,
               DOKAN_FILE_INFO *file_info LIBCSYSTEM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_dokan_CloseFile";
	int result               = 0;

	LIBCSYSTEM_UNREFERENCED_PARAMETER( file_info )

	if( path == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		result = -ERROR_BAD_ARGUMENTS;

		goto on_error;
	}
	return( 0 );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Reads a buffer of data at the specified offset
 * Returns 0 if successful or a negative error code otherwise
 */
int __stdcall vshadowmount_dokan_ReadFile(
               const wchar_t *path,
               void *buffer,
               DWORD number_of_bytes_to_read,
               DWORD *number_of_bytes_read,
               LONGLONG offset,
               DOKAN_FILE_INFO *file_info LIBCSYSTEM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_dokan_ReadFile";
	size_t path_length       = 0;
	ssize_t read_count       = 0;
	int result               = 0;
	int store_index          = 0;
	int string_index         = 0;

	LIBCSYSTEM_UNREFERENCED_PARAMETER( file_info )

/* TODO what about end of file behavior ? */

	if( path == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		result = -ERROR_BAD_ARGUMENTS;

		goto on_error;
	}
	if( number_of_bytes_to_read > (DWORD) INT32_MAX )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid number of bytes to read value exceeds maximum.",
		 function );

		result = -ERROR_BAD_ARGUMENTS;

		goto on_error;
	}
	if( number_of_bytes_read == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of bytes read.",
		 function );

		result = -ERROR_BAD_ARGUMENTS;

		goto on_error;
	}
	path_length = libcstring_wide_string_length(
	               path );

	if( ( path_length <= vshadowmount_dokan_path_prefix_length )
         || ( path_length > ( vshadowmount_dokan_path_prefix_length + 3 ) )
	 || ( libcstring_wide_string_compare(
	       path,
	       vshadowmount_dokan_path_prefix,
	       vshadowmount_dokan_path_prefix_length ) != 0 ) )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported path: %ls.",
		 function,
		 path );

		result = -ERROR_FILE_NOT_FOUND;

		goto on_error;
	}
	string_index = (int) vshadowmount_dokan_path_prefix_length;

	store_index = path[ string_index++ ] - (wchar_t) '0';

	if( string_index < (int) path_length )
	{
		store_index *= 10;
		store_index += path[ string_index++ ] - (wchar_t) '0';
	}
	if( string_index < (int) path_length )
	{
		store_index *= 10;
		store_index += path[ string_index++ ] - (wchar_t) '0';
	}
	store_index -= 1;

	if( mount_handle_seek_offset(
	     vshadowmount_mount_handle,
	     store_index,
	     (off64_t) offset,
	     SEEK_SET,
	     &error ) == -1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset in mount handle.",
		 function );

		result = -ERROR_SEEK_ON_DEVICE;

		goto on_error;
	}
	read_count = mount_handle_read_buffer(
		      vshadowmount_mount_handle,
		      store_index,
		      (uint8_t *) buffer,
		      (size_t) number_of_bytes_to_read,
		      &error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from mount handle.",
		 function );

		result = -ERROR_READ_FAULT;

		goto on_error;
	}
	if( read_count > (size_t) INT32_MAX )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid read count value exceeds maximum.",
		 function );

		result = -ERROR_READ_FAULT;

		goto on_error;
	}
	/* Dokan does not require the read function to return ERROR_HANDLE_EOF
	 */
	*number_of_bytes_read = (DWORD) read_count;

	return( 0 );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Reads a directory
 * Returns 0 if successful or a negative error code otherwise
 */
int __stdcall vshadowmount_dokan_FindFiles(
               const wchar_t *path,
               PFillFindData fill_find_data,
               DOKAN_FILE_INFO *file_info )
{
	WIN32_FIND_DATAW find_data;

	wchar_t vshadowmount_dokan_path[ 10 ];

	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_dokan_FindFiles";
	size64_t volume_size     = 0;
	size_t path_length       = 0;
	int number_of_stores     = 0;
	int result               = 0;
	int store_index          = 0;
	int string_index         = 0;

	if( path == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		result = -ERROR_BAD_ARGUMENTS;

		goto on_error;
	}
	path_length = libcstring_wide_string_length(
	               path );

	if( ( path_length != 1 )
	 || ( path[ 0 ] != (wchar_t) '\\' ) )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported path: %ls.",
		 function,
		 path );

		result = -ERROR_FILE_NOT_FOUND;

		goto on_error;
	}
	if( libcstring_wide_string_copy(
	     vshadowmount_dokan_path,
	     vshadowmount_dokan_path_prefix,
	     vshadowmount_dokan_path_prefix_length ) == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy path prefix.",
		 function );

		result = -ERROR_GEN_FAILURE;

		goto on_error;
	}
	if( mount_handle_get_number_of_stores(
	     vshadowmount_mount_handle,
	     &number_of_stores,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of input files.",
		 function );

		result = -ERROR_GEN_FAILURE;

		goto on_error;
	}
	if( ( number_of_stores < 0 )
	 || ( number_of_stores > 255 ) )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported number of input files.",
		 function );

		result = -ERROR_GEN_FAILURE;

		goto on_error;
	}
	if( memory_set(
	     &find_data,
	     0,
	     sizeof( WIN32_FIND_DATAW ) ) == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear find data.",
		 function );

		result = -ERROR_GEN_FAILURE;

		goto on_error;
	}
	if( libcstring_wide_string_copy(
	     find_data.cFileName,
	     L".",
	     1 ) == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy filename.",
		 function );

		result = -ERROR_GEN_FAILURE;

		goto on_error;
	}
	if( libcstring_wide_string_copy(
	     find_data.cAlternateFileName,
	     L".",
	     1 ) == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy alternate filename.",
		 function );

		result = -ERROR_GEN_FAILURE;

		goto on_error;
	}
	find_data.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
/* TODO set timestamps
	find_data.ftCreationTime   = { 0, 0 };
	find_data.ftLastAccessTime = { 0, 0 };
	find_data.ftLastWriteTime  = { 0, 0 };
*/

	if( fill_find_data(
	     &find_data,
	     file_info ) != 0 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set directory entry.",
		 function );

		result = -ERROR_GEN_FAILURE;

		goto on_error;
	}
	if( memory_set(
	     &find_data,
	     0,
	     sizeof( WIN32_FIND_DATAW ) ) == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear find data.",
		 function );

		result = -ERROR_GEN_FAILURE;

		goto on_error;
	}
	if( libcstring_wide_string_copy(
	     find_data.cFileName,
	     L"..",
	     2 ) == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy filename.",
		 function );

		result = -ERROR_GEN_FAILURE;

		goto on_error;
	}
	if( libcstring_wide_string_copy(
	     find_data.cAlternateFileName,
	     L"..",
	     2 ) == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy alternate filename.",
		 function );

		result = -ERROR_GEN_FAILURE;

		goto on_error;
	}
	find_data.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
/* TODO set timestamps
	find_data.ftCreationTime   = { 0, 0 };
	find_data.ftLastAccessTime = { 0, 0 };
	find_data.ftLastWriteTime  = { 0, 0 };
*/

	if( fill_find_data(
	     &find_data,
	     file_info ) != 0 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set directory entry.",
		 function );

		result = -ERROR_GEN_FAILURE;

		goto on_error;
	}
	for( store_index = 1;
	     store_index <= number_of_stores;
	     store_index++ )
	{
		string_index = vshadowmount_dokan_path_prefix_length;

		if( store_index >= 100 )
		{
			vshadowmount_dokan_path[ string_index++ ] = (wchar_t) ( '0' + ( store_index / 100 ) );
		}
		if( store_index >= 10 )
		{
			vshadowmount_dokan_path[ string_index++ ] = (wchar_t) ( '0' + ( store_index / 10 ) );
		}
		vshadowmount_dokan_path[ string_index++ ] = (wchar_t) ( '0' + ( store_index % 10 ) );
		vshadowmount_dokan_path[ string_index++ ] = 0;

		if( mount_handle_get_size(
		     vshadowmount_mount_handle,
		     &volume_size,
		     &error ) != 1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve volume size.",
			 function );

			result = -ERROR_GEN_FAILURE;

			goto on_error;
		}
		if( memory_set(
		     &find_data,
		     0,
		     sizeof( WIN32_FIND_DATAW ) ) == NULL )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear find data.",
			 function );

			result = -ERROR_GEN_FAILURE;

			goto on_error;
		}
		if( libcstring_wide_string_copy(
		     find_data.cFileName,
		     &( vshadowmount_dokan_path[ 1 ] ),
		     string_index - 2 ) == NULL )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy filename.",
			 function );

			result = -ERROR_GEN_FAILURE;

			goto on_error;
		}
		if( libcstring_wide_string_copy(
		     find_data.cAlternateFileName,
		     &( vshadowmount_dokan_path[ 1 ] ),
		     string_index - 2 ) == NULL )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy alternate filename.",
			 function );

			result = -ERROR_GEN_FAILURE;

			goto on_error;
		}
		find_data.dwFileAttributes = FILE_ATTRIBUTE_READONLY;
/* TODO set timestamps
		find_data.ftCreationTime   = { 0, 0 };
		find_data.ftLastAccessTime = { 0, 0 };
		find_data.ftLastWriteTime  = { 0, 0 };
*/
		find_data.nFileSizeHigh    = (DWORD) ( volume_size >> 32 );
		find_data.nFileSizeLow     = (DWORD) ( volume_size & 0xffffffffUL );

		if( fill_find_data(
		     &find_data,
		     file_info ) != 0 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set directory entry.",
			 function );

			result = -ERROR_GEN_FAILURE;

			goto on_error;
		}
	}
	return( 0 );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	return( result );
}

int __stdcall vshadowmount_dokan_GetFileInformation(
               const wchar_t *path,
               BY_HANDLE_FILE_INFORMATION *file_information,
               DOKAN_FILE_INFO *file_info )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_dokan_GetFileInformation";
	size64_t volume_size     = 0;
	size_t path_length       = 0;
	int result               = 0;
	int store_index          = 0;
	int string_index         = 0;

	if( path == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		result = -ERROR_BAD_ARGUMENTS;

		goto on_error;
	}
	if( file_info == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file info.",
		 function );

		result = -ERROR_BAD_ARGUMENTS;

		goto on_error;
	}
	path_length = libcstring_wide_string_length(
	               path );

	if( path_length == 1 )
	{
		if( path[ 0 ] != (wchar_t) '\\' )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported path: %ls.",
			 function,
			 path );

			result = -ERROR_FILE_NOT_FOUND;

			goto on_error;
		}
		file_information->dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
/* TODO set timestamps
		file_information->ftCreationTime   = { 0, 0 };
		file_information->ftLastAccessTime = { 0, 0 };
		file_information->ftLastWriteTime  = { 0, 0 };
*/
	}
	else
	{
		if( ( path_length <= vshadowmount_dokan_path_prefix_length )
		 || ( path_length > ( vshadowmount_dokan_path_prefix_length + 3 ) )
		 || ( libcstring_wide_string_compare(
		       path,
		       vshadowmount_dokan_path_prefix,
		       vshadowmount_dokan_path_prefix_length ) != 0 ) )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported path: %ls.",
			 function,
			 path );

			result = -ERROR_FILE_NOT_FOUND;

			goto on_error;
		}
		string_index = (int) vshadowmount_dokan_path_prefix_length;

		store_index = path[ string_index++ ] - (wchar_t) '0';

		if( string_index < (int) path_length )
		{
			store_index *= 10;
			store_index += path[ string_index++ ] - (wchar_t) '0';
		}
		if( string_index < (int) path_length )
		{
			store_index *= 10;
			store_index += path[ string_index++ ] - (wchar_t) '0';
		}
		store_index -= 1;

		if( mount_handle_get_size(
		     vshadowmount_mount_handle,
		     &volume_size,
		     &error ) != 1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve volume size.",
			 function );

			result = -ERROR_GEN_FAILURE;

			goto on_error;
		}
		file_information->dwFileAttributes = FILE_ATTRIBUTE_READONLY;
/* TODO set timestamps
		file_information->ftCreationTime   = { 0, 0 };
		file_information->ftLastAccessTime = { 0, 0 };
		file_information->ftLastWriteTime  = { 0, 0 };
*/
		file_information->nFileSizeHigh    = (DWORD) ( volume_size >> 32 );
		file_information->nFileSizeLow     = (DWORD) ( volume_size & 0xffffffffUL );
	}
	return( 0 );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Retrieves the volume information
 * Returns 0 if successful or a negative error code otherwise
 */
int __stdcall vshadowmount_dokan_GetVolumeInformation(
               wchar_t *volume_name,
               DWORD volume_name_size,
               DWORD *volume_serial_number,
               DWORD *maximum_filename_length,
               DWORD *file_system_flags,
               wchar_t *file_system_name,
               DWORD file_system_name_size,
               DOKAN_FILE_INFO *file_info LIBCSYSTEM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vshadowmount_dokan_GetVolumeInformation";
	int result               = 0;

	LIBCSYSTEM_UNREFERENCED_PARAMETER( file_info )

	if( ( volume_name != NULL )
	 && ( volume_name_size > (DWORD) ( sizeof( wchar_t ) * 8 ) ) )
	{
		/* Using wcsncpy seems to cause strange behavior here
		 */
		if( memory_copy(
		     volume_name,
		     L"VSHADOW",
		     sizeof( wchar_t ) * 8 ) == NULL )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy volume name.",
			 function );

			result = -ERROR_GEN_FAILURE;

			goto on_error;
		}
	}
	if( volume_serial_number != NULL )
	{
		/* If this value contains 0 it can crash the system is this an issue in Dokan?
		 */
		*volume_serial_number = 0x19831116;
	}
	if( maximum_filename_length != NULL )
	{
		*maximum_filename_length = 256;
	}
	if( file_system_flags != NULL )
	{
		*file_system_flags = FILE_CASE_SENSITIVE_SEARCH
		                   | FILE_CASE_PRESERVED_NAMES
		                   | FILE_UNICODE_ON_DISK
		                   | FILE_READ_ONLY_VOLUME;
	}
	if( ( file_system_name != NULL )
	 && ( file_system_name_size > (DWORD) ( sizeof( wchar_t ) * 6 ) ) )
	{
		/* Using wcsncpy seems to cause strange behavior here
		 */
		if( memory_copy(
		     file_system_name,
		     L"Dokan",
		     sizeof( wchar_t ) * 6 ) == NULL )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy file system name.",
			 function );

			result = -ERROR_GEN_FAILURE;

			goto on_error;
		}
	}
	return( 0 );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Unmount the image
 * Returns 0 if successful or a negative error code otherwise
 */
int __stdcall vshadowmount_dokan_Unmount(
               DOKAN_FILE_INFO *file_info LIBCSYSTEM_ATTRIBUTE_UNUSED )
{
	static char *function = "vshadowmount_dokan_Unmount";

	LIBCSYSTEM_UNREFERENCED_PARAMETER( file_info )

	return( 0 );
}

#endif


/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libvshadow_error_t *error                              = NULL;
	libcstring_system_character_t *mount_point             = NULL;
	libcstring_system_character_t *option_extended_options = NULL;
	libcstring_system_character_t *option_volume_offset    = NULL;
	libcstring_system_character_t *source                  = NULL;
	char *program                                          = "vshadowmount";
	libcstring_system_integer_t option                     = 0;
	int result                                             = 0;
	int verbose                                            = 0;

#if defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE )
	struct fuse_operations vshadowmount_fuse_operations;

	struct fuse_args vshadowmount_fuse_arguments           = FUSE_ARGS_INIT(0, NULL);
	struct fuse_chan *vshadowmount_fuse_channel            = NULL;
	struct fuse *vshadowmount_fuse_handle                  = NULL;

#elif defined( HAVE_LIBDOKAN )
	DOKAN_OPERATIONS vshadowmount_dokan_operations;
	DOKAN_OPTIONS vshadowmount_dokan_options;
#endif

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
             "vshadowtools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
        if( libcsystem_initialize(
             _IONBF,
             &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize system values.\n" );

		goto on_error;
	}
	vshadowoutput_version_fprint(
	 stdout,
	 program );

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _LIBCSTRING_SYSTEM_STRING( "ho:vVX:" ) ) ) != (libcstring_system_integer_t) -1 )
	{
		switch( option )
		{
			case (libcstring_system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_LIBCSTRING_SYSTEM "\n",
				 argv[ optind - 1 ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (libcstring_system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (libcstring_system_integer_t) 'o':
				option_volume_offset = optarg;

				break;

			case (libcstring_system_integer_t) 'v':
				verbose = 1;

				break;

			case (libcstring_system_integer_t) 'V':
				vshadowoutput_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (libcstring_system_integer_t) 'X':
				option_extended_options = optarg;

				break;
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file or device.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind++ ];

	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing mount point.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	mount_point = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libvshadow_notify_set_stream(
	 stderr,
	 NULL );
	libvshadow_notify_set_verbose(
	 verbose );

	if( mount_handle_initialize(
	     &vshadowmount_mount_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize mount handle.\n" );

		goto on_error;
	}
	if( option_volume_offset != NULL )
	{
		if( mount_handle_set_volume_offset(
		     vshadowmount_mount_handle,
		     option_volume_offset,
		     &error ) != 1 )
		{
			libcnotify_print_error_backtrace(
			 error );
			libcerror_error_free(
			 &error );

			fprintf(
			 stderr,
			 "Unsupported volume offset defaulting to: %" PRIi64 ".\n",
			 vshadowmount_mount_handle->volume_offset );
		}
	}
	result = mount_handle_open_input(
	          vshadowmount_mount_handle,
	          source,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to open: %" PRIs_LIBCSTRING_SYSTEM ".\n",
		 source );

		goto on_error;
	}
	else if( result == 0 )
	{
		fprintf(
		 stderr,
		 "No Volume Shadow Snapshots found.\n" );

		goto on_error;
	}
#if defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE )
	if( memory_set(
	     &vshadowmount_fuse_operations,
	     0,
	     sizeof( struct fuse_operations ) ) == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to clear fuse operations.\n" );

		goto on_error;
	}
	if( option_extended_options != NULL )
	{
		/* This argument is required but ignored
		 */
		if( fuse_opt_add_arg(
		     &vshadowmount_fuse_arguments,
		     "" ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable add fuse arguments.\n" );

			goto on_error;
		}
		if( fuse_opt_add_arg(
		     &vshadowmount_fuse_arguments,
		     "-o" ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable add fuse arguments.\n" );

			goto on_error;
		}
		if( fuse_opt_add_arg(
		     &vshadowmount_fuse_arguments,
		     option_extended_options ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable add fuse arguments.\n" );

			goto on_error;
		}
	}
	vshadowmount_fuse_operations.open    = &vshadowmount_fuse_open;
	vshadowmount_fuse_operations.read    = &vshadowmount_fuse_read;
	vshadowmount_fuse_operations.readdir = &vshadowmount_fuse_readdir;
	vshadowmount_fuse_operations.getattr = &vshadowmount_fuse_getattr;
	vshadowmount_fuse_operations.destroy = &vshadowmount_fuse_destroy;

	vshadowmount_fuse_channel = fuse_mount(
	                             mount_point,
	                             &vshadowmount_fuse_arguments );

	if( vshadowmount_fuse_channel == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to create fuse channel.\n" );

		goto on_error;
	}
	vshadowmount_fuse_handle = fuse_new(
	                            vshadowmount_fuse_channel,
	                            &vshadowmount_fuse_arguments,
	                            &vshadowmount_fuse_operations,
	                            sizeof( struct fuse_operations ),
	                            vshadowmount_mount_handle );
	
	if( vshadowmount_fuse_handle == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to create fuse handle.\n" );

		goto on_error;
	}
	if( verbose == 0 )
	{
		if( fuse_daemonize(
		     0 ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable to daemonize fuse.\n" );

			goto on_error;
		}
	}
	result = fuse_loop(
	          vshadowmount_fuse_handle );

	if( result != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to run fuse loop.\n" );

		goto on_error;
	}
	fuse_destroy(
	 vshadowmount_fuse_handle );

	fuse_opt_free_args(
	 &vshadowmount_fuse_arguments );

	return( EXIT_SUCCESS );
#elif defined( HAVE_LIBDOKAN )
	if( memory_set(
	     &vshadowmount_dokan_operations,
	     0,
	     sizeof( DOKAN_OPERATIONS ) ) == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to clear dokan operations.\n" );

		goto on_error;
	}
	if( memory_set(
	     &vshadowmount_dokan_options,
	     0,
	     sizeof( DOKAN_OPTIONS ) ) == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to clear dokan options.\n" );

		goto on_error;
	}
	vshadowmount_dokan_options.Version     = 600;
	vshadowmount_dokan_options.ThreadCount = 0;
	vshadowmount_dokan_options.MountPoint  = mount_point;

	if( verbose != 0 )
	{
		vshadowmount_dokan_options.Options |= DOKAN_OPTION_STDERR;
#if defined( HAVE_DEBUG_OUTPUT )
		vshadowmount_dokan_options.Options |= DOKAN_OPTION_DEBUG;
#endif
	}
/* This will only affect the drive properties
	vshadowmount_dokan_options.Options |= DOKAN_OPTION_REMOVABLE;
*/
	vshadowmount_dokan_options.Options |= DOKAN_OPTION_KEEP_ALIVE;

	vshadowmount_dokan_operations.CreateFile           = &vshadowmount_dokan_CreateFile;
	vshadowmount_dokan_operations.OpenDirectory        = &vshadowmount_dokan_OpenDirectory;
	vshadowmount_dokan_operations.CreateDirectory      = NULL;
	vshadowmount_dokan_operations.Cleanup              = NULL;
	vshadowmount_dokan_operations.CloseFile            = &vshadowmount_dokan_CloseFile;
	vshadowmount_dokan_operations.ReadFile             = &vshadowmount_dokan_ReadFile;
	vshadowmount_dokan_operations.WriteFile            = NULL;
	vshadowmount_dokan_operations.FlushFileBuffers     = NULL;
	vshadowmount_dokan_operations.GetFileInformation   = &vshadowmount_dokan_GetFileInformation;
	vshadowmount_dokan_operations.FindFiles            = &vshadowmount_dokan_FindFiles;
	vshadowmount_dokan_operations.FindFilesWithPattern = NULL;
	vshadowmount_dokan_operations.SetFileAttributes    = NULL;
	vshadowmount_dokan_operations.SetFileTime          = NULL;
	vshadowmount_dokan_operations.DeleteFile           = NULL;
	vshadowmount_dokan_operations.DeleteDirectory      = NULL;
	vshadowmount_dokan_operations.MoveFile             = NULL;
	vshadowmount_dokan_operations.SetEndOfFile         = NULL;
	vshadowmount_dokan_operations.SetAllocationSize    = NULL;
	vshadowmount_dokan_operations.LockFile             = NULL;
	vshadowmount_dokan_operations.UnlockFile           = NULL;
	vshadowmount_dokan_operations.GetFileSecurity      = NULL;
	vshadowmount_dokan_operations.SetFileSecurity      = NULL;
	vshadowmount_dokan_operations.GetDiskFreeSpace     = NULL;
	vshadowmount_dokan_operations.GetVolumeInformation = &vshadowmount_dokan_GetVolumeInformation;
	vshadowmount_dokan_operations.Unmount              = &vshadowmount_dokan_Unmount;

	result = DokanMain(
	          &vshadowmount_dokan_options,
	          &vshadowmount_dokan_operations );

	switch( result )
	{
		case DOKAN_SUCCESS:
			break;

		case DOKAN_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: generic error\n" );
			break;

		case DOKAN_DRIVE_LETTER_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: bad drive letter\n" );
			break;

		case DOKAN_DRIVER_INSTALL_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: unable to load driver\n" );
			break;

		case DOKAN_START_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: driver error\n" );
			break;

		case DOKAN_MOUNT_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: unable to assign drive letter\n" );
			break;

		case DOKAN_MOUNT_POINT_ERROR:
			fprintf(
			 stderr,
			 "Unable to run dokan main: mount point error\n" );
			break;

		default:
			fprintf(
			 stderr,
			 "Unable to run dokan main: unknown error: %d\n",
			 result );
			break;
	}
#else
	fprintf(
	 stderr,
	 "No sub system to mount VSS volume.\n" );

	return( EXIT_FAILURE );
#endif

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LIBFUSE ) || defined( HAVE_LIBOSXFUSE )
	if( vshadowmount_fuse_handle != NULL )
	{
		fuse_destroy(
		 vshadowmount_fuse_handle );
	}
	fuse_opt_free_args(
	 &vshadowmount_fuse_arguments );
#endif
	if( vshadowmount_mount_handle != NULL )
	{
		mount_handle_free(
		 &vshadowmount_mount_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

