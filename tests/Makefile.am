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
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBVSHADOW_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYVSHADOW = \
	test_python_functions.sh
endif

TESTS = \
	test_api_functions.sh \
	test_vshadowinfo.sh \
	$(TESTS_PYVSHADOW)

check_SCRIPTS = \
	pyvshadow_test_get_version.py \
	pyvshadow_test_open_close.py \
	pyvshadow_test_read.py \
	pyvshadow_test_seek.py \
	test_api_functions.sh \
	test_python_functions.sh \
	test_runner.sh \
	test_vshadowinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vshadow_test_error \
	vshadow_test_notify \
	vshadow_test_open_close \
	vshadow_test_read \
	vshadow_test_seek \
	vshadow_test_support

vshadow_test_error_SOURCES = \
	vshadow_test_error.c \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_unused.h

vshadow_test_error_LDADD = \
	../libvshadow/libvshadow.la

vshadow_test_notify_SOURCES = \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_notify.c \
	vshadow_test_unused.h

vshadow_test_notify_LDADD = \
	../libvshadow/libvshadow.la

vshadow_test_open_close_SOURCES = \
	vshadow_test_libcerror.h \
	vshadow_test_libcsystem.h \
	vshadow_test_libvshadow.h \
	vshadow_test_open_close.c \
	vshadow_test_unused.h

vshadow_test_open_close_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@
	@PTHREAD_LIBADD@

vshadow_test_read_SOURCES = \
	vshadow_test_libcerror.h \
	vshadow_test_libcthreads.h \
	vshadow_test_libcsystem.h \
	vshadow_test_libvshadow.h \
	vshadow_test_read.c \
	vshadow_test_unused.h

vshadow_test_read_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@
	@PTHREAD_LIBADD@

vshadow_test_seek_SOURCES = \
	vshadow_test_libcerror.h \
	vshadow_test_libcsystem.h \
	vshadow_test_libvshadow.h \
	vshadow_test_seek.c \
	vshadow_test_unused.h

vshadow_test_seek_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@
	@PTHREAD_LIBADD@

vshadow_test_support_SOURCES = \
	vshadow_test_libcerror.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_support.c \
	vshadow_test_unused.h

vshadow_test_support_LDADD = \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

