# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir2)"
pyexecdir = $(pyexecdir2)

if HAVE_PYTHON2
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBVSHADOW_DLL_IMPORT@

am_pyvshadow_la_rpath = -rpath $(pyexecdir2)

BUILT_SOURCES = \
	pyvshadow.c pyvshadow.h \
	pyvshadow_block.c pyvshadow_block.h \
	pyvshadow_block_flags.c pyvshadow_block_flags.h \
	pyvshadow_blocks.c pyvshadow_blocks.h \
	pyvshadow_datetime.c pyvshadow_datetime.h \
	pyvshadow_error.c pyvshadow_error.h \
	pyvshadow_file_object_io_handle.c pyvshadow_file_object_io_handle.h \
	pyvshadow_guid.c pyvshadow_guid.h \
	pyvshadow_integer.c pyvshadow_integer.h \
	pyvshadow_libbfio.h \
	pyvshadow_libcerror.h \
	pyvshadow_libclocale.h \
	pyvshadow_libfguid.h \
	pyvshadow_libvshadow.h \
	pyvshadow_python.h \
	pyvshadow_store.c pyvshadow_store.h \
	pyvshadow_stores.c pyvshadow_stores.h \
	pyvshadow_unused.h \
	pyvshadow_volume.c pyvshadow_volume.h

pyexec_LTLIBRARIES = pyvshadow.la

nodist_pyvshadow_la_SOURCES = $(BUILT_SOURCES)

pyvshadow_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFGUID_LIBADD@

pyvshadow_la_CPPFLAGS = $(PYTHON2_CPPFLAGS)
pyvshadow_la_LDFLAGS  = -module -avoid-version $(PYTHON2_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyvshadow/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyvshadow*.[ch]

distclean: clean
	/bin/rm -f Makefile

