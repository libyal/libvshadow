/*
 * Python object definition of the libvshadow store
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

#if !defined( _PYVSHADOW_STORE_H )
#define _PYVSHADOW_STORE_H

#include <common.h>
#include <types.h>

#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"
#include "pyvshadow_volume.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvshadow_store pyvshadow_store_t;

struct pyvshadow_store
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvshadow store
	 */
	libvshadow_store_t *store;

	/* The pyvshadow volume object
	 */
	pyvshadow_volume_t *volume_object;
};

extern PyMethodDef pyvshadow_store_object_methods[];
extern PyTypeObject pyvshadow_store_type_object;

PyObject *pyvshadow_store_new(
           libvshadow_store_t *store,
           pyvshadow_volume_t *volume_object );

int pyvshadow_store_init(
     pyvshadow_store_t *pyvshadow_store );

void pyvshadow_store_free(
      pyvshadow_store_t *pyvshadow_store );

PyObject *pyvshadow_store_has_in_volume_data(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments );

PyObject *pyvshadow_store_read_buffer(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvshadow_store_read_buffer_at_offset(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvshadow_store_seek_offset(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvshadow_store_get_offset(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments );

PyObject *pyvshadow_store_get_size(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments );

PyObject *pyvshadow_store_get_volume_size(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments );

PyObject *pyvshadow_store_get_identifier(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments );

PyObject *pyvshadow_store_get_creation_time(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments );

PyObject *pyvshadow_store_get_creation_time_as_integer(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments );

PyObject *pyvshadow_store_get_copy_identifier(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments );

PyObject *pyvshadow_store_get_copy_set_identifier(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments );

PyObject *pyvshadow_store_get_number_of_blocks(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments );

PyObject *pyvshadow_store_get_block_by_index(
           pyvshadow_store_t *pyvshadow_store,
           int block_index );

PyObject *pyvshadow_store_get_block(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvshadow_store_get_blocks(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSHADOW_STORE_H ) */

