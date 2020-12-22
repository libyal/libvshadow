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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libvshadow_block_descriptor.h"
#include "libvshadow_block_tree.h"
#include "libvshadow_block_tree_node.h"
#include "libvshadow_definitions.h"
#include "libvshadow_libcdata.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_libcnotify.h"
#include "libvshadow_unused.h"

/* Creates a block tree
 * Make sure the value block_tree is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_tree_initialize(
     libvshadow_block_tree_t **block_tree,
     size64_t volume_size,
     libcerror_error_t **error )
{
	static char *function = "libvshadow_block_tree_initialize";

	if( block_tree == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block tree.",
		 function );

		return( -1 );
	}
	if( *block_tree != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block tree value already set.",
		 function );

		return( -1 );
	}
	*block_tree = memory_allocate_structure(
	               libvshadow_block_tree_t );

	if( *block_tree == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block tree.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *block_tree,
	     0,
	     sizeof( libvshadow_block_tree_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block tree.",
		 function );

		memory_free(
		 *block_tree );

		*block_tree = NULL;

		return( -1 );
	}
	if( libvshadow_block_tree_node_initialize(
	     &( ( *block_tree )->root_node ),
	     0,
	     volume_size,
	     0x4000,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create root node.",
		 function );

		goto on_error;
	}
	( *block_tree )->leaf_value_size = 0x4000;

	return( 1 );

on_error:
	if( *block_tree != NULL )
	{
		memory_free(
		 *block_tree );

		*block_tree = NULL;
	}
	return( -1 );
}

/* Frees a block tree
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_tree_free(
     libvshadow_block_tree_t **block_tree,
     int (*value_free_function)(
            intptr_t **value,
            libcerror_error_t **error ),
     libcerror_error_t **error )
{
	static char *function = "libvshadow_block_tree_free";
	int result            = 1;

	if( block_tree == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block tree.",
		 function );

		return( -1 );
	}
	if( *block_tree != NULL )
	{
		if( libvshadow_block_tree_node_free(
		     &( ( *block_tree )->root_node ),
		     value_free_function,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free root node.",
			 function );

			result = -1;
		}
		memory_free(
		 *block_tree );

		*block_tree = NULL;
	}
	return( result );
}

/* Retrieves the block descriptor for a specific offset
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvshadow_block_tree_get_block_descriptor_by_offset(
     libvshadow_block_tree_t *block_tree,
     off64_t offset,
     libvshadow_block_descriptor_t **block_descriptor,
     libcerror_error_t **error )
{
	libvshadow_block_descriptor_t *safe_block_descriptor = NULL;
	libvshadow_block_tree_node_t *block_tree_node        = NULL;
	static char *function                                = "libvshadow_block_tree_get_block_descriptor_by_offset";

	if( block_tree == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block tree.",
		 function );

		return( -1 );
	}
	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	block_tree_node = block_tree->root_node;

	while( block_tree_node->is_leaf_node == 0 )
	{
		if( libvshadow_block_tree_node_get_sub_node_at_offset(
		     block_tree_node,
		     offset,
		     &block_tree_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve sub node at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 offset,
			 offset );

			return( -1 );
		}
		if( block_tree_node == NULL )
		{
			return( 0 );
		}
	}
	if( libvshadow_block_tree_node_get_leaf_value_at_offset(
	     block_tree_node,
	     offset,
	     &safe_block_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve leaf value at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		return( -1 );
	}
	if( safe_block_descriptor == NULL )
	{
		return( 0 );
	}
	*block_descriptor = safe_block_descriptor;

	return( 1 );
}

/* Inserts the block descriptor for a specific offset
 * Returns 1 if successful, 0 if already set or -1 on error
 */
