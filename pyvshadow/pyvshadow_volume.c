/*
 * Python object definition of the libvshadow volume
 *
 * Copyright (c) 2011-2013, Joachim Metz <joachim.metz@gmail.com>
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

#include "pyvshadow.h"
#include "pyvshadow_file_object_io_handle.h"
#include "pyvshadow_libbfio.h"
#include "pyvshadow_libcerror.h"
#include "pyvshadow_libclocale.h"
#include "pyvshadow_libcstring.h"
#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"
#include "pyvshadow_store.h"
#include "pyvshadow_stores.h"
#include "pyvshadow_unused.h"
#include "pyvshadow_volume.h"

#if !defined( LIBVSHADOW_HAVE_BFIO )
LIBVSHADOW_EXTERN \
int libvshadow_volume_open_file_io_handle(
     libvshadow_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvshadow_error_t **error );
#endif

PyMethodDef pyvshadow_volume_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pyvshadow_volume_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the volume to abort the current activity." },

	/* Functions to access the volume */

	{ "open",
	  (PyCFunction) pyvshadow_volume_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a volume." },

	{ "open_file_object",
	  (PyCFunction) pyvshadow_volume_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a volume using a file-like object." },

	{ "close",
	  (PyCFunction) pyvshadow_volume_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a volume." },

	/* Functions to access the stores */

	{ "get_number_of_stores",
	  (PyCFunction) pyvshadow_volume_get_number_of_stores,
	  METH_NOARGS,
	  "get_number_of_stores() -> Integer\n"
	  "\n"
	  "Retrieves the number of stores." },

	{ "get_store",
	  (PyCFunction) pyvshadow_volume_get_store,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_store(store_index) -> Object or None\n"
	  "\n"
	  "Retrieves a specific store." },

	{ "get_stores",
	  (PyCFunction) pyvshadow_volume_get_stores,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_stores() -> Object\n"
	  "\n"
	  "Retrieves a sequence object of the stores." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvshadow_volume_object_get_set_definitions[] = {

	{ "number_of_stores",
	  (getter) pyvshadow_volume_get_number_of_stores,
	  (setter) 0,
	  "The number of stores.",
	  NULL },

	{ "stores",
	  (getter) pyvshadow_volume_get_stores,
	  (setter) 0,
	  "The stores.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyvshadow_volume_type_object = {
	PyObject_HEAD_INIT( NULL )

	/* ob_size */
	0,
	/* tp_name */
	"pyvshadow.volume",
	/* tp_basicsize */
	sizeof( pyvshadow_volume_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvshadow_volume_free,
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
	"pyvshadow volume object (wraps libvshadow_volume_t)",
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
	pyvshadow_volume_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyvshadow_volume_object_get_set_definitions,
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
	(initproc) pyvshadow_volume_init,
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

/* Creates a new volume object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_new(
           void )
{
	pyvshadow_volume_t *pyvshadow_volume = NULL;
	static char *function                = "pyvshadow_volume_new";

	pyvshadow_volume = PyObject_New(
	                    struct pyvshadow_volume,
	                    &pyvshadow_volume_type_object );

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize volume.",
		 function );

		goto on_error;
	}
	if( pyvshadow_volume_init(
	     pyvshadow_volume ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize volume.",
		 function );

		goto on_error;
	}
	return( (PyObject *) pyvshadow_volume );

on_error:
	if( pyvshadow_volume != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvshadow_volume );
	}
	return( NULL );
}

/* Creates a new volume object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_new_open(
           PyObject *self PYVSHADOW_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pyvshadow_volume = NULL;

	PYVSHADOW_UNREFERENCED_PARAMETER( self )

	pyvshadow_volume = pyvshadow_volume_new();

	pyvshadow_volume_open(
	 (pyvshadow_volume_t *) pyvshadow_volume,
	 arguments,
	 keywords );

	return( pyvshadow_volume );
}

/* Creates a new volume object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_new_open_file_object(
           PyObject *self PYVSHADOW_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pyvshadow_volume = NULL;

	PYVSHADOW_UNREFERENCED_PARAMETER( self )

	pyvshadow_volume = pyvshadow_volume_new();

	pyvshadow_volume_open_file_object(
	 (pyvshadow_volume_t *) pyvshadow_volume,
	 arguments,
	 keywords );

	return( pyvshadow_volume );
}

/* Intializes a volume object
 * Returns 0 if successful or -1 on error
 */
int pyvshadow_volume_init(
     pyvshadow_volume_t *pyvshadow_volume )
{
	char error_string[ PYVSHADOW_ERROR_STRING_SIZE ];

	static char *function    = "pyvshadow_volume_init";
	libcerror_error_t *error = NULL;

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	/* Make sure libvshadow volume is set to NULL
	 */
	pyvshadow_volume->volume = NULL;

	if( libvshadow_volume_initialize(
	     &( pyvshadow_volume->volume ),
	     &error ) != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to initialize volume.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to initialize volume.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a volume object
 */
void pyvshadow_volume_free(
      pyvshadow_volume_t *pyvshadow_volume )
{
	char error_string[ PYVSHADOW_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyvshadow_volume_free";
	int result               = 0;

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return;
	}
	if( pyvshadow_volume->ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume - missing ob_type.",
		 function );

		return;
	}
	if( pyvshadow_volume->ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume - invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pyvshadow_volume->volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume - missing libvshadow volume.",
		 function );

		return;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_volume_free(
	          &( pyvshadow_volume->volume ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to free libvshadow volume.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to free libvshadow volume.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );
	}
	pyvshadow_volume->ob_type->tp_free(
	 (PyObject*) pyvshadow_volume );
}

/* Signals the volume to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_signal_abort(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	char error_string[ PYVSHADOW_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyvshadow_volume_signal_abort";
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_volume_signal_abort(
	          pyvshadow_volume->volume,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to signal abort.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to signal abort.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a volume
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_open(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYVSHADOW_ERROR_STRING_SIZE ];

	libcerror_error_t *error    = NULL;
	char *filename              = NULL;
	char *mode                  = NULL;
	static char *keyword_list[] = { "filename", "mode", NULL };
	static char *function       = "pyvshadow_volume_open";
	int result                  = 0;

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s|s",
	     keyword_list,
	     &filename,
	     &mode ) == 0 )
        {
                return( NULL );
        }
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_volume_open(
	          pyvshadow_volume->volume,
                  filename,
                  LIBVSHADOW_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to open volume.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to open volume.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a volume using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_open_file_object(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYVSHADOW_ERROR_STRING_SIZE ];

	PyObject *file_object            = NULL;
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	char *mode                       = NULL;
	static char *keyword_list[]      = { "file_object", "mode", NULL };
	static char *function            = "pyvshadow_volume_open_file_object";
	int result                       = 0;

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
        {
                return( NULL );
        }
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	if( pyvshadow_file_object_initialize(
	     &file_io_handle,
	     file_object,
	     &error ) != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to initialize file IO handle.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to initialize file IO handle.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_volume_open_file_io_handle(
	          pyvshadow_volume->volume,
                  file_io_handle,
                  LIBVSHADOW_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to open volume.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to open volume.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( NULL );
}

/* Closes a volume
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_close(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	char error_string[ PYVSHADOW_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyvshadow_volume_close";
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_volume_close(
	          pyvshadow_volume->volume,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to close volume.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to close volume.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the number of stores
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_get_number_of_stores(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	char error_string[ PYVSHADOW_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyvshadow_volume_get_number_of_stores";
	int number_of_stores     = 0;
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_volume_get_number_of_stores(
	          pyvshadow_volume->volume,
	          &number_of_stores,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve number of stores.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve number of stores.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( PyInt_FromLong(
	         (long) number_of_stores ) );
}

/* Retrieves a specific store by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_get_store_by_index(
           pyvshadow_volume_t *pyvshadow_volume,
           int store_index )
{
	char error_string[ PYVSHADOW_ERROR_STRING_SIZE ];

	libcerror_error_t *error  = NULL;
	libvshadow_store_t *store = NULL;
	PyObject *store_object    = NULL;
	static char *function     = "pyvshadow_volume_get_store_by_index";
	int result                = 0;

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_volume_get_store(
	          pyvshadow_volume->volume,
	          store_index,
	          &store,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve store: %d.",
			 function,
			 store_index );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve store: %d.\n%s",
			 function,
			 store_index,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	store_object = pyvshadow_store_new(
	                store,
	                pyvshadow_volume );

	if( store_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create store object.",
		 function );

		goto on_error;
	}
	return( store_object );

on_error:
	if( store != NULL )
	{
		libvshadow_store_free(
		 &store,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific store
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_get_store(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *store_object      = NULL;
	static char *keyword_list[] = { "store_index", NULL };
	int store_index             = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &store_index ) == 0 )
        {
		return( NULL );
        }
	store_object = pyvshadow_volume_get_store_by_index(
	                pyvshadow_volume,
	                store_index );

	return( store_object );
}

/* Retrieves a stores sequence and iterator object for the stores
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_get_stores(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	char error_string[ PYVSHADOW_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	PyObject *stores_object  = NULL;
	static char *function    = "pyvshadow_volume_get_stores";
	int number_of_stores     = 0;
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_volume_get_number_of_stores(
	          pyvshadow_volume->volume,
	          &number_of_stores,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve number of stores.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve number of stores.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	stores_object = pyvshadow_stores_new(
	                 pyvshadow_volume,
	                 &pyvshadow_volume_get_store_by_index,
	                 number_of_stores );

	if( stores_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create stores object.",
		 function );

		return( NULL );
	}
	return( stores_object );
}

