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
	vshadowtools_getopt.c vshadowtools_getopt.h \
	vshadowtools_i18n.h \
	vshadowtools_libbfio.h \
	vshadowtools_libcerror.h \
	vshadowtools_libcfile.h \
	vshadowtools_libclocale.h \
	vshadowtools_libcnotify.h \
	vshadowtools_libcpath.h \
	vshadowtools_libfdatetime.h \
	vshadowtools_libfguid.h \
	vshadowtools_libuna.h \
	vshadowtools_libvshadow.h \
	vshadowtools_output.c vshadowtools_output.h \
	vshadowtools_signal.c vshadowtools_signal.h \
	vshadowtools_unused.h

vshadowdebug_LDADD = \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

vshadowinfo_SOURCES = \
	byte_size_string.c byte_size_string.h \
	info_handle.c info_handle.h \
	vshadowinfo.c \
	vshadowtools_getopt.c vshadowtools_getopt.h \
	vshadowtools_i18n.h \
	vshadowtools_libbfio.h \
	vshadowtools_libcerror.h \
	vshadowtools_libcfile.h \
	vshadowtools_libclocale.h \
	vshadowtools_libcnotify.h \
	vshadowtools_libcpath.h \
	vshadowtools_libfdatetime.h \
	vshadowtools_libfguid.h \
	vshadowtools_libuna.h \
	vshadowtools_libvshadow.h \
	vshadowtools_output.c vshadowtools_output.h \
	vshadowtools_signal.c vshadowtools_signal.h \
	vshadowtools_unused.h

vshadowinfo_LDADD = \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libvshadow/libvshadow.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

vshadowmount_SOURCES = \
	mount_dokan.c mount_dokan.h \
	mount_file_entry.c mount_file_entry.h \
	mount_file_system.c mount_file_system.h \
	mount_fuse.c mount_fuse.h \
	mount_handle.c mount_handle.h \
	vshadowmount.c \
	vshadowtools_getopt.c vshadowtools_getopt.h \
	vshadowtools_i18n.h \
	vshadowtools_libbfio.h \
	vshadowtools_libcdata.h \
	vshadowtools_libcerror.h \
	vshadowtools_libcfile.h \
	vshadowtools_libclocale.h \
	vshadowtools_libcnotify.h \
	vshadowtools_libcpath.h \
	vshadowtools_libfdatetime.h \
	vshadowtools_libfguid.h \
	vshadowtools_libuna.h \
	vshadowtools_libvshadow.h \
	vshadowtools_output.c vshadowtools_output.h \
	vshadowtools_signal.c vshadowtools_signal.h \
	vshadowtools_unused.h

vshadowmount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libvshadow/libvshadow.la \
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

