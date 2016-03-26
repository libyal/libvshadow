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
	/bin/rm -f libvshadow.h
	/bin/rm -f libvshadow/definitions.h
	/bin/rm -f libvshadow/features.h
	/bin/rm -f libvshadow/types.h
	/bin/rm -f Makefile

