/*
 * Python object definition of the libvshadow block
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

#if !defined( _PYVSHADOW_BLOCK_H )
#define _PYVSHADOW_BLOCK_H

#include <common.h>
#include <types.h>

#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"
#include "pyvshadow_store.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvshadow_block pyvshadow_block_t;

struct pyvshadow_block
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvshadow block
	 */
	libvshadow_block_t *block;

	/* The pyvshadow store object
	 */
	pyvshadow_store_t *store_object;
};

extern PyMethodDef pyvshadow_block_object_methods[];
extern PyTypeObject pyvshadow_block_type_object;

PyObject *pyvshadow_block_new(
           libvshadow_block_t *block,
           pyvshadow_store_t *store_object );

int pyvshadow_block_init(
     pyvshadow_block_t *pyvshadow_block );

void pyvshadow_block_free(
      pyvshadow_block_t *pyvshadow_block );

PyObject *pyvshadow_block_get_original_offset(
           pyvshadow_block_t *pyvshadow_block,
           PyObject *arguments );

PyObject *pyvshadow_block_get_relative_offset(
           pyvshadow_block_t *pyvshadow_block,
           PyObject *arguments );

PyObject *pyvshadow_block_get_offset(
           pyvshadow_block_t *pyvshadow_block,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSHADOW_BLOCK_H ) */

