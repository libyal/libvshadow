MSVSCPP_FILES = \
	dokan_dll/dokan_dll.vcproj \
	libbfio/libbfio.vcproj \
	libcdata/libcdata.vcproj \
	libcerror/libcerror.vcproj \
	libcfile/libcfile.vcproj \
	libclocale/libclocale.vcproj \
	libcnotify/libcnotify.vcproj \
	libcpath/libcpath.vcproj \
	libcsplit/libcsplit.vcproj \
	libcstring/libcstring.vcproj \
	libcsystem/libcsystem.vcproj \
	libcthreads/libcthreads.vcproj \
	libfdatetime/libfdatetime.vcproj \
	libfguid/libfguid.vcproj \
	libuna/libuna.vcproj \
	libvshadow_dll/libvshadow_dll.vcproj \
	pyvshadow/pyvshadow.vcproj \
	vshadow_test_read/vshadow_test_read.vcproj \
	vshadow_test_seek/vshadow_test_seek.vcproj \
	vshadowinfo/vshadowinfo.vcproj \
	vshadowmount/vshadowmount.vcproj \
	libvshadow.sln

SCRIPT_FILES = \
	scripts/vs2008_x64.sh \
	scripts/vs2008_x64_sln.sed \
	scripts/vs2008_x64_vcproj.sed \
	scripts/vs2010_x64.sh \
	scripts/vs2010_x64_sln.sed \
	scripts/vs2010_x64_vcxproj.sed

EXTRA_DIST = \
	$(MSVSCPP_FILES) \
	$(SCRIPT_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

