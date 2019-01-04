/*
 * Block tree functions
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

int libvshadow_block_tree_insert(
     libcdata_btree_t *forward_block_tree,
     libcdata_btree_t *reverse_block_tree,
     libvshadow_block_descriptor_t *block_descriptor,
     int store_index,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSHADOW_BLOCK_TREE_H ) */

