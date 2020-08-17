/*
 * Python object wrapper of libvshadow_block_t
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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvshadow_block.h"
#include "pyvshadow_error.h"
#include "pyvshadow_integer.h"
#include "pyvshadow_libcerror.h"
#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"
#include "pyvshadow_unused.h"

PyMethodDef pyvshadow_block_object_methods[] = {

	{ "get_original_offset",
	  (PyCFunction) pyvshadow_block_get_original_offset,
	  METH_NOARGS,
	  "get_original_offset() -> Integer\n"
	  "\n"
	  "Retrieves the original offset." },

	{ "get_relative_offset",
	  (PyCFunction) pyvshadow_block_get_relative_offset,
	  METH_NOARGS,
	  "get_relative_offset() -> Integer\n"
	  "\n"
	  "Retrieves the relative offset." },

	{ "get_offset",
	  (PyCFunction) pyvshadow_block_get_offset,
	  METH_NOARGS,
	  "get_offset() -> Integer\n"
	  "\n"
	  "Retrieves the offset." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvshadow_block_object_get_set_definitions[] = {

	{ "original_offset",
	  (getter) pyvshadow_block_get_original_offset,
	  (setter) 0,
	  "The original offset.",
	  NULL },

	{ "relative_offset",
	  (getter) pyvshadow_block_get_relative_offset,
	  (setter) 0,
	  "The relative offset.",
	  NULL },

	{ "offset",
	  (getter) pyvshadow_block_get_offset,
	  (setter) 0,
	  "The offset.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyvshadow_block_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvshadow.block",
	/* tp_basicsize */
	sizeof( pyvshadow_block_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvshadow_block_free,
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
	0,
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
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyvshadow block object (wraps libvshadow_block_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyvshadow_block_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyvshadow_block_object_get_set_definitions,
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
	(initproc) pyvshadow_block_init,
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

/* Creates a new block object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_block_new(
           libvshadow_block_t *block,
           PyObject *parent_object )
{
	pyvshadow_block_t *pyvshadow_block = NULL;
	static char *function              = "pyvshadow_block_new";

	if( block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid block.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyvshadow_block = PyObject_New(
	                   struct pyvshadow_block,
	                   &pyvshadow_block_type_object );

	if( pyvshadow_block == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize block.",
		 function );

		goto on_error;
	}
	pyvshadow_block->block         = block;
	pyvshadow_block->parent_object = parent_object;

	if( pyvshadow_block->parent_object != NULL )
	{
		Py_IncRef(
		 pyvshadow_block->parent_object );
	}
	return( (PyObject *) pyvshadow_block );

on_error:
	if( pyvshadow_block != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvshadow_block );
	}
	return( NULL );
}

/* Initializes a block object
 * Returns 0 if successful or -1 on error
 */
int pyvshadow_block_init(
     pyvshadow_block_t *pyvshadow_block )
{
	static char *function = "pyvshadow_block_init";

	if( pyvshadow_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	/* Make sure libvshadow block is set to NULL
	 */
	pyvshadow_block->block = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of block not supported.",
	 function );

	return( -1 );
}

/* Frees a block object
 */
void pyvshadow_block_free(
      pyvshadow_block_t *pyvshadow_block )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvshadow_block_free";
	int result                  = 0;

	if( pyvshadow_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid block.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvshadow_block );

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
	if( pyvshadow_block->block != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libvshadow_block_free(
		          &( pyvshadow_block->block ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvshadow_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libvshadow block.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyvshadow_block->parent_object != NULL )
	{
		Py_DecRef(
		 pyvshadow_block->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvshadow_block );
}

/* Retrieves the original offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_block_get_original_offset(
           pyvshadow_block_t *pyvshadow_block,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyvshadow_block_get_original_offset";
	off64_t offset           = 0;
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid block.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_block_get_original_offset(
	          pyvshadow_block->block,
	          &offset,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve original offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pyvshadow_integer_signed_new_from_64bit(
	                  (int64_t) offset );

	return( integer_object );
}

/* Retrieves the relative offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_block_get_relative_offset(
           pyvshadow_block_t *pyvshadow_block,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyvshadow_block_get_relative_offset";
	off64_t offset           = 0;
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid block.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_block_get_relative_offset(
	          pyvshadow_block->block,
	          &offset,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve relative offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pyvshadow_integer_signed_new_from_64bit(
	                  (int64_t) offset );

	return( integer_object );
}

/* Retrieves the offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_block_get_offset(
           pyvshadow_block_t *pyvshadow_block,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyvshadow_block_get_offset";
	off64_t offset           = 0;
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid block.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_block_get_offset(
	          pyvshadow_block->block,
	          &offset,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pyvshadow_integer_signed_new_from_64bit(
	                  (int64_t) offset );

	return( integer_object );
}

