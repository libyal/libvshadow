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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvshadow_error.h"
#include "pyvshadow_file_object_io_handle.h"
#include "pyvshadow_integer.h"
#include "pyvshadow_libbfio.h"
#include "pyvshadow_libcerror.h"
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

#endif /* !defined( LIBVSHADOW_HAVE_BFIO ) */

PyMethodDef pyvshadow_volume_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pyvshadow_volume_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the volume to abort the current activity." },

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

	{ "get_number_of_stores",
	  (PyCFunction) pyvshadow_volume_get_number_of_stores,
	  METH_NOARGS,
	  "get_number_of_stores() -> Integer\n"
	  "\n"
	  "Retrieves the number of stores." },

	{ "get_store",
	  (PyCFunction) pyvshadow_volume_get_store,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_store(store_index) -> Object\n"
	  "\n"
	  "Retrieves the store specified by the index." },

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
	PyVarObject_HEAD_INIT( NULL, 0 )

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

/* Initializes a volume object
 * Returns 0 if successful or -1 on error
 */
int pyvshadow_volume_init(
     pyvshadow_volume_t *pyvshadow_volume )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyvshadow_volume_init";

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
	pyvshadow_volume->volume         = NULL;
	pyvshadow_volume->file_io_handle = NULL;

	if( libvshadow_volume_initialize(
	     &( pyvshadow_volume->volume ),
	     &error ) != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize volume.",
		 function );

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
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvshadow_volume_free";
	int result                  = 0;

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvshadow_volume );

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
	if( pyvshadow_volume->volume != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libvshadow_volume_free(
		          &( pyvshadow_volume->volume ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvshadow_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libvshadow volume.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	ob_type->tp_free(
	 (PyObject*) pyvshadow_volume );
}

/* Signals the volume to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_signal_abort(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
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
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to signal abort.",
		 function );

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
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	const char *filename_narrow  = NULL;
	static char *function        = "pyvshadow_volume_open";
	static char *keyword_list[]  = { "filename", "mode", NULL };
	char *mode                   = NULL;
	int result                   = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object,
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
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pyvshadow_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type Unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
		Py_BEGIN_ALLOW_THREADS

		result = libvshadow_volume_open_wide(
		          pyvshadow_volume->volume,
		          filename_wide,
		          LIBVSHADOW_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pyvshadow_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert Unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
		                   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libvshadow_volume_open(
		          pyvshadow_volume->volume,
		          filename_narrow,
		          LIBVSHADOW_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result != 1 )
		{
			pyvshadow_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open volume.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pyvshadow_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   string_object );
#else
		filename_narrow = PyString_AsString(
		                   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libvshadow_volume_open(
		          pyvshadow_volume->volume,
		          filename_narrow,
		          LIBVSHADOW_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvshadow_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open volume.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Opens a volume using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_open_file_object(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object       = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvshadow_volume_open_file_object";
	static char *keyword_list[] = { "file_object", "mode", NULL };
	char *mode                  = NULL;
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
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "read" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing read attribute.",
		 function );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "seek" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing seek attribute.",
		 function );

		return( NULL );
	}
	if( pyvshadow_volume->file_io_handle != NULL )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: invalid volume - file IO handle already set.",
		 function );

		goto on_error;
	}
	if( pyvshadow_file_object_initialize(
	     &( pyvshadow_volume->file_io_handle ),
	     file_object,
	     &error ) != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_volume_open_file_io_handle(
	          pyvshadow_volume->volume,
	          pyvshadow_volume->file_io_handle,
	          LIBVSHADOW_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open volume.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pyvshadow_volume->file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &( pyvshadow_volume->file_io_handle ),
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
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to close volume.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( pyvshadow_volume->file_io_handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_handle_free(
		          &( pyvshadow_volume->file_io_handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvshadow_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libbfio file IO handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
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
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyvshadow_volume_get_number_of_stores";
	int number_of_stores     = 0;
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

	result = libvshadow_volume_get_number_of_stores(
	          pyvshadow_volume->volume,
	          &number_of_stores,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of stores.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_stores );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_stores );
#endif
	return( integer_object );
}

/* Retrieves a specific store by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_get_store_by_index(
           PyObject *pyvshadow_volume,
           int store_index )
{
	PyObject *store_object    = NULL;
	libcerror_error_t *error  = NULL;
	libvshadow_store_t *store = NULL;
	static char *function     = "pyvshadow_volume_get_store_by_index";
	int result                = 0;

	if( pyvshadow_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_volume_get_store(
	          ( (pyvshadow_volume_t *) pyvshadow_volume )->volume,
	          store_index,
	          &store,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve store: %d.",
		 function,
		 store_index );

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
	                (PyObject *) pyvshadow_volume,
	                store_index );

	return( store_object );
}

/* Retrieves a sequence and iterator object for the stores
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_volume_get_stores(
           pyvshadow_volume_t *pyvshadow_volume,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyvshadow_volume_get_stores";
	int number_of_stores      = 0;
	int result                = 0;

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

	result = libvshadow_volume_get_number_of_stores(
	          pyvshadow_volume->volume,
	          &number_of_stores,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of stores.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyvshadow_stores_new(
	                   (PyObject *) pyvshadow_volume,
	                   &pyvshadow_volume_get_store_by_index,
	                   number_of_stores );

	if( sequence_object == NULL )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

