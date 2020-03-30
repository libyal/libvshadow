/*
 * Tool to troubleshoot issues with libvshadow
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
#include <memory.h>
#include <system_string.h>
#include <types.h>

#include <stdio.h>

#if defined( HAVE_IO_H ) || defined( WINAPI )
#include <io.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "debug_handle.h"
#include "vshadowtools_getopt.h"
#include "vshadowtools_libcerror.h"
#include "vshadowtools_libclocale.h"
#include "vshadowtools_libcnotify.h"
#include "vshadowtools_libvshadow.h"
#include "vshadowtools_output.h"
#include "vshadowtools_signal.h"
#include "vshadowtools_unused.h"

debug_handle_t *vshadowdebug_debug_handle = NULL;
int vshadowdebug_abort                    = 0;

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use vshadowdebug to troubleshoot issues with libvshadow\n\n" );

	fprintf( stream, "Usage: vshadowdebug [ -o offset ] [ -hvV ] source\n\n" );

	fprintf( stream, "\tsource: the source file or device\n\n" );

	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-o:     specify the volume offset in bytes\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* Signal handler for vshadowdebug
 */
void vshadowdebug_signal_handler(
      vshadowtools_signal_t signal VSHADOWTOOLS_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "vshadowdebug_signal_handler";

	VSHADOWTOOLS_UNREFERENCED_PARAMETER( signal )

	vshadowdebug_abort = 1;

	if( vshadowdebug_debug_handle != NULL )
	{
		if( debug_handle_signal_abort(
		     vshadowdebug_debug_handle,
		     &error ) != 1 )
		{
			libcnotify_printf(
			 "%s: unable to signal debug handle to abort.\n",
			 function );

			libcnotify_print_error_backtrace(
			 error );
			libcerror_error_free(
			 &error );
		}
	}
	/* Force stdin to close otherwise any function reading it will remain blocked
	 */
#if defined( WINAPI ) && !defined( __CYGWIN__ )
	if( _close(
	     0 ) != 0 )
#else
	if( close(
	     0 ) != 0 )
#endif
	{
		libcnotify_printf(
		 "%s: unable to close stdin.\n",
		 function );
	}
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error                 = NULL;
	system_character_t *option_volume_offset = NULL;
	system_character_t *source               = NULL;
	char *program                            = "vshadowdebug";
	system_integer_t option                  = 0;
	int result                               = 0;
	int verbose                              = 0;

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
        if( vshadowtools_output_initialize(
             _IONBF,
             &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
	vshadowtools_output_version_fprint(
	 stdout,
	 program );

	while( ( option = vshadowtools_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "ho:vV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind - 1 ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'o':
				option_volume_offset = optarg;

				break;

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				vshadowtools_output_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
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
	source = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libvshadow_notify_set_stream(
	 stderr,
	 NULL );
	libvshadow_notify_set_verbose(
	 verbose );

	if( debug_handle_initialize(
	     &vshadowdebug_debug_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize debug handle.\n" );

		goto on_error;
	}
	if( option_volume_offset != NULL )
	{
		if( debug_handle_set_volume_offset(
		     vshadowdebug_debug_handle,
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
			 vshadowdebug_debug_handle->volume_offset );
		}
	}
	result = debug_handle_open_input(
	          vshadowdebug_debug_handle,
	          source,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to open: %" PRIs_SYSTEM ".\n",
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
	if( debug_handle_test_read(
	     vshadowdebug_debug_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}
	if( debug_handle_close(
	     vshadowdebug_debug_handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close debug handle.\n" );

		goto on_error;
	}
	if( debug_handle_free(
	     &vshadowdebug_debug_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free debug handle.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( vshadowdebug_debug_handle != NULL )
	{
		debug_handle_free(
		 &vshadowdebug_debug_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

