/*
 * The Volume Shadow Snapshot (VSS) store definition
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

#if !defined( _VSHADOW_STORE_H )
#define _VSHADOW_STORE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vshadow_store_header vshadow_store_header_t;

struct vshadow_store_header
{
	/* The identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t identifier[ 16 ];

	/* The version
	 * Consists of 4 bytes
	 */
	uint8_t version[ 4 ];

	/* The record type
	 * Consists of 4 bytes
	 */
	uint8_t record_type[ 4 ];

	/* The relative offset
	 * Consists of 8 bytes
	 */
	uint8_t relative_offset[ 8 ];

	/* The (current) offset
	 * Consists of 8 bytes
	 */
	uint8_t offset[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown2[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown3[ 8 ];

	/* Unknown
	 * Consists of 72 bytes
	 */
	uint8_t unknown4[ 72 ];
};

typedef struct vshadow_store_information vshadow_store_information_t;

struct vshadow_store_information
{
	/* Unknown
	 * Consists of 16 bytes
	 */
	uint8_t unknown5[ 16 ];

	/* The (shadow) copy identifier
	 * Consists of 8 bytes
	 */
	uint8_t copy_identifier[ 16 ];

	/* The (shadow) copy set identifier
	 * Consists of 8 bytes
	 */
	uint8_t copy_set_identifier[ 16 ];

	/* The type
	 * Consists of 4 bytes
	 */
	uint8_t type[ 4 ];

	/* The provider
	 * Consists of 4 bytes
	 */
	uint8_t provider[ 4 ];

	/* The attribute flags
	 * Consists of 4 bytes
	 */
	uint8_t attribute_flags[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown10[ 4 ];
};

typedef struct vshadow_store_block_header vshadow_store_block_header_t;

struct vshadow_store_block_header
{
	/* The identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t identifier[ 16 ];

	/* The version
	 * Consists of 4 bytes
	 */
	uint8_t version[ 4 ];

	/* The record type
	 * Consists of 4 bytes
	 */
	uint8_t record_type[ 4 ];

	/* The relative offset
	 * Consists of 8 bytes
	 */
	uint8_t relative_offset[ 8 ];

	/* The (current) offset
	 * Consists of 8 bytes
	 */
	uint8_t offset[ 8 ];

	/* The next offset
	 * Consists of 8 bytes
	 */
	uint8_t next_offset[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];

	/* Unknown
	 * Consists of 72 bytes
	 */
	uint8_t unknown2[ 72 ];
};

typedef struct vshadow_store_block_list_entry vshadow_store_block_list_entry_t;

struct vshadow_store_block_list_entry
{
	/* The original (volume) offset
	 * Consists of 8 bytes
	 */
	uint8_t original_offset[ 8 ];

	/* The relative (store) offset
	 * Consists of 8 bytes
	 */
	uint8_t relative_offset[ 8 ];

	/* The (store) offset
	 * Consists of 8 bytes
	 */
	uint8_t offset[ 8 ];

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* The allocation bitmap
	 * Consists of 4 bytes
	 */
	uint8_t allocation_bitmap[ 4 ];
};

typedef struct vshadow_store_block_range_list_entry vshadow_store_block_range_list_entry_t;

struct vshadow_store_block_range_list_entry
{
	/* The (store) offset
	 * Consists of 8 bytes
	 */
	uint8_t offset[ 8 ];

	/* The relative (store) offset
	 * Consists of 8 bytes
	 */
	uint8_t relative_offset[ 8 ];

	/* The size
	 * Consists of 8 bytes
	 */
	uint8_t size[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VSHADOW_STORE_H ) */

