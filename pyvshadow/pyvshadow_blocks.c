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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvshadow_block.h"
#include "pyvshadow_blocks.h"
#include "pyvshadow_libcerror.h"
#include "pyvshadow_libvshadow.h"
#include "pyvshadow_python.h"
#include "pyvshadow_store.h"

PySequenceMethods pyvshadow_blocks_sequence_methods = {
	/* sq_length */
	(lenfunc) pyvshadow_blocks_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyvshadow_blocks_getitem,
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

PyTypeObject pyvshadow_blocks_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvshadow._blocks",
	/* tp_basicsize */
	sizeof( pyvshadow_blocks_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvshadow_blocks_free,
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
	&pyvshadow_blocks_sequence_methods,
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
	"internal pyvshadow blocks sequence and iterator object",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyvshadow_blocks_iter,
	/* tp_iternext */
	(iternextfunc) pyvshadow_blocks_iternext,
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
	(initproc) pyvshadow_blocks_init,
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

/* Creates a new blocks object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvshadow_blocks_new(
           pyvshadow_store_t *store_object,
           PyObject* (*get_block_by_index)(
                        pyvshadow_store_t *store_object,
                        int block_index ),
           int number_of_blocks )
{
	pyvshadow_blocks_t *pyvshadow_blocks = NULL;
	static char *function                = "pyvshadow_blocks_new";

	if( store_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid store object.",
		 function );

		return( NULL );
	}
	if( get_block_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get block by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the blocks values are initialized
	 */
	pyvshadow_blocks = PyObject_New(
	                    struct pyvshadow_blocks,
	                    &pyvshadow_blocks_type_object );

	if( pyvshadow_blocks == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize blocks.",
		 function );

		goto on_error;
	}
	if( pyvshadow_blocks_init(
	     pyvshadow_blocks ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize blocks.",
		 function );

		goto on_error;
	}
	pyvshadow_blocks->store_object       = store_object;
	pyvshadow_blocks->get_block_by_index = get_block_by_index;
	pyvshadow_blocks->number_of_blocks   = number_of_blocks;

	Py_IncRef(
	 (PyObject *) pyvshadow_blocks->store_object );

	return( (PyObject *) pyvshadow_blocks );

on_error:
	if( pyvshadow_blocks != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvshadow_blocks );
	}
	return( NULL );
}

/* Intializes a blocks object
 * Returns 0 if successful or -1 on error
 */
int pyvshadow_blocks_init(
     pyvshadow_blocks_t *pyvshadow_blocks )
{
	static char *function = "pyvshadow_blocks_init";

	if( pyvshadow_blocks == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid blocks.",
		 function );

		return( -1 );
	}
	/* Make sure the blocks values are initialized
	 */
	pyvshadow_blocks->store_object       = NULL;
	pyvshadow_blocks->get_block_by_index = NULL;
	pyvshadow_blocks->block_index        = 0;
	pyvshadow_blocks->number_of_blocks   = 0;

	return( 0 );
}

/* Frees a blocks object
 */
void pyvshadow_blocks_free(
      pyvshadow_blocks_t *pyvshadow_blocks )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvshadow_blocks_free";

	if( pyvshadow_blocks == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid blocks.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvshadow_blocks );

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
	if( pyvshadow_blocks->store_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvshadow_blocks->store_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvshadow_blocks );
}

/* The blocks len() function
 */
Py_ssize_t pyvshadow_blocks_len(
            pyvshadow_blocks_t *pyvshadow_blocks )
{
	static char *function = "pyvshadow_blocks_len";

	if( pyvshadow_blocks == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid blocks.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pyvshadow_blocks->number_of_blocks );
}

/* The blocks getitem() function
 */
PyObject *pyvshadow_blocks_getitem(
           pyvshadow_blocks_t *pyvshadow_blocks,
           Py_ssize_t item_index )
{
	PyObject *block_object = NULL;
	static char *function  = "pyvshadow_blocks_getitem";

	if( pyvshadow_blocks == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid blocks.",
		 function );

		return( NULL );
	}
	if( pyvshadow_blocks->get_block_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid blocks - missing get block by index function.",
		 function );

		return( NULL );
	}
	if( pyvshadow_blocks->number_of_blocks < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid blocks - invalid number of blocks.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pyvshadow_blocks->number_of_blocks ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	block_object = pyvshadow_blocks->get_block_by_index(
	                pyvshadow_blocks->store_object,
	                (int) item_index );

	return( block_object );
}

/* The blocks iter() function
 */
PyObject *pyvshadow_blocks_iter(
           pyvshadow_blocks_t *pyvshadow_blocks )
{
	static char *function = "pyvshadow_blocks_iter";

	if( pyvshadow_blocks == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid blocks.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pyvshadow_blocks );

	return( (PyObject *) pyvshadow_blocks );
}

/* The blocks iternext() function
 */
PyObject *pyvshadow_blocks_iternext(
           pyvshadow_blocks_t *pyvshadow_blocks )
{
	PyObject *block_object = NULL;
	static char *function  = "pyvshadow_blocks_iternext";

	if( pyvshadow_blocks == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid blocks.",
		 function );

		return( NULL );
	}
	if( pyvshadow_blocks->get_block_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid blocks - missing get block by index function.",
		 function );

		return( NULL );
	}
	if( pyvshadow_blocks->block_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid blocks - invalid block index.",
		 function );

		return( NULL );
	}
	if( pyvshadow_blocks->number_of_blocks < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid blocks - invalid number of blocks.",
		 function );

		return( NULL );
	}
	if( pyvshadow_blocks->block_index >= pyvshadow_blocks->number_of_blocks )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	block_object = pyvshadow_blocks->get_block_by_index(
	                pyvshadow_blocks->store_object,
	                pyvshadow_blocks->block_index );

	if( block_object != NULL )
	{
		pyvshadow_blocks->block_index++;
	}
	return( block_object );
}

