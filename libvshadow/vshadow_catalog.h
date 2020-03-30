/*
 * The Volume Shadow Snapshot (VSS) catalog definition
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

#if !defined( _VSHADOW_CATALOG_H )
#define _VSHADOW_CATALOG_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vshadow_catalog_header vshadow_catalog_header_t;

struct vshadow_catalog_header
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
	 * Consists of 80 bytes
	 */
	uint8_t unknown1[ 80 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VSHADOW_CATALOG_H ) */

