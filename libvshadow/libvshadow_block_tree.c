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

#include <common.h>
#include <types.h>

#include "libvshadow_block_descriptor.h"
#include "libvshadow_definitions.h"
#include "libvshadow_libcdata.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_libcnotify.h"
#include "libvshadow_unused.h"

/* Inserts a block descriptor in the block tree
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_tree_insert(
     libcdata_btree_t *forward_block_tree,
     libcdata_btree_t *reverse_block_tree,
     libvshadow_block_descriptor_t *block_descriptor,
     int store_index LIBVSHADOW_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libcdata_tree_node_t *existing_tree_node                 = NULL;
	libcdata_tree_node_t *reverse_tree_node                  = NULL;
	libvshadow_block_descriptor_t *existing_block_descriptor = NULL;
	libvshadow_block_descriptor_t *new_block_descriptor      = NULL;
	libvshadow_block_descriptor_t *overlay_block_descriptor  = NULL;
	libvshadow_block_descriptor_t *reverse_block_descriptor  = NULL;
	static char *function                                    = "libvshadow_block_tree_insert";
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
	if( ( new_block_descriptor->flags & LIBVSHADOW_BLOCK_FLAG_IS_OVERLAY ) == 0 )
	{
		/* The reverse block tree is used to detect forwarder block descriptors that point to each other
		 */
		result = libcdata_btree_get_value_by_value(
			  reverse_block_tree,
			  (intptr_t *) new_block_descriptor,
			  (int (*)(intptr_t *, intptr_t *, libcerror_error_t **)) &libvshadow_block_descriptor_compare_reverse,
			  &reverse_tree_node,
			  (intptr_t **) &reverse_block_descriptor,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve reverse block descriptor from reverse block tree.",
			 function );

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
				 "%s: store: %02d found reverse block descriptor: 0x%08" PRIx64 ".\n",
				 function,
				 store_index,
				 reverse_block_descriptor->original_offset );

				libcnotify_printf(
				 "%s: store: %02d swapping original offset.\n",
				 function,
				 store_index );
			}
#endif
			new_block_descriptor->original_offset = reverse_block_descriptor->original_offset;

			if( libcdata_btree_remove_value(
			     reverse_block_tree,
			     reverse_tree_node,
			     &( reverse_block_descriptor->reverse_index ),
			     (intptr_t *) reverse_block_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_REMOVE_FAILED,
				 "%s: unable to remove reverse block descriptor: 0x%08" PRIx64 " from reverse block tree node.",
				 function,
				 reverse_block_descriptor->original_offset );

				goto on_error;
			}
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
	if( ( new_block_descriptor->flags & LIBVSHADOW_BLOCK_FLAG_IS_FORWARDER ) != 0 )
	{
		if( new_block_descriptor->original_offset == new_block_descriptor->relative_offset )
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
			return( 1 );
		}
	}
	result = libcdata_btree_insert_value(
		  forward_block_tree,
	          &( new_block_descriptor->index ),
		  (intptr_t *) new_block_descriptor,
		  (int (*)(intptr_t *, intptr_t *, libcerror_error_t **)) &libvshadow_block_descriptor_compare_by_original_offset,
		  &existing_tree_node,
		  (intptr_t **) &existing_block_descriptor,
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
#endif
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
		if( libcdata_btree_replace_value(
		     forward_block_tree,
		     existing_tree_node,
		     &( existing_block_descriptor->index ),
		     (intptr_t *) existing_block_descriptor,
		     &( new_block_descriptor->index ),
		     (intptr_t *) new_block_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_REMOVE_FAILED,
			 "%s: unable to replace existing block descriptor: %d.",
			 function,
			 existing_block_descriptor->index );

			goto on_error;
		}
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
		result = libcdata_btree_insert_value(
			  reverse_block_tree,
			  &( new_block_descriptor->reverse_index ),
			  (intptr_t *) new_block_descriptor,
			  (int (*)(intptr_t *, intptr_t *, libcerror_error_t **)) &libvshadow_block_descriptor_compare_by_relative_offset,
			  &reverse_tree_node,
			  (intptr_t **) &reverse_block_descriptor,
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
			if( libcdata_btree_replace_value(
			     reverse_block_tree,
			     reverse_tree_node,
			     &( reverse_block_descriptor->reverse_index ),
			     (intptr_t *) reverse_block_descriptor,
			     &( new_block_descriptor->reverse_index ),
			     (intptr_t *) new_block_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_REMOVE_FAILED,
				 "%s: unable to replace reverse block descriptor: %d.",
				 function,
				 reverse_block_descriptor->reverse_index );

				new_block_descriptor = NULL;

				goto on_error;
			}
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

