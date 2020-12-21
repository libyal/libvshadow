/*
 * Block tree functions
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

#if !defined( _LIBVSHADOW_BLOCK_TREE_H )
#define _LIBVSHADOW_BLOCK_TREE_H

#include <common.h>
#include <types.h>

#include "libvshadow_block_descriptor.h"
#include "libvshadow_libcdata.h"
#include "libvshadow_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvshadow_block_tree libvshadow_block_tree_t;

struct libvshadow_block_tree
{
	/* The block descriptors B-tree
	 */
	libcdata_btree_t *block_descriptors_tree;
};

int libvshadow_block_tree_initialize(
     libvshadow_block_tree_t **block_tree,
     libcerror_error_t **error );

int libvshadow_block_tree_free(
     libvshadow_block_tree_t **block_tree,
     int (*value_free_function)(
            intptr_t **value,
            libcerror_error_t **error ),
     libcerror_error_t **error );

int libvshadow_block_tree_get_block_descriptor_by_offset(
     libvshadow_block_tree_t *block_tree,
     off64_t offset,
     int (*value_compare_function)(
            intptr_t *first_value,
            intptr_t *second_value,
            libcerror_error_t **error ),
     libvshadow_block_descriptor_t **block_descriptor,
     libcerror_error_t **error );

int libvshadow_block_tree_insert(
     libvshadow_block_tree_t *forward_block_tree,
     libvshadow_block_tree_t *reverse_block_tree,
     libvshadow_block_descriptor_t *block_descriptor,
     int store_index,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSHADOW_BLOCK_TREE_H ) */

