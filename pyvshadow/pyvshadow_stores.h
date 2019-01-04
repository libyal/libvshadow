/*
 * Python object definition of the stores sequence and iterator
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

#if !defined( _PYVSHADOW_STORES_H )
#define _PYVSHADOW_STORES_H

#include <common.h>
#include <types.h>

#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"
#include "pyvshadow_volume.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvshadow_stores pyvshadow_stores_t;

struct pyvshadow_stores
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The pyvshadow volume object
	 */
	pyvshadow_volume_t *volume_object;

	/* The get store by index callback function
	 */
	PyObject* (*get_store_by_index)(
	             pyvshadow_volume_t *volume_object,
	             int store_index );

	/* The (current) store index
	 */
	int store_index;

	/* The number of stores
	 */
	int number_of_stores;
};

extern PyTypeObject pyvshadow_stores_type_object;

PyObject *pyvshadow_stores_new(
           pyvshadow_volume_t *volume_object,
           PyObject* (*get_store_by_index)(
                        pyvshadow_volume_t *volume_object,
                        int store_index ),
           int number_of_stores );

int pyvshadow_stores_init(
     pyvshadow_stores_t *pyvshadow_stores );

void pyvshadow_stores_free(
      pyvshadow_stores_t *pyvshadow_stores );

Py_ssize_t pyvshadow_stores_len(
            pyvshadow_stores_t *pyvshadow_stores );

PyObject *pyvshadow_stores_getitem(
           pyvshadow_stores_t *pyvshadow_stores,
           Py_ssize_t item_index );

PyObject *pyvshadow_stores_iter(
           pyvshadow_stores_t *pyvshadow_stores );

PyObject *pyvshadow_stores_iternext(
           pyvshadow_stores_t *pyvshadow_stores );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSHADOW_STORES_H ) */

