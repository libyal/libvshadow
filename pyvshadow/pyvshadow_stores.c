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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvshadow_libcerror.h"
#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"
#include "pyvshadow_store.h"
#include "pyvshadow_stores.h"
#include "pyvshadow_volume.h"

PySequenceMethods pyvshadow_stores_sequence_methods = {
	/* sq_length */
	(lenfunc) pyvshadow_stores_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyvshadow_stores_getitem,
	/* sq_slice */
	0,
	/* sq_ass_item */
	0,
	/* sq_ass_slice */
	0,
	/* sq_contains */
	0,
	/* sq_inplace_concat */
	0,
	/* sq_inplace_repeat */
	0
};

PyTypeObject pyvshadow_stores_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvshadow._stores",
	/* tp_basicsize */
	sizeof( pyvshadow_stores_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvshadow_stores_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	&pyvshadow_stores_sequence_methods,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_ITER,
	/* tp_doc */
	"internal pyvshadow stores sequence and iterator object",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyvshadow_stores_iter,
	/* tp_iternext */
	(iternextfunc) pyvshadow_stores_iternext,
	/* tp_methods */
	0,
	/* tp_members */
	0,
	/* tp_getset */
	0,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyvshadow_stores_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new stores object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_stores_new(
           pyvshadow_volume_t *volume_object,
           PyObject* (*get_store_by_index)(
                        pyvshadow_volume_t *volume_object,
                        int store_index ),
           int number_of_stores )
{
	pyvshadow_stores_t *pyvshadow_stores = NULL;
	static char *function                = "pyvshadow_stores_new";

	if( volume_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume object.",
		 function );

		return( NULL );
	}
	if( get_store_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get store by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the stores values are initialized
	 */
	pyvshadow_stores = PyObject_New(
	                    struct pyvshadow_stores,
	                    &pyvshadow_stores_type_object );

	if( pyvshadow_stores == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize stores.",
		 function );

		goto on_error;
	}
	if( pyvshadow_stores_init(
	     pyvshadow_stores ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize stores.",
		 function );

		goto on_error;
	}
	pyvshadow_stores->volume_object      = volume_object;
	pyvshadow_stores->get_store_by_index = get_store_by_index;
	pyvshadow_stores->number_of_stores   = number_of_stores;

	Py_IncRef(
	 (PyObject *) pyvshadow_stores->volume_object );

	return( (PyObject *) pyvshadow_stores );

on_error:
	if( pyvshadow_stores != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvshadow_stores );
	}
	return( NULL );
}

/* Intializes a stores object
 * Returns 0 if successful or -1 on error
 */
int pyvshadow_stores_init(
     pyvshadow_stores_t *pyvshadow_stores )
{
	static char *function = "pyvshadow_stores_init";

	if( pyvshadow_stores == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores.",
		 function );

		return( -1 );
	}
	/* Make sure the stores values are initialized
	 */
	pyvshadow_stores->volume_object      = NULL;
	pyvshadow_stores->get_store_by_index = NULL;
	pyvshadow_stores->store_index        = 0;
	pyvshadow_stores->number_of_stores   = 0;

	return( 0 );
}

/* Frees a stores object
 */
void pyvshadow_stores_free(
      pyvshadow_stores_t *pyvshadow_stores )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvshadow_stores_free";

	if( pyvshadow_stores == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvshadow_stores );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pyvshadow_stores->volume_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvshadow_stores->volume_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvshadow_stores );
}

/* The stores len() function
 */
Py_ssize_t pyvshadow_stores_len(
            pyvshadow_stores_t *pyvshadow_stores )
{
	static char *function = "pyvshadow_stores_len";

	if( pyvshadow_stores == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pyvshadow_stores->number_of_stores );
}

/* The stores getitem() function
 */
PyObject *pyvshadow_stores_getitem(
           pyvshadow_stores_t *pyvshadow_stores,
           Py_ssize_t item_index )
{
	PyObject *store_object = NULL;
	static char *function  = "pyvshadow_stores_getitem";

	if( pyvshadow_stores == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores.",
		 function );

		return( NULL );
	}
	if( pyvshadow_stores->get_store_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores - missing get store by index function.",
		 function );

		return( NULL );
	}
	if( pyvshadow_stores->number_of_stores < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores - invalid number of stores.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pyvshadow_stores->number_of_stores ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	store_object = pyvshadow_stores->get_store_by_index(
	                pyvshadow_stores->volume_object,
	                (int) item_index );

	return( store_object );
}

/* The stores iter() function
 */
PyObject *pyvshadow_stores_iter(
           pyvshadow_stores_t *pyvshadow_stores )
{
	static char *function = "pyvshadow_stores_iter";

	if( pyvshadow_stores == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pyvshadow_stores );

	return( (PyObject *) pyvshadow_stores );
}

/* The stores iternext() function
 */
PyObject *pyvshadow_stores_iternext(
           pyvshadow_stores_t *pyvshadow_stores )
{
	PyObject *store_object = NULL;
	static char *function  = "pyvshadow_stores_iternext";

	if( pyvshadow_stores == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores.",
		 function );

		return( NULL );
	}
	if( pyvshadow_stores->get_store_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores - missing get store by index function.",
		 function );

		return( NULL );
	}
	if( pyvshadow_stores->store_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores - invalid store index.",
		 function );

		return( NULL );
	}
	if( pyvshadow_stores->number_of_stores < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores - invalid number of stores.",
		 function );

		return( NULL );
	}
	if( pyvshadow_stores->store_index >= pyvshadow_stores->number_of_stores )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	store_object = pyvshadow_stores->get_store_by_index(
	                pyvshadow_stores->volume_object,
	                pyvshadow_stores->store_index );

	if( store_object != NULL )
	{
		pyvshadow_stores->store_index++;
	}
	return( store_object );
}

