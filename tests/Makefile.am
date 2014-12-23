AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
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
	@PTHREAD_CPPFLAGS@ \
	@LIBVSHADOW_DLL_IMPORT@

if HAVE_PYTHON
TESTS_PYVSHADOW  = \
	test_pyvshadow_open_close.sh \
	test_pyvshadow_seek.sh
endif

TESTS = \
	test_open_close.sh \
	test_seek.sh \
	test_read.sh \
	test_vshadowinfo.sh \
	$(TESTS_PYVSHADOW)

check_SCRIPTS = \
	pyvshadow_test_open_close.py \
	pyvshadow_test_seek.py \
	test_open_close.sh \
	test_pyvshadow_open_close.sh \
	test_pyvshadow_seek.sh \
	test_read.sh \
	test_runner.sh \
	test_seek.sh \
	test_vshadowinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vshadow_test_open_close \
	vshadow_test_read \
	vshadow_test_seek

vshadow_test_open_close_SOURCES = \
	vshadow_test_libcerror.h \
	vshadow_test_libcstring.h \
	vshadow_test_libvshadow.h \
	vshadow_test_open_close.c \
	vshadow_test_unused.h

vshadow_test_open_close_LDADD = \
	../libvshadow/libvshadow.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

vshadow_test_read_SOURCES = \
	vshadow_test_libcerror.h \
	vshadow_test_libcstring.h \
	vshadow_test_libcthreads.h \
	vshadow_test_libvshadow.h \
	vshadow_test_read.c \
	vshadow_test_unused.h

vshadow_test_read_LDADD = \
	../libvshadow/libvshadow.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

vshadow_test_seek_SOURCES = \
	vshadow_test_libcerror.h \
	vshadow_test_libcstring.h \
	vshadow_test_libvshadow.h \
	vshadow_test_seek.c \
	vshadow_test_unused.h

vshadow_test_seek_LDADD = \
	../libvshadow/libvshadow.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

