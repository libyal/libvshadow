/*
 * Block functions
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

#include "libvshadow_block.h"
#include "libvshadow_block_descriptor.h"
#include "libvshadow_definitions.h"
#include "libvshadow_libcerror.h"
#include "libvshadow_types.h"

/* Creates a block
 * Make sure the value block is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_initialize(
     libvshadow_block_t **block,
     libvshadow_block_descriptor_t *block_descriptor,
     libcerror_error_t **error )
{
	libvshadow_internal_block_t *internal_block = NULL;
	static char *function                       = "libvshadow_block_initialize";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	if( *block != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block value already set.",
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
	internal_block = memory_allocate_structure(
	                  libvshadow_internal_block_t );

	if( internal_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_block,
	     0,
	     sizeof( libvshadow_internal_block_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block.",
		 function );

		goto on_error;
	}
	internal_block->block_descriptor = block_descriptor;

	*block = (libvshadow_block_t *) internal_block;

	return( 1 );

on_error:
	if( internal_block != NULL )
	{
		memory_free(
		 internal_block );
	}
	return( -1 );
}

/* Frees a block
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_free(
     libvshadow_block_t **block,
     libcerror_error_t **error )
{
	libvshadow_internal_block_t *internal_block = NULL;
	static char *function                       = "libvshadow_block_free";
	int result                                  = 1;

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	if( *block != NULL )
	{
		internal_block = (libvshadow_internal_block_t *) *block;
		*block         = NULL;

		memory_free(
		 internal_block );
	}
	return( result );
}

/* Retrieves the original offset
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_get_original_offset(
     libvshadow_block_t *block,
     off64_t *original_offset,
     libcerror_error_t **error )
{
	libvshadow_internal_block_t *internal_block = NULL;
	static char *function                       = "libvshadow_block_get_original_offset";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libvshadow_internal_block_t *) block;

	if( internal_block->block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid block - missing block descriptor.",
		 function );

		return( -1 );
	}
	if( original_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid original offset.",
		 function );

		return( -1 );
	}
	*original_offset = internal_block->block_descriptor->original_offset;

	return( 1 );
}

/* Retrieves the relative offset
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_get_relative_offset(
     libvshadow_block_t *block,
     off64_t *relative_offset,
     libcerror_error_t **error )
{
	libvshadow_internal_block_t *internal_block = NULL;
	static char *function                       = "libvshadow_block_get_relative_offset";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libvshadow_internal_block_t *) block;

	if( internal_block->block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid block - missing block descriptor.",
		 function );

		return( -1 );
	}
	if( relative_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid relative offset.",
		 function );

		return( -1 );
	}
	*relative_offset = internal_block->block_descriptor->relative_offset;

	return( 1 );
}

/* Retrieves the offset
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_get_offset(
     libvshadow_block_t *block,
     off64_t *offset,
     libcerror_error_t **error )
{
	libvshadow_internal_block_t *internal_block = NULL;
	static char *function                       = "libvshadow_block_get_offset";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libvshadow_internal_block_t *) block;

	if( internal_block->block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid block - missing block descriptor.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	*offset = internal_block->block_descriptor->offset;

	return( 1 );
}

/* Retrieves the values
 * Returns 1 if successful or -1 on error
 */
int libvshadow_block_get_values(
     libvshadow_block_t *block,
     off64_t *original_offset,
     off64_t *relative_offset,
     off64_t *offset,
     uint32_t *flags,
     uint32_t *bitmap,
     libcerror_error_t **error )
{
	libvshadow_internal_block_t *internal_block = NULL;
	static char *function                       = "libvshadow_block_get_values";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	internal_block = (libvshadow_internal_block_t *) block;

	if( internal_block->block_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid block - missing block descriptor.",
		 function );

		return( -1 );
	}
	if( original_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid original offset.",
		 function );

		return( -1 );
	}
	if( relative_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid relative offset.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	if( flags == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid flags.",
		 function );

		return( -1 );
	}
	if( bitmap == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bitmap.",
		 function );

		return( -1 );
	}
	*original_offset = internal_block->block_descriptor->original_offset;
	*relative_offset = internal_block->block_descriptor->relative_offset;
	*offset          = internal_block->block_descriptor->offset;
	*flags           = internal_block->block_descriptor->flags;
	*bitmap          = internal_block->block_descriptor->bitmap;

	return( 1 );
}

