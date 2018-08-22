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
	@LIBVSHADOW_DLL_EXPORT@

lib_LTLIBRARIES = libvshadow.la

libvshadow_la_SOURCES = \
	libvshadow.c \
	libvshadow_block.c libvshadow_block.h \
	libvshadow_block_descriptor.c libvshadow_block_descriptor.h \
	libvshadow_block_range_descriptor.c libvshadow_block_range_descriptor.h \
	libvshadow_block_tree.c libvshadow_block_tree.h \
	libvshadow_codepage.h \
	libvshadow_debug.c libvshadow_debug.h \
	libvshadow_definitions.h \
	libvshadow_error.c libvshadow_error.h \
	libvshadow_extern.h \
	libvshadow_io_handle.c libvshadow_io_handle.h \
	libvshadow_libbfio.h \
	libvshadow_libcdata.h \
	libvshadow_libcerror.h \
	libvshadow_libclocale.h \
	libvshadow_libcnotify.h \
	libvshadow_libcthreads.h \
	libvshadow_libfdata.h \
	libvshadow_libfdatetime.h \
	libvshadow_libfguid.h \
	libvshadow_libuna.h \
	libvshadow_notify.c libvshadow_notify.h \
	libvshadow_support.c libvshadow_support.h \
	libvshadow_store.c libvshadow_store.h \
	libvshadow_store_block.c libvshadow_store_block.h \
	libvshadow_store_descriptor.c libvshadow_store_descriptor.h \
	libvshadow_types.h \
	libvshadow_unused.h \
	libvshadow_volume.c libvshadow_volume.h \
	vshadow_catalog.h \
	vshadow_store.h \
	vshadow_volume.h

libvshadow_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@PTHREAD_LIBADD@

libvshadow_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libvshadow_definitions.h.in \
	libvshadow.rc \
	libvshadow.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libvshadow_definitions.h
	/bin/rm -f libvshadow.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libvshadow ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libvshadow_la_SOURCES)

