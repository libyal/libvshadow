/*
 * Python bindings module for libvshadow (pyvshadow)
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

#if !defined( _PYVSHADOW_H )
#define _PYVSHADOW_H

#include <common.h>
#include <types.h>

#include "pyvshadow_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

PyObject *pyvshadow_get_version(
           PyObject *self,
           PyObject *arguments );

PyObject *pyvshadow_check_volume_signature(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvshadow_check_volume_signature_file_object(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvshadow_open_new_volume(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvshadow_open_new_volume_with_file_object(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_pyvshadow(
                void );
#else
PyMODINIT_FUNC initpyvshadow(
                void );
#endif

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSHADOW_H ) */

