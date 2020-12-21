/*
 * Store descriptor functions
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

#if !defined( _LIBVSHADOW_STORE_DESCRIPTOR_H )
#define _LIBVSHADOW_STORE_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libvshadow_block_descriptor.h"
#include "libvshadow_block_tree.h"
#include "libvshadow_libbfio.h"
#include "libvshadow_libcdata.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_libcthreads.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvshadow_store_descriptor libvshadow_store_descriptor_t;

struct libvshadow_store_descriptor
{
	/* The volume size
	 */
	size64_t volume_size;

	/* The (store) identifier
	 * Contains a GUID
	 */
	uint8_t identifier[ 16 ];

	/* The creation date and time
	 */
	uint64_t creation_time;

	/* The store header offset
	 */
	off64_t store_header_offset;

	/* The store block list offset
	 */
	off64_t store_block_list_offset;

	/* The store block range list offset
	 */
	off64_t store_block_range_list_offset;

	/* The store bitmap offset
	 */
	off64_t store_bitmap_offset;

	/* The store previous bitmap offset
	 */
	off64_t store_previous_bitmap_offset;

	/* The (shadow) copy identifier
	 * Contains a GUID
	 */
	uint8_t copy_identifier[ 16 ];

	/* The (shadow) copy set identifier
	 * Contains a GUID
	 */
	uint8_t copy_set_identifier[ 16 ];

	/* The attribute flags
	 */
	uint32_t attribute_flags;

	/* The operating machine string
	 */
	uint8_t *operating_machine_string;

	/* The operating machine string size
	 */
	uint16_t operating_machine_string_size;

	/* The service machine string
	 */
	uint8_t *service_machine_string;

	/* The service machine string size
	 */
	uint16_t service_machine_string_size;

	/* The block descriptors list
	 */
	libcdata_list_t *block_descriptors_list;

	/* The forward block B-tree
	 */
	libvshadow_block_tree_t *forward_block_tree;

	/* The reverse block B-tree
	 */
	libvshadow_block_tree_t *reverse_block_tree;

	/* The block offset list
	 */
	libcdata_range_list_t *block_offset_list;

	/* The previous block offset list
	 */
	libcdata_range_list_t *previous_block_offset_list;

	/* The previous store descriptor in the read chain
	 */
	libvshadow_store_descriptor_t *previous_store_descriptor;

	/* The next store descriptor in the read chain
	 */
	libvshadow_store_descriptor_t *next_store_descriptor;

	/* The current block descriptor
	 */
	libvshadow_block_descriptor_t *current_block_descriptor;

	/* The current reverse block descriptor
	 */
	libvshadow_block_descriptor_t *current_reverse_block_descriptor;

	/* The index
	 */
	int index;

	/* Value to indicate the store has in-volume store data
	 */
	uint8_t has_in_volume_store_data;

	/* Value to indicate the block descriptors have been read
	 */
	uint8_t block_descriptors_read;

#if defined( HAVE_LIBVSHADOW_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

int libvshadow_store_descriptor_initialize(
     libvshadow_store_descriptor_t **store_descriptor,
     libcerror_error_t **error );

int libvshadow_store_descriptor_free(
     libvshadow_store_descriptor_t **store_descriptor,
     libcerror_error_t **error );

int libvshadow_store_descriptor_has_in_volume_data(
     libvshadow_store_descriptor_t *store_descriptor,
     libcerror_error_t **error );

int libvshadow_store_descriptor_compare_by_creation_time(
     libvshadow_store_descriptor_t *first_store_descriptor,
     libvshadow_store_descriptor_t *second_store_descriptor,
     libcerror_error_t **error );

int libvshadow_store_descriptor_compare_by_identifier(
     libvshadow_store_descriptor_t *first_store_descriptor,
     libvshadow_store_descriptor_t *second_store_descriptor,
     libcerror_error_t **error );

int libvshadow_store_descriptor_read_catalog_entry(
     libvshadow_store_descriptor_t *store_descriptor,
     const uint8_t *catalog_block_data,
     size_t catalog_block_data_size,
     uint64_t *entry_type,
     libcerror_error_t **error );

int libvshadow_store_descriptor_read_store_header(
     libvshadow_store_descriptor_t *store_descriptor,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libvshadow_store_descriptor_read_store_bitmap(
     libvshadow_store_descriptor_t *store_descriptor,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcdata_range_list_t *offset_list,
     off64_t *bitmap_offset,
     off64_t *next_offset,
     libcerror_error_t **error );

int libvshadow_store_descriptor_read_store_block_list(
     libvshadow_store_descriptor_t *store_descriptor,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     off64_t *next_offset,
     libcerror_error_t **error );

int libvshadow_store_descriptor_read_store_block_range_list(
     libvshadow_store_descriptor_t *store_descriptor,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     off64_t *next_offset,
     libcerror_error_t **error );

int libvshadow_store_descriptor_read_block_descriptors(
     libvshadow_store_descriptor_t *store_descriptor,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

ssize_t libvshadow_store_descriptor_read_buffer(
         libvshadow_store_descriptor_t *store_descriptor,
         libbfio_handle_t *file_io_handle,
         uint8_t *buffer,
         size_t buffer_size,
         off64_t offset,
         int active_store_descriptor_index,
         libcerror_error_t **error );

int libvshadow_store_descriptor_get_volume_size(
     libvshadow_store_descriptor_t *store_descriptor,
     size64_t *volume_size,
     libcerror_error_t **error );

int libvshadow_store_descriptor_get_identifier(
     libvshadow_store_descriptor_t *store_descriptor,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

int libvshadow_store_descriptor_get_creation_time(
     libvshadow_store_descriptor_t *store_descriptor,
     uint64_t *filetime,
     libcerror_error_t **error );

int libvshadow_store_descriptor_get_copy_identifier(
     libvshadow_store_descriptor_t *store_descriptor,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

int libvshadow_store_descriptor_get_copy_set_identifier(
     libvshadow_store_descriptor_t *store_descriptor,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

int libvshadow_store_descriptor_get_attribute_flags(
     libvshadow_store_descriptor_t *store_descriptor,
     uint32_t *attribute_flags,
     libcerror_error_t **error );

int libvshadow_store_descriptor_get_number_of_blocks(
     libvshadow_store_descriptor_t *store_descriptor,
     libbfio_handle_t *file_io_handle,
     int *number_of_blocks,
     libcerror_error_t **error );

int libvshadow_store_descriptor_get_block_descriptor_by_index(
     libvshadow_store_descriptor_t *store_descriptor,
     libbfio_handle_t *file_io_handle,
     int block_index,
     libvshadow_block_descriptor_t **block_descriptor,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSHADOW_STORE_DESCRIPTOR_H ) */

