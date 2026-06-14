#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libvshadow/.libs/libvshadow.1.dylib && test -f ./pyvshadow/.libs/pyvshadow.so
then
	install_name_tool -change /usr/local/lib/libvshadow.1.dylib ${PWD}/libvshadow/.libs/libvshadow.1.dylib ./pyvshadow/.libs/pyvshadow.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

