/*
 * Python object definition of the libvshadow block flags
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

#if !defined( _PYVSHADOW_BLOCK_FLAGS_H )
#define _PYVSHADOW_BLOCK_FLAGS_H

#include <common.h>
#include <types.h>

#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvshadow_block_flags pyvshadow_block_flags_t;

struct pyvshadow_block_flags
{
	/* Python object initialization
	 */
	PyObject_HEAD
};

extern PyTypeObject pyvshadow_block_flags_type_object;

int pyvshadow_block_flags_init_type(
     PyTypeObject *type_object );

PyObject *pyvshadow_block_flags_new(
           void );

int pyvshadow_block_flags_init(
     pyvshadow_block_flags_t *definitions_object );

void pyvshadow_block_flags_free(
      pyvshadow_block_flags_t *definitions_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSHADOW_BLOCK_FLAGS_H ) */

