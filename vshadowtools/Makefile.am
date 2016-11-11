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
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBFUSE_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBVSHADOW_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	vshadowdebug \
	vshadowinfo \
	vshadowmount

vshadowdebug_SOURCES = \
	debug_handle.c debug_handle.h \
	vshadowdebug.c \
	vshadowoutput.c vshadowoutput.h \
	vshadowtools_libbfio.h \
	vshadowtools_libcerror.h \
	vshadowtools_libcfile.h \
	vshadowtools_libclocale.h \
	vshadowtools_libcnotify.h \
	vshadowtools_libcpath.h \
	vshadowtools_libcsystem.h \
	vshadowtools_libfdatetime.h \
	vshadowtools_libfguid.h \
	vshadowtools_libuna.h \
	vshadowtools_libvshadow.h

vshadowdebug_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

vshadowinfo_SOURCES = \
	byte_size_string.c byte_size_string.h \
	info_handle.c info_handle.h \
	vshadowinfo.c \
	vshadowoutput.c vshadowoutput.h \
	vshadowtools_libbfio.h \
	vshadowtools_libcerror.h \
	vshadowtools_libcfile.h \
	vshadowtools_libclocale.h \
	vshadowtools_libcnotify.h \
	vshadowtools_libcpath.h \
	vshadowtools_libcsystem.h \
	vshadowtools_libfdatetime.h \
	vshadowtools_libfguid.h \
	vshadowtools_libuna.h \
	vshadowtools_libvshadow.h

vshadowinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

vshadowmount_SOURCES = \
	mount_handle.c mount_handle.h \
	vshadowmount.c \
	vshadowoutput.c vshadowoutput.h \
	vshadowtools_libbfio.h \
	vshadowtools_libcerror.h \
	vshadowtools_libcfile.h \
	vshadowtools_libclocale.h \
	vshadowtools_libcnotify.h \
	vshadowtools_libcpath.h \
	vshadowtools_libcsystem.h \
	vshadowtools_libfdatetime.h \
	vshadowtools_libfguid.h \
	vshadowtools_libuna.h \
	vshadowtools_libvshadow.h

vshadowmount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBCSYSTEM_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on vshadowinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(vshadowinfo_SOURCES)
	@echo "Running splint on vshadowmount ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(vshadowmount_SOURCES)

