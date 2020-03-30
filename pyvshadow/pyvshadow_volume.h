/*
 * Python object wrapper of libvshadow_volume_t
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

#if !defined( _PYVSHADOW_VOLUME_H )
#define _PYVSHADOW_VOLUME_H

#include <common.h>
#include <types.h>

#include "pyvshadow_libbfio.h"
#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvshadow_volume pyvshadow_volume_t;

struct pyvshadow_volume
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvshadow volume
	 */
	libvshadow_volume_t *volume;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pyvshadow_volume_object_methods[];
extern PyTypeObject pyvshadow_volume_type_object;

int pyvshadow_volume_init(
     pyvshadow_volume_t *pyvshadow_volume );

void pyvshadow_volume_free(
      pyvshadow_volume_t *pyvshadow_volume );

PyObject *pyvshadow_volume_signal_abort(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments );

PyObject *pyvshadow_volume_open(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvshadow_volume_open_file_object(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvshadow_volume_close(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments );

PyObject *pyvshadow_volume_get_number_of_stores(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments );

PyObject *pyvshadow_volume_get_store_by_index(
           PyObject *pyvshadow_volume,
           int store_index );

PyObject *pyvshadow_volume_get_store(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvshadow_volume_get_stores(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSHADOW_VOLUME_H ) */

