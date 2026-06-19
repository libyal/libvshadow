AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_SCRIPTS = \
	pyvshadow_test_store.py \
	pyvshadow_test_support.py \
	pyvshadow_test_volume.py

check_PROGRAMS = \
	vshadow_test_block \
	vshadow_test_block_descriptor \
	vshadow_test_block_range_descriptor \
	vshadow_test_block_tree \
	vshadow_test_block_tree_node \
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

vshadow_test_block_tree_node_SOURCES = \
	vshadow_test_block_tree_node.c \
	vshadow_test_libcerror.h \
	vshadow_test_libvshadow.h \
	vshadow_test_macros.h \
	vshadow_test_memory.c vshadow_test_memory.h \
	vshadow_test_unused.h

vshadow_test_block_tree_node_LDADD = \
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
	vshadow_test_store.c \
	vshadow_test_unused.h

vshadow_test_store_LDADD = \
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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libvshadow.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libvshadow

test_inputs_pyvshadow.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) pyvshadow

test_inputs_vshadowinfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) vshadowinfo

test_library: \
	package.m4 \
	test_inputs_libvshadow.at \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_python_module: \
	package.m4 \
	test_inputs_pyvshadow.at \
	test_python_module.at

test_tools: \
	package.m4 \
	test_inputs_vshadowinfo.at \
	test_macros.at \
	test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(check_SCRIPTS) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

