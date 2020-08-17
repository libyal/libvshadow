/*
 * Python object definition of the libvshadow store
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
#include "pyvshadow_blocks.h"
#include "pyvshadow_datetime.h"
#include "pyvshadow_error.h"
#include "pyvshadow_guid.h"
#include "pyvshadow_integer.h"
#include "pyvshadow_libcerror.h"
#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"
#include "pyvshadow_store.h"
#include "pyvshadow_unused.h"
#include "pyvshadow_volume.h"

PyMethodDef pyvshadow_store_object_methods[] = {

	/* Functions to access the store data */

	{ "has_in_volume_data",
	  (PyCFunction) pyvshadow_store_has_in_volume_data,
	  METH_NOARGS,
	  "has_in_volume_data() -> Boolean\n"
	  "\n"
	  "Determines if the store as in-volume data." },

	{ "read_buffer",
	  (PyCFunction) pyvshadow_store_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_buffer(size) -> String\n"
	  "\n"
	  "Reads a buffer of store data." },

	{ "read_buffer_at_offset",
	  (PyCFunction) pyvshadow_store_read_buffer_at_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_buffer_at_offset(size, offset) -> String\n"
	  "\n"
	  "Reads a buffer of store data at a specific offset." },

	{ "seek_offset",
	  (PyCFunction) pyvshadow_store_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek_offset(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the store data." },

	{ "get_offset",
	  (PyCFunction) pyvshadow_store_get_offset,
	  METH_NOARGS,
	  "get_offset() -> Integer\n"
	  "\n"
	  "Retrieves the current offset within the store data." },

	/* Some Pythonesque aliases */

	{ "read",
	  (PyCFunction) pyvshadow_store_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read(size) -> String\n"
	  "\n"
	  "Reads a buffer of store data." },

	{ "seek",
	  (PyCFunction) pyvshadow_store_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the store data." },

	{ "tell",
	  (PyCFunction) pyvshadow_store_get_offset,
	  METH_NOARGS,
	  "tell() -> Integer\n"
	  "\n"
	  "Retrieves the current offset within the store data." },

	/* Functions to access the store values */

	{ "get_size",
	  (PyCFunction) pyvshadow_store_get_size,
	  METH_NOARGS,
	  "get_size() -> Integer\n"
	  "\n"
	  "Retrieves the size of the store data." },

	{ "get_volume_size",
	  (PyCFunction) pyvshadow_store_get_volume_size,
	  METH_NOARGS,
	  "get_volume_size() -> Integer\n"
	  "\n"
	  "Retrieves the size of the volume as stored in the store information." },

	{ "get_identifier",
	  (PyCFunction) pyvshadow_store_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the identifier (GUID)." },

	{ "get_creation_time",
	  (PyCFunction) pyvshadow_store_get_creation_time,
	  METH_NOARGS,
	  "get_creation_time() -> Datetime\n"
	  "\n"
	  "Returns the creation date and time." },

	{ "get_creation_time_as_integer",
	  (PyCFunction) pyvshadow_store_get_creation_time_as_integer,
	  METH_NOARGS,
	  "pyvshadow_store_get_creation_time_as_integer() -> Integer\n"
	  "\n"
	  "Returns the creation date and time as a 64-bit integer containing a FILETIME value." },

	{ "get_copy_identifier",
	  (PyCFunction) pyvshadow_store_get_copy_identifier,
	  METH_NOARGS,
	  "get_copy_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the copy identifier (GUID)." },

	{ "get_copy_set_identifier",
	  (PyCFunction) pyvshadow_store_get_copy_set_identifier,
	  METH_NOARGS,
	  "get_copy_set_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the copy set identifier (GUID)." },

	/* Functions to access the blocks */

	{ "get_number_of_blocks",
	  (PyCFunction) pyvshadow_store_get_number_of_blocks,
	  METH_NOARGS,
	  "get_number_of_blocks() -> Integer\n"
	  "\n"
	  "Retrieves the number of blocks." },

	{ "get_block",
	  (PyCFunction) pyvshadow_store_get_block,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_block(block_index) -> Object or None\n"
	  "\n"
	  "Retrieves a specific block." },

	{ "get_blocks",
	  (PyCFunction) pyvshadow_store_get_blocks,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_blocks() -> Object\n"
	  "\n"
	  "Retrieves a sequence object of the blocks." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvshadow_store_object_get_set_definitions[] = {

	{ "size",
	  (getter) pyvshadow_store_get_size,
	  (setter) 0,
	  "The size.",
	  NULL },

	{ "volume_size",
	  (getter) pyvshadow_store_get_volume_size,
	  (setter) 0,
	  "The volume size.",
	  NULL },

	{ "identifier",
	  (getter) pyvshadow_store_get_identifier,
	  (setter) 0,
	  "The identifier.",
	  NULL },

	{ "creation_time",
	  (getter) pyvshadow_store_get_creation_time,
	  (setter) 0,
	  "The creation date and time.",
	  NULL },

	{ "copy_identifier",
	  (getter) pyvshadow_store_get_copy_identifier,
	  (setter) 0,
	  "The copy identifier.",
	  NULL },

	{ "copy_set_identifier",
	  (getter) pyvshadow_store_get_copy_set_identifier,
	  (setter) 0,
	  "The copy set identifier.",
	  NULL },

	{ "number_of_blocks",
	  (getter) pyvshadow_store_get_number_of_blocks,
	  (setter) 0,
	  "The number of blocks.",
	  NULL },

	{ "blocks",
	  (getter) pyvshadow_store_get_blocks,
	  (setter) 0,
	  "The blocks.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyvshadow_store_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvshadow.store",
	/* tp_basicsize */
	sizeof( pyvshadow_store_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvshadow_store_free,
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
	"pyvshadow store object (wraps libvshadow_store_t)",
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
	pyvshadow_store_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyvshadow_store_object_get_set_definitions,
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
	(initproc) pyvshadow_store_init,
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

/* Creates a new store object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_new(
           libvshadow_store_t *store,
           PyObject *parent_object )
{
	pyvshadow_store_t *pyvshadow_store = NULL;
	static char *function              = "pyvshadow_store_new";

	if( store == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyvshadow_store = PyObject_New(
	                   struct pyvshadow_store,
	                   &pyvshadow_store_type_object );

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize store.",
		 function );

		goto on_error;
	}
	pyvshadow_store->store         = store;
	pyvshadow_store->parent_object = parent_object;

	if( pyvshadow_store->parent_object != NULL )
	{
		Py_IncRef(
		 pyvshadow_store->parent_object );
	}
	return( (PyObject *) pyvshadow_store );

on_error:
	if( pyvshadow_store != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvshadow_store );
	}
	return( NULL );
}

/* Initializes a store object
 * Returns 0 if successful or -1 on error
 */
int pyvshadow_store_init(
     pyvshadow_store_t *pyvshadow_store )
{
	static char *function = "pyvshadow_store_init";

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	/* Make sure libvshadow store is set to NULL
	 */
	pyvshadow_store->store = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of store not supported.",
	 function );

	return( -1 );
}

/* Frees a store object
 */
void pyvshadow_store_free(
      pyvshadow_store_t *pyvshadow_store )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvshadow_store_free";
	int result                  = 0;

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid store.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvshadow_store );

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
	if( pyvshadow_store->store != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libvshadow_store_free(
		          &( pyvshadow_store->store ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvshadow_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libvshadow store.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyvshadow_store->parent_object != NULL )
	{
		Py_DecRef(
		 pyvshadow_store->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvshadow_store );
}

/* Determines if the store has in-volume data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_has_in_volume_data(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyvshadow_store_has_in_volume_data";
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_store_has_in_volume_data(
	          pyvshadow_store->store,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine if the store has in-volume data.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 (PyObject *) Py_False );

		return( Py_False );
	}
	Py_IncRef(
	 (PyObject *) Py_True );

	return( Py_True );
}

/* Reads (store) data at the current offset into a buffer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_read_buffer(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	PyObject *string_object     = NULL;
	static char *function       = "pyvshadow_store_read_buffer";
	static char *keyword_list[] = { "size", NULL };
	char *buffer                = NULL;
	ssize_t read_count          = 0;
	int read_size               = -1;

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyvshadow store.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|i",
	     keyword_list,
	     &read_size ) == 0 )
	{
		return( NULL );
	}
	if( read_size < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into the memory buffer
	 */
	if( read_size > INT_MAX )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
	                 NULL,
	                 read_size );

	buffer = PyBytes_AsString(
	          string_object );
#else
	string_object = PyString_FromStringAndSize(
	                 NULL,
	                 read_size );

	buffer = PyString_AsString(
	          string_object );
#endif
	Py_BEGIN_ALLOW_THREADS

	read_count = libvshadow_store_read_buffer(
	              pyvshadow_store->store,
	              (uint8_t *) buffer,
	              (size_t) read_size,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count <= -1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to read data.",
		 function );

		libcerror_error_free(
		 &error );

		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	/* Need to resize the string here in case read_size was not fully read.
	 */
#if PY_MAJOR_VERSION >= 3
	if( _PyBytes_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#else
	if( _PyString_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#endif
	{
		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	return( string_object );
}

/* Reads (store) data at a specific offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_read_buffer_at_offset(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	PyObject *string_object     = NULL;
	static char *function       = "pyvshadow_store_read_buffer_at_offset";
	static char *keyword_list[] = { "size", "offset", NULL };
	char *buffer                = NULL;
	off64_t read_offset         = 0;
	ssize_t read_count          = 0;
	int read_size               = 0;

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyvshadow store.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i|L",
	     keyword_list,
	     &read_size,
	     &read_offset ) == 0 )
	{
		return( NULL );
	}
	if( read_size < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into the memory buffer
	 */
	if( read_size > INT_MAX )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
	if( read_offset < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read offset value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into the memory buffer
	 */
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
	                 NULL,
	                 read_size );

	buffer = PyBytes_AsString(
	          string_object );
#else
	string_object = PyString_FromStringAndSize(
	                 NULL,
	                 read_size );

	buffer = PyString_AsString(
	          string_object );
#endif
	Py_BEGIN_ALLOW_THREADS

	read_count = libvshadow_store_read_buffer_at_offset(
	              pyvshadow_store->store,
	              (uint8_t *) buffer,
	              (size_t) read_size,
	              (off64_t) read_offset,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count <= -1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to read data.",
		 function );

		libcerror_error_free(
		 &error );

		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	/* Need to resize the string here in case read_size was not fully read.
	 */
#if PY_MAJOR_VERSION >= 3
	if( _PyBytes_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#else
	if( _PyString_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#endif
	{
		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	return( string_object );
}

/* Seeks a certain offset in the (store) data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_seek_offset(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvshadow_store_seek_offset";
	static char *keyword_list[] = { "offset", "whence", NULL };
	off64_t offset              = 0;
	int whence                  = 0;

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyvshadow store.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "L|i",
	     keyword_list,
	     &offset,
	     &whence ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	offset = libvshadow_store_seek_offset(
	          pyvshadow_store->store,
	          offset,
	          whence,
	          &error );

	Py_END_ALLOW_THREADS

 	if( offset == -1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to seek offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the current offset in the (store) data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_get_offset(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyvshadow_store_get_offset";
	off64_t current_offset   = 0;
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_store_get_offset(
	          pyvshadow_store->store,
	          &current_offset,
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
	                  (int64_t) current_offset );

	return( integer_object );
}

/* Retrieves the size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_get_size(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyvshadow_store_get_size";
	size64_t size            = 0;
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_store_get_size(
	          pyvshadow_store->store,
	          &size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: failed to retrieve size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pyvshadow_integer_unsigned_new_from_64bit(
	                  (uint64_t) size );

	return( integer_object );
}

/* Retrieves the volume size as stored in the store information
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_get_volume_size(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyvshadow_store_get_volume_size";
	size64_t volume_size     = 0;
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_store_get_volume_size(
	          pyvshadow_store->store,
	          &volume_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: failed to retrieve volume size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pyvshadow_integer_unsigned_new_from_64bit(
	                  (uint64_t) volume_size );

	return( integer_object );
}

/* Retrieves the identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_get_identifier(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pyvshadow_store_get_identifier";
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_store_get_identifier(
	          pyvshadow_store->store,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	string_object = pyvshadow_string_new_from_guid(
			 guid_data,
			 16 );

	return( string_object );
}

/* Retrieves the creation date and time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_get_creation_time(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error   = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pyvshadow_store_get_creation_time";
	uint64_t filetime          = 0;
	int result                 = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_store_get_creation_time(
	          pyvshadow_store->store,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve creation time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	date_time_object = pyvshadow_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the creation date and time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_get_creation_time_as_integer(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyvshadow_store_get_creation_time_as_integer";
	uint64_t filetime        = 0;
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_store_get_creation_time(
	          pyvshadow_store->store,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve creation time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pyvshadow_integer_unsigned_new_from_64bit(
	                  (uint64_t) filetime );

	return( integer_object );
}

/* Retrieves the copy identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_get_copy_identifier(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pyvshadow_store_get_copy_identifier";
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_store_get_copy_identifier(
	          pyvshadow_store->store,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve copy identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	string_object = pyvshadow_string_new_from_guid(
			 guid_data,
			 16 );

	return( string_object );
}

/* Retrieves the copy set identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_get_copy_set_identifier(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pyvshadow_store_get_copy_set_identifier";
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_store_get_copy_set_identifier(
	          pyvshadow_store->store,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve copy set identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	string_object = pyvshadow_string_new_from_guid(
			 guid_data,
			 16 );

	return( string_object );
}

/* Retrieves the number of blocks
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_get_number_of_blocks(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyvshadow_store_get_number_of_blocks";
	int number_of_blocks     = 0;
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_store_get_number_of_blocks(
	          pyvshadow_store->store,
	          &number_of_blocks,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of blocks.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_blocks );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_blocks );
#endif
	return( integer_object );
}

/* Retrieves a specific block by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_get_block_by_index(
           PyObject *pyvshadow_store,
           int block_index )
{
	libcerror_error_t *error  = NULL;
	libvshadow_block_t *block = NULL;
	PyObject *block_object    = NULL;
	static char *function     = "pyvshadow_store_get_block_by_index";
	int result                = 0;

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_store_get_block_by_index(
	          ( (pyvshadow_store_t *) pyvshadow_store )->store,
	          block_index,
	          &block,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve block: %d.",
		 function,
		 block_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	block_object = pyvshadow_block_new(
	                block,
	                pyvshadow_store );

	if( block_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create block object.",
		 function );

		goto on_error;
	}
	return( block_object );

on_error:
	if( block != NULL )
	{
		libvshadow_block_free(
		 &block,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific block
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_get_block(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *block_object      = NULL;
	static char *keyword_list[] = { "block_index", NULL };
	int block_index             = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &block_index ) == 0 )
	{
		return( NULL );
	}
	block_object = pyvshadow_store_get_block_by_index(
	                (PyObject *) pyvshadow_store,
	                block_index );

	return( block_object );
}

/* Retrieves a blocks sequence and iterator object for the blocks
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_store_get_blocks(
           pyvshadow_store_t *pyvshadow_store,
           PyObject *arguments PYVSHADOW_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *blocks_object  = NULL;
	static char *function    = "pyvshadow_store_get_blocks";
	int number_of_blocks     = 0;
	int result               = 0;

	PYVSHADOW_UNREFERENCED_PARAMETER( arguments )

	if( pyvshadow_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvshadow_store_get_number_of_blocks(
	          pyvshadow_store->store,
	          &number_of_blocks,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvshadow_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of blocks.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	blocks_object = pyvshadow_blocks_new(
	                 (PyObject *) pyvshadow_store,
	                 &pyvshadow_store_get_block_by_index,
	                 number_of_blocks );

	if( blocks_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create blocks object.",
		 function );

		return( NULL );
	}
	return( blocks_object );
}

