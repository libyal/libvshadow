/*
 * Debug functions
 *
 * Copyright (C) 2011-2014, Joachim Metz <joachim.metz@gmail.com>
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

#include "libvshadow_debug.h"
#include "libvshadow_definitions.h"
#include "libvshadow_libbfio.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_libcnotify.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the attribute flags
 */
void libvshadow_debug_print_attribute_flags(
      uint32_t attribute_flags )
{
	if( ( attribute_flags & 0x00000001 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_PERSISTENT)\n" );
	}
	if( ( attribute_flags & 0x00000002 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_NO_AUTORECOVERY)\n" );
	}
	if( ( attribute_flags & 0x00000004 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_CLIENT_ACCESSIBLE)\n" );
	}
	if( ( attribute_flags & 0x00000008 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_NO_AUTO_RELEASE)\n" );
	}
	if( ( attribute_flags & 0x00000010 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_NO_WRITERS)\n" );
	}
	if( ( attribute_flags & 0x00000020 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_TRANSPORTABLE)\n" );
	}
	if( ( attribute_flags & 0x00000040 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_NOT_SURFACED)\n" );
	}
	if( ( attribute_flags & 0x00000080 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_NOT_TRANSACTED)\n" );
	}

	if( ( attribute_flags & 0x00010000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_HARDWARE_ASSISTED)\n" );
	}
	if( ( attribute_flags & 0x00020000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_DIFFERENTIAL)\n" );
	}
	if( ( attribute_flags & 0x00040000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_PLEX)\n" );
	}
	if( ( attribute_flags & 0x00080000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_IMPORTED)\n" );
	}
	if( ( attribute_flags & 0x00100000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_EXPOSED_LOCALLY)\n" );
	}
	if( ( attribute_flags & 0x00200000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_EXPOSED_REMOTELY)\n" );
	}
	if( ( attribute_flags & 0x00400000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_AUTORECOVER)\n" );
	}
	if( ( attribute_flags & 0x00800000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_ROLLBACK_RECOVERY)\n" );
	}
	if( ( attribute_flags & 0x01000000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_DELAYED_POSTSNAPSHOT)\n" );
	}
	if( ( attribute_flags & 0x01000000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(VSS_VOLSNAP_ATTR_TXF_RECOVERY)\n" );
	}
}

/* Prints the read offsets
 * Returns 1 if successful or -1 on error
 */
int libvshadow_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_debug_print_read_offsets";
	off64_t offset        = 0;
	size64_t size         = 0;
	int number_of_offsets = 0;
	int offset_iterator   = 0;

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
	if( libbfio_handle_get_number_of_offsets_read(
	     file_io_handle,
	     &number_of_offsets,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of offsets read.",
		 function );

		return( -1 );
	}
	libcnotify_printf(
	 "Offsets read:\n" );

	for( offset_iterator = 0;
	     offset_iterator < number_of_offsets;
	     offset_iterator++ )
	{
		if( libbfio_handle_get_offset_read(
		     file_io_handle,
		     offset_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offset: %d.",
			 function,
			 ( offset_iterator + 1 ) );

			return( -1 );
		}
		libcnotify_printf(
		 "%08" PRIi64 " ( 0x%08" PRIx64 " ) - %08" PRIi64 " ( 0x%08" PRIx64 " ) size: %" PRIu64 "\n",
		 offset,
		 offset,
		 offset + (off64_t) size,
		 offset + (off64_t) size,
		 size );
	}
	libcnotify_printf(
	 "\n" );

	return( 1 );
}

#endif