int libvshadow_block_tree_insert_block_descriptor_by_offset(
     libvshadow_block_tree_t *block_tree,
     off64_t offset,
     libvshadow_block_descriptor_t *block_descriptor,
     int *leaf_value_index,
     libvshadow_block_tree_node_t **leaf_block_tree_node,
     libvshadow_block_descriptor_t **existing_block_descriptor,
     libcerror_error_t **error )
{
	libvshadow_block_descriptor_t *safe_block_descriptor = NULL;
	libvshadow_block_tree_node_t *block_tree_node        = NULL;
	libvshadow_block_tree_node_t *safe_block_tree_node   = NULL;
	libvshadow_block_tree_node_t *sub_block_tree_node    = NULL;
	static char *function                                = "libvshadow_block_tree_insert_block_descriptor_by_offset";
	off64_t sub_node_index                               = 0;
	off64_t sub_node_offset                              = 0;

	if( block_tree == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block tree.",
		 function );

		return( -1 );
	}
	if( leaf_value_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leaf value index.",
		 function );

		return( -1 );
	}
	if( leaf_block_tree_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leaf block tree node.",
		 function );

		return( -1 );
	}
	if( existing_block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid existing block descriptor.",
		 function );

		return( -1 );
	}
	safe_block_tree_node = block_tree->root_node;

	while( safe_block_tree_node->is_leaf_node == 0 )
	{
		if( libvshadow_block_tree_node_get_sub_node_at_offset(
		     safe_block_tree_node,
		     offset,
		     &block_tree_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve sub node at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 offset,
			 offset );

			goto on_error;
		}
		if( block_tree_node == NULL )
		{
			sub_node_offset = offset - safe_block_tree_node->start_offset;

			sub_node_index  = sub_node_offset / safe_block_tree_node->sub_node_size;
			sub_node_offset = safe_block_tree_node->start_offset + ( sub_node_index * safe_block_tree_node->sub_node_size );

			if( libvshadow_block_tree_node_initialize(
			     &sub_block_tree_node,
			     sub_node_offset,
			     safe_block_tree_node->sub_node_size,
			     block_tree->leaf_value_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create sub node.",
				 function );

				goto on_error;
			}
			if( libvshadow_block_tree_node_set_sub_node_at_offset(
			     safe_block_tree_node,
			     offset,
			     sub_block_tree_node,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to set sub node at offset: %" PRIi64 " (0x%08" PRIx64 ").",
				 function,
				 offset,
				 offset );

				goto on_error;
			}
			block_tree_node     = sub_block_tree_node;
			sub_block_tree_node = NULL;
		}
		safe_block_tree_node = block_tree_node;
	}
	*leaf_block_tree_node = safe_block_tree_node;

	if( libvshadow_block_tree_node_get_leaf_value_at_offset(
	     safe_block_tree_node,
	     offset,
	     &safe_block_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve leaf value at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		goto on_error;
	}
	if( safe_block_descriptor != NULL )
	{
		*existing_block_descriptor = safe_block_descriptor;

		return( 0 );
	}
	if( libvshadow_block_tree_node_set_leaf_value_at_offset(
	     safe_block_tree_node,
	     offset,
	     block_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set leaf value at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		goto on_error;
	}
	*leaf_value_index = (int) ( offset / block_tree->leaf_value_size );

	return( 1 );

on_error:
	if( sub_block_tree_node != NULL )
	{
		libvshadow_block_tree_node_free(
		 &sub_block_tree_node,
		 NULL,
		 NULL );
	}
	return( -1 );
}

/* Removes the block descriptor for a specific offset
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvshadow_block_tree_remove_block_descriptor_by_offset(
     libvshadow_block_tree_t *block_tree,
     off64_t offset,
     libcerror_error_t **error )
{
	libvshadow_block_descriptor_t *safe_block_descriptor = NULL;
	libvshadow_block_tree_node_t *block_tree_node        = NULL;
	static char *function                                = "libvshadow_block_tree_remove_block_descriptor_by_offset";

	if( block_tree == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block tree.",
		 function );

		return( -1 );
	}
	block_tree_node = block_tree->root_node;

	while( block_tree_node->is_leaf_node == 0 )
	{
		if( libvshadow_block_tree_node_get_sub_node_at_offset(
		     block_tree_node,
		     offset,
		     &block_tree_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve sub node at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 offset,
			 offset );

			return( -1 );
		}
		if( block_tree_node == NULL )
		{
			return( 0 );
		}
	}
	if( libvshadow_block_tree_node_get_leaf_value_at_offset(
	     block_tree_node,
	     offset,
	     &safe_block_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve leaf value at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		return( -1 );
	}
	if( safe_block_descriptor == NULL )
	{
		return( 0 );
	}
	if( libvshadow_block_tree_node_set_leaf_value_at_offset(
	     block_tree_node,
	     offset,
	     NULL,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set leaf value at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		return( -1 );
	}
	return( 1 );
}

/* Inserts a block descriptor in the block tree
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_tree_insert(
     libvshadow_block_tree_t *forward_block_tree,
     libvshadow_block_tree_t *reverse_block_tree,
     libvshadow_block_descriptor_t *block_descriptor,
     int store_index LIBVSHADOW_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libvshadow_block_descriptor_t *existing_block_descriptor = NULL;
	libvshadow_block_descriptor_t *new_block_descriptor      = NULL;
	libvshadow_block_descriptor_t *overlay_block_descriptor  = NULL;
	libvshadow_block_descriptor_t *reverse_block_descriptor  = NULL;
	libvshadow_block_tree_node_t *leaf_block_tree_node       = NULL;
	static char *function                                    = "libvshadow_block_tree_insert";
	off64_t new_original_offset                              = 0;
	int result                                               = 0;

	LIBVSHADOW_UNREFERENCED_PARAMETER( store_index )

	if( forward_block_tree == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid forward block tree.",
		 function );

		return( -1 );
	}
	if( reverse_block_tree == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid reverse block tree.",
		 function );

		return( -1 );
	}
	if( block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block descriptor.",
		 function );

		return( -1 );
	}
	if( ( block_descriptor->flags & LIBVSHADOW_BLOCK_FLAG_NOT_USED ) != 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: store: %02d not used flag set - ignoring block descriptor.\n",
			 function,
			 store_index );
			libcnotify_printf(
			 "\n" );
		}
#endif
		return( 1 );
	}
	new_original_offset = block_descriptor->original_offset;

	if( ( block_descriptor->flags & LIBVSHADOW_BLOCK_FLAG_IS_OVERLAY ) == 0 )
	{
		/* The reverse block tree is used to detect forwarder block descriptors that point to each other
		 */
		result = libvshadow_block_tree_get_block_descriptor_by_offset(
			  reverse_block_tree,
			  block_descriptor->original_offset,
			  &reverse_block_descriptor,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve reverse block descriptor for offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 block_descriptor->original_offset,
			 block_descriptor->original_offset );

			goto on_error;
		}
		else if( result != 0 )
		{
			if( reverse_block_descriptor == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing reverse block descriptor.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: store: %02d found reverse block descriptor: %" PRIi64 " (0x%08" PRIx64 ").\n",
				 function,
				 store_index,
				 reverse_block_descriptor->original_offset,
				 reverse_block_descriptor->original_offset );

				libcnotify_printf(
				 "%s: store: %02d swapping original offset.\n",
				 function,
				 store_index );
			}
