#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libvshadow/.libs/libvshadow.1.dylib && test -f ./pyvshadow/.libs/pyvshadow.so;
then
	install_name_tool -change /usr/local/lib/libvshadow.1.dylib ${PWD}/libvshadow/.libs/libvshadow.1.dylib ./pyvshadow/.libs/pyvshadow.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

