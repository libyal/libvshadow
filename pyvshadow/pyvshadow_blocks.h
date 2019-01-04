/*
 * Python object definition of the blocks sequence and iterator
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

#if !defined( _PYVSHADOW_BLOCKS_H )
#define _PYVSHADOW_BLOCKS_H

#include <common.h>
#include <types.h>

#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"
#include "pyvshadow_store.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvshadow_blocks pyvshadow_blocks_t;

struct pyvshadow_blocks
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The pyvshadow store object
	 */
	pyvshadow_store_t *store_object;

	/* The get block by index callback function
	 */
	PyObject* (*get_block_by_index)(
	             pyvshadow_store_t *store_object,
	             int block_index );

	/* The (current) block index
	 */
	int block_index;

	/* The number of blocks
	 */
	int number_of_blocks;
};

extern PyTypeObject pyvshadow_blocks_type_object;

PyObject *pyvshadow_blocks_new(
           pyvshadow_store_t *store_object,
           PyObject* (*get_block_by_index)(
                        pyvshadow_store_t *store_object,
                        int block_index ),
           int number_of_blocks );

int pyvshadow_blocks_init(
     pyvshadow_blocks_t *pyvshadow_blocks );

void pyvshadow_blocks_free(
      pyvshadow_blocks_t *pyvshadow_blocks );

Py_ssize_t pyvshadow_blocks_len(
            pyvshadow_blocks_t *pyvshadow_blocks );

PyObject *pyvshadow_blocks_getitem(
           pyvshadow_blocks_t *pyvshadow_blocks,
           Py_ssize_t item_index );

PyObject *pyvshadow_blocks_iter(
           pyvshadow_blocks_t *pyvshadow_blocks );

PyObject *pyvshadow_blocks_iternext(
           pyvshadow_blocks_t *pyvshadow_blocks );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSHADOW_BLOCKS_H ) */

