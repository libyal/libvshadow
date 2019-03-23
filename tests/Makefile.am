AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBVSHADOW_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYVSHADOW = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_vshadowinfo.sh \
	$(TESTS_PYVSHADOW)

check_SCRIPTS = \
	pyvshadow_test_read.py \
	pyvshadow_test_support.py \
	pyvshadow_test_volume.py \
	test_library.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh \
	test_vshadowinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vshadow_test_block \
	vshadow_test_block_descriptor \
	vshadow_test_block_range_descriptor \
	vshadow_test_block_tree \
	vshadow_test_error \
	vshadow_test_io_handle \
	vshadow_test_notify \
	vshadow_test_store \
	vshadow_test_store_block \
	vshadow_test_store_descriptor \
	vshadow_test_support \
	vshadow_test_volume

vshadow_test_block_SOURCES = \
	vshadow_test_block.c \
	vshadow_test_libcerror.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_memory.c vshadow_test_memory.h \
	vshadow_test_unused.h

vshadow_test_block_LDADD = \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@

vshadow_test_block_descriptor_SOURCES = \
	vshadow_test_block_descriptor.c \
	vshadow_test_libcerror.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_memory.c vshadow_test_memory.h \
	vshadow_test_unused.h

vshadow_test_block_descriptor_LDADD = \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@

vshadow_test_block_range_descriptor_SOURCES = \
	vshadow_test_block_range_descriptor.c \
	vshadow_test_libcerror.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_memory.c vshadow_test_memory.h \
	vshadow_test_unused.h

vshadow_test_block_range_descriptor_LDADD = \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@

vshadow_test_block_tree_SOURCES = \
	vshadow_test_block_tree.c \
	vshadow_test_libcdata.h \
	vshadow_test_libcerror.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_memory.c vshadow_test_memory.h \
	vshadow_test_unused.h

vshadow_test_block_tree_LDADD = \
	@LIBCDATA_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@

vshadow_test_error_SOURCES = \
	vshadow_test_error.c \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_unused.h

vshadow_test_error_LDADD = \
	../libvshadow/libvshadow.la

vshadow_test_io_handle_SOURCES = \
	vshadow_test_io_handle.c \
	vshadow_test_libcerror.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_memory.c vshadow_test_memory.h \
	vshadow_test_unused.h

vshadow_test_io_handle_LDADD = \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@

vshadow_test_notify_SOURCES = \
	vshadow_test_libcerror.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_notify.c \
	vshadow_test_unused.h

vshadow_test_notify_LDADD = \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@

vshadow_test_store_SOURCES = \
	vshadow_test_libcerror.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_memory.c vshadow_test_memory.h \
	vshadow_test_store.c \
	vshadow_test_unused.h

vshadow_test_store_LDADD = \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@

vshadow_test_store_block_SOURCES = \
	vshadow_test_libbfio.h \
	vshadow_test_libcerror.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_memory.c vshadow_test_memory.h \
	vshadow_test_store_block.c \
	vshadow_test_unused.h

vshadow_test_store_block_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@

vshadow_test_store_descriptor_SOURCES = \
	vshadow_test_libcerror.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_memory.c vshadow_test_memory.h \
	vshadow_test_store_descriptor.c \
	vshadow_test_unused.h

vshadow_test_store_descriptor_LDADD = \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@

vshadow_test_support_SOURCES = \
	vshadow_test_functions.c vshadow_test_functions.h \
	vshadow_test_getopt.c vshadow_test_getopt.h \
	vshadow_test_libbfio.h \
	vshadow_test_libcerror.h \
	vshadow_test_libclocale.h \
	vshadow_test_libcnotify.h \
	vshadow_test_libuna.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_memory.c vshadow_test_memory.h \
	vshadow_test_support.c \
	vshadow_test_unused.h

vshadow_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@

vshadow_test_volume_SOURCES = \
	vshadow_test_functions.c vshadow_test_functions.h \
	vshadow_test_getopt.c vshadow_test_getopt.h \
	vshadow_test_libbfio.h \
	vshadow_test_libcerror.h \
	vshadow_test_libclocale.h \
	vshadow_test_libcnotify.h \
	vshadow_test_libuna.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_memory.c vshadow_test_memory.h \
	vshadow_test_unused.h \
	vshadow_test_volume.c

vshadow_test_volume_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

