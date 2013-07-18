/*
 * Python bindings module for libvshadow (pyvshadow)
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
#include "pyvshadow_block.h"
#include "pyvshadow_blocks.h"
#include "pyvshadow_file_object_io_handle.h"
#include "pyvshadow_libcerror.h"
#include "pyvshadow_libcstring.h"
#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"
#include "pyvshadow_store.h"
#include "pyvshadow_stores.h"
#include "pyvshadow_unused.h"
#include "pyvshadow_volume.h"

#if !defined( LIBVSHADOW_HAVE_BFIO )
LIBVSHADOW_EXTERN \
int libvshadow_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libvshadow_error_t **error );
#endif

/* The pyvshadow module methods
 */
PyMethodDef pyvshadow_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pyvshadow_get_version,
	  METH_NOARGS,
	  "get_version() -> String\n"
	  "\n"
	  "Retrieves the version." },

	{ "check_volume_signature",
	  (PyCFunction) pyvshadow_check_volume_signature,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_volume_signature(filename) -> Boolean\n"
	  "\n"
	  "Checks if a volume has a Windows NT Volume Shadow Snapshot (VSS) volume signature." },

	{ "check_volume_signature_file_object",
	  (PyCFunction) pyvshadow_check_volume_signature_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_volume_signature(file_object) -> Boolean\n"
	  "\n"
	  "Checks if a volume has a Windows NT Volume Shadow Snapshot (VSS) volume signature using a file-like object." },

	{ "open",
	  (PyCFunction) pyvshadow_volume_new_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> Object\n"
	  "\n"
	  "Opens a volume." },

	{ "open_file_object",
	  (PyCFunction) pyvshadow_volume_new_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> Object\n"
	  "\n"
	  "Opens a volume using a file-like object." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

/* Retrieves the pyvshadow/libvshadow version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_get_version(
           PyObject *self PYVSHADOW_ATTRIBUTE_UNUSED,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	const char *errors           = NULL;
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( self )
	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = libvshadow_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = libcstring_narrow_string_length(
	                         version_string );

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) version_string_length,
	         errors ) );
}

/* Checks if the volume has a Windows NT Volume Shadow Snapshot (VSS) volume signature
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_check_volume_signature(
           PyObject *self PYVSHADOW_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYVSHADOW_ERROR_STRING_SIZE ];

	libcerror_error_t *error    = NULL;
	static char *function       = "pyvshadow_check_volume_signature";
	static char *keyword_list[] = { "filename", NULL };
	const char *filename        = NULL;
	int result                  = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( self )

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|s",
	     keyword_list,
	     &filename ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_check_volume_signature(
	          filename,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to check volume signature.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to check volume signature.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( result != 0 )
	{
		return( Py_True );
	}
	return( Py_False );
}

/* Checks if the volume has a Windows NT Volume Shadow Snapshot (VSS) volume signature using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_check_volume_signature_file_object(
           PyObject *self PYVSHADOW_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYVSHADOW_ERROR_STRING_SIZE ];

	libcerror_error_t *error         = NULL;
	libbfio_handle_t *file_io_handle = NULL;
	PyObject *file_object            = NULL;
	static char *function            = "pyvshadow_check_volume_signature_file_object";
	static char *keyword_list[]      = { "file_object", NULL };
	int result                       = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( self )

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|O",
	     keyword_list,
	     &file_object ) == 0 )
	{
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

	result = libvshadow_check_volume_signature_file_io_handle(
	          file_io_handle,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to check volume signature.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to check volume signature.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( libbfio_handle_free(
	     &file_io_handle,
	     &error ) != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYVSHADOW_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to free file IO handle.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to free file IO handle.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( result != 0 )
	{
		return( Py_True );
	}
	return( Py_False );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( NULL );
}

/* Declarations for DLL import/export
 */
#ifndef PyMODINIT_FUNC
#define PyMODINIT_FUNC void
#endif

/* Initializes the pyvshadow module
 */
PyMODINIT_FUNC initpyvshadow(
                void )
{
	PyObject *module                 = NULL;
	PyTypeObject *block_type_object  = NULL;
	PyTypeObject *blocks_type_object = NULL;
	PyTypeObject *store_type_object  = NULL;
	PyTypeObject *stores_type_object = NULL;
	PyTypeObject *volume_type_object = NULL;
	PyGILState_STATE gil_state       = 0;

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
	module = Py_InitModule3(
	          "pyvshadow",
	          pyvshadow_module_methods,
	          "Python libvshadow module (pyvshadow)." );

	PyEval_InitThreads();

	gil_state = PyGILState_Ensure();

	/* Setup the volume type object
	 */
	pyvshadow_volume_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvshadow_volume_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvshadow_volume_type_object );

	volume_type_object = &pyvshadow_volume_type_object;

	PyModule_AddObject(
	 module,
	 "volume",
	 (PyObject *) volume_type_object );

	/* Setup the stores type object
	 */
	pyvshadow_stores_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvshadow_stores_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvshadow_stores_type_object );

	stores_type_object = &pyvshadow_stores_type_object;

	PyModule_AddObject(
	 module,
	 "_stores",
	 (PyObject *) stores_type_object );

	/* Setup the store type object
	 */
	pyvshadow_store_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvshadow_store_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvshadow_store_type_object );

	store_type_object = &pyvshadow_store_type_object;

	PyModule_AddObject(
	 module,
	 "store",
	 (PyObject *) store_type_object );

	/* Setup the blocks type object
	 */
	pyvshadow_blocks_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvshadow_blocks_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvshadow_blocks_type_object );

	blocks_type_object = &pyvshadow_blocks_type_object;

	PyModule_AddObject(
	 module,
	 "_blocks",
	 (PyObject *) blocks_type_object );

	/* Setup the block type object
	 */
	pyvshadow_block_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvshadow_block_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvshadow_block_type_object );

	block_type_object = &pyvshadow_block_type_object;

	PyModule_AddObject(
	 module,
	 "block",
	 (PyObject *) block_type_object );

on_error:
	PyGILState_Release(
	 gil_state );
}

