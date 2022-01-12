/*
 * Python object definition of the sequence and iterator object of stores
 *
 * Copyright (C) 2011-2022, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYVSHADOW_STORES_H )
#define _PYVSHADOW_STORES_H

#include <common.h>
#include <types.h>

#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvshadow_stores pyvshadow_stores_t;

struct pyvshadow_stores
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pyvshadow_stores_type_object;

PyObject *pyvshadow_stores_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyvshadow_stores_init(
     pyvshadow_stores_t *sequence_object );

void pyvshadow_stores_free(
      pyvshadow_stores_t *sequence_object );

Py_ssize_t pyvshadow_stores_len(
            pyvshadow_stores_t *sequence_object );

PyObject *pyvshadow_stores_getitem(
           pyvshadow_stores_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pyvshadow_stores_iter(
           pyvshadow_stores_t *sequence_object );

PyObject *pyvshadow_stores_iternext(
           pyvshadow_stores_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSHADOW_STORES_H ) */