#endif
			new_original_offset = reverse_block_descriptor->original_offset;

			if( libvshadow_block_tree_remove_block_descriptor_by_offset(
			     reverse_block_tree,
			     reverse_block_descriptor->relative_offset,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_REMOVE_FAILED,
				 "%s: unable to remove reverse block descriptor: %" PRIi64 " (0x%08" PRIx64 ") from reverse block tree node.",
				 function,
				 reverse_block_descriptor->original_offset,
				 reverse_block_descriptor->original_offset );

				goto on_error;
			}
			reverse_block_descriptor->reverse_index = -1;

			if( reverse_block_descriptor->index == -1 )
			{
				if( libvshadow_block_descriptor_free(
				     &reverse_block_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to free reverse block descriptor.",
					 function );

					goto on_error;
				}
			}
		}
	}
	if( ( block_descriptor->flags & LIBVSHADOW_BLOCK_FLAG_IS_FORWARDER ) != 0 )
	{
		if( new_original_offset == block_descriptor->relative_offset )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: store: %02d forwarder points to itself - ignoring block descriptor.\n",
				 function,
				 store_index );
				libcnotify_printf(
				 "\n" );
			}
#endif
			return( 1 );
		}
	}
	if( libvshadow_block_descriptor_clone(
	     &new_block_descriptor,
	     block_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block descriptor.",
		 function );

		goto on_error;
	}
	new_block_descriptor->original_offset = new_original_offset;

	result = libvshadow_block_tree_insert_block_descriptor_by_offset(
		  forward_block_tree,
	          new_block_descriptor->original_offset,
	          new_block_descriptor,
	          &( new_block_descriptor->index ),
	          &leaf_block_tree_node,
	          &existing_block_descriptor,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to insert block descriptor in forward block tree.",
		 function );

		goto on_error;
	}
	else if( result == 0 )
	{
		if( existing_block_descriptor == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing existing block descriptor.",
			 function );

			goto on_error;
		}
		if( ( new_block_descriptor->flags & LIBVSHADOW_BLOCK_FLAG_IS_OVERLAY ) != 0 )
		{
			if( ( existing_block_descriptor->flags & LIBVSHADOW_BLOCK_FLAG_IS_OVERLAY ) != 0 )
			{
				overlay_block_descriptor = existing_block_descriptor;
			}
			else
			{
				overlay_block_descriptor = existing_block_descriptor->overlay;
			}
			if( overlay_block_descriptor != NULL )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					if( new_block_descriptor->original_offset != overlay_block_descriptor->original_offset )
					{
						libcnotify_printf(
						 "%s: store: %02d mismatch in block descriptor store original offset (0x%08" PRIx64 ").\n",
						 function,
						 store_index,
						 overlay_block_descriptor->original_offset );
					}
					if( new_block_descriptor->offset != overlay_block_descriptor->offset )
					{
						libcnotify_printf(
						 "%s: store: %02d mismatch in block descriptor store offset (0x%08" PRIx64 ").\n",
						 function,
						 store_index,
						 overlay_block_descriptor->offset );
					}
					if( new_block_descriptor->relative_offset != 0x00000001UL )
					{
						libcnotify_printf(
						 "%s: store: %02d mismatch in block descriptor relative store offset (0x%08" PRIx64 ").\n",
						 function,
						 store_index,
						 new_block_descriptor->relative_offset );
					}
					libcnotify_printf(
					 "%s: store: %02d expanding overlay.\n",
					 function,
					 store_index );
				}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

				overlay_block_descriptor->bitmap |= new_block_descriptor->bitmap;

				if( libvshadow_block_descriptor_free(
				     &new_block_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to free block descriptor.",
					 function );

					goto on_error;
				}
			}
			else
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					if( new_block_descriptor->relative_offset == 0x00000001UL )
					{
						libcnotify_printf(
						 "%s: store: %02d mismatch in block descriptor relative store offset (0x%08" PRIx64 ").\n",
						 function,
						 store_index,
						 new_block_descriptor->relative_offset );
					}
					libcnotify_printf(
					 "%s: store: %02d creating overlay.\n",
					 function,
					 store_index );
				}
