/*
 * The NTFS volume header functions
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

#if !defined( _LIBVSHADOW_NTFS_VOLUME_HEADER_H )
#define _LIBVSHADOW_NTFS_VOLUME_HEADER_H

#include <common.h>
#include <types.h>

#include "libvshadow_libbfio.h"
#include "libvshadow_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvshadow_ntfs_volume_header libvshadow_ntfs_volume_header_t;

struct libvshadow_ntfs_volume_header
{
	/* The number of bytes per sector
	 */
	uint16_t bytes_per_sector;

	/* The volume size
	 */
	size64_t volume_size;
};

int libvshadow_ntfs_volume_header_initialize(
     libvshadow_ntfs_volume_header_t **ntfs_volume_header,
     libcerror_error_t **error );

int libvshadow_ntfs_volume_header_free(
     libvshadow_ntfs_volume_header_t **ntfs_volume_header,
     libcerror_error_t **error );

int libvshadow_ntfs_volume_header_read_data(
     libvshadow_ntfs_volume_header_t *ntfs_volume_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvshadow_ntfs_volume_header_read_file_io_handle(
     libvshadow_ntfs_volume_header_t *ntfs_volume_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSHADOW_NTFS_VOLUME_HEADER_H ) */

