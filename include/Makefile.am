include_HEADERS = \
	libvshadow.h

pkginclude_HEADERS = \
	libvshadow/codepage.h \
	libvshadow/definitions.h \
	libvshadow/error.h \
	libvshadow/extern.h \
	libvshadow/features.h \
	libvshadow/types.h

EXTRA_DIST = \
	libvshadow.h.in \
	libvshadow/definitions.h.in \
	libvshadow/features.h.in \
	libvshadow/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libvshadow.h
	-rm -f libvshadow/definitions.h
	-rm -f libvshadow/features.h
	-rm -f libvshadow/types.h
	-rm -f Makefile

