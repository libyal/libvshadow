/*
 * Mount file system
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

#if !defined( _MOUNT_FILE_SYSTEM_H )
#define _MOUNT_FILE_SYSTEM_H

#include <common.h>
#include <types.h>

#include "vshadowtools_libcdata.h"
#include "vshadowtools_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct mount_file_system mount_file_system_t;

struct mount_file_system
{
	/* The mounted timestamp
	 */
	uint64_t mounted_timestamp;

	/* The path prefix
	 */
	system_character_t *path_prefix;

	/* The path prefix size
	 */
	size_t path_prefix_size;

	/* The volume
	 */
	libvshadow_volume_t *vshadow_volume;

	/* The stores array
	 */
	libcdata_array_t *stores_array;
};

int mount_file_system_initialize(
     mount_file_system_t **file_system,
     libcerror_error_t **error );

int mount_file_system_free(
     mount_file_system_t **file_system,
     libcerror_error_t **error );

int mount_file_system_signal_abort(
     mount_file_system_t *file_system,
     libcerror_error_t **error );

int mount_file_system_set_volume(
     mount_file_system_t *file_system,
     libvshadow_volume_t *vshadow_volume,
     libcerror_error_t **error );

int mount_file_system_get_volume(
     mount_file_system_t *file_system,
     libvshadow_volume_t **vshadow_volume,
     libcerror_error_t **error );

int mount_file_system_set_path_prefix(
     mount_file_system_t *file_system,
     const system_character_t *path_prefix,
     size_t path_prefix_size,
     libcerror_error_t **error );

int mount_file_system_get_mounted_timestamp(
     mount_file_system_t *file_system,
     uint64_t *mounted_timestamp,
     libcerror_error_t **error );

int mount_file_system_get_number_of_stores(
     mount_file_system_t *file_system,
     int *number_of_stores,
     libcerror_error_t **error );

int mount_file_system_get_store_by_index(
     mount_file_system_t *file_system,
     int store_index,
     libvshadow_store_t **vshadow_store,
     libcerror_error_t **error );

int mount_file_system_get_store_by_path(
     mount_file_system_t *file_system,
     const system_character_t *path,
     size_t path_length,
     libvshadow_store_t **vshadow_store,
     libcerror_error_t **error );

int mount_file_system_append_store(
     mount_file_system_t *file_system,
     libvshadow_store_t *vshadow_store,
     libcerror_error_t **error );

int mount_file_system_get_path_from_store_index(
     mount_file_system_t *file_system,
     int store_index,
     system_character_t *path,
     size_t path_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _MOUNT_FILE_SYSTEM_H ) */