#endif
				existing_block_descriptor->overlay = new_block_descriptor;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "\n" );
			}
#endif
			return( 1 );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: store: %02d replacing existing block descriptor.\n",
			 function,
			 store_index );
		}
#endif
		if( libvshadow_block_tree_node_set_leaf_value_at_offset(
		     leaf_block_tree_node,
		     new_block_descriptor->original_offset,
		     new_block_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set leaf value at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 new_block_descriptor->original_offset,
			 new_block_descriptor->original_offset );

			goto on_error;
		}
		new_block_descriptor->index      = existing_block_descriptor->index;
		existing_block_descriptor->index = -1;

		if( ( existing_block_descriptor->flags & LIBVSHADOW_BLOCK_FLAG_IS_OVERLAY ) != 0 )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: store: %02d adding existing block descriptor as overlay.\n",
				 function,
				 store_index );
			}
#endif
			if( existing_block_descriptor->overlay != NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: invalid existing overlay block descriptor.",
				 function );

				goto on_error;
			}
			new_block_descriptor->overlay = existing_block_descriptor;
		}
		else
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: store: %02d swapping overlay block descriptor.\n",
				 function,
				 store_index );
			}
#endif
			/* Swap the overlay block descriptor of the existing block descriptor with the new block descriptor
			 */
			new_block_descriptor->overlay      = existing_block_descriptor->overlay;
			existing_block_descriptor->overlay = NULL;

			if( existing_block_descriptor->reverse_index == -1 )
			{
				if( libvshadow_block_descriptor_free(
				     &existing_block_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to free existing block descriptor.",
					 function );

					goto on_error;
				}
			}
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	else if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: store: %02d adding block descriptor.\n",
		 function,
		 store_index );
	}
#endif
	if( ( new_block_descriptor->flags & LIBVSHADOW_BLOCK_FLAG_IS_FORWARDER ) != 0 )
	{
		result = libvshadow_block_tree_insert_block_descriptor_by_offset(
			  reverse_block_tree,
			  new_block_descriptor->relative_offset,
			  new_block_descriptor,
			  &( new_block_descriptor->reverse_index ),
			  &leaf_block_tree_node,
			  &reverse_block_descriptor,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to insert block descriptor in reverse block tree.",
			 function );

			new_block_descriptor = NULL;

			goto on_error;
		}
		else if( result == 0 )
		{
			if( reverse_block_descriptor == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing reverse block descriptor.",
				 function );

				new_block_descriptor = NULL;

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: store: %02d replacing existing reverse block descriptor: 0x08%" PRIx64 ".\n",
				 function,
				 store_index,
				 reverse_block_descriptor->original_offset );
			}
#endif
			if( libvshadow_block_tree_node_set_leaf_value_at_offset(
			     leaf_block_tree_node,
			     new_block_descriptor->relative_offset,
			     new_block_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set reverse leaf value at offset: %" PRIi64 " (0x%08" PRIx64 ").",
				 function,
				 new_block_descriptor->relative_offset,
				 new_block_descriptor->relative_offset );

				new_block_descriptor = NULL;

				goto on_error;
			}
			new_block_descriptor->reverse_index     = reverse_block_descriptor->reverse_index;
			reverse_block_descriptor->reverse_index = -1;

			if( reverse_block_descriptor->index == -1 )
			{
				if( libvshadow_block_descriptor_free(
				     &reverse_block_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to free reverse block descriptor.",
					 function );

					new_block_descriptor = NULL;

					goto on_error;
				}
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		else if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: store: %02d adding reverse block descriptor.\n",
			 function,
			 store_index );
		}
#endif
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	if( new_block_descriptor != NULL )
	{
		libvshadow_block_descriptor_free(
		 &new_block_descriptor,
		 NULL );
	}
	return( -1 );
}

