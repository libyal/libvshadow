dnl Checks for required headers and functions
dnl
dnl Version: 20200713

dnl Function to detect if libvshadow dependencies are available
AC_DEFUN([AX_LIBVSHADOW_CHECK_LOCAL],
  [dnl Check for internationalization functions in libvshadow/libvshadow_i18n.c
  AC_CHECK_FUNCS([bindtextdomain])
])

dnl Function to detect if vshadowtools dependencies are available
AC_DEFUN([AX_VSHADOWTOOLS_CHECK_LOCAL],
  [AC_CHECK_HEADERS([signal.h sys/signal.h unistd.h])

  AC_CHECK_FUNCS([close getopt setvbuf])

  AS_IF(
   [test "x$ac_cv_func_close" != xyes],
   [AC_MSG_FAILURE(
     [Missing function: close],
     [1])
  ])

  dnl Headers included in vshadowtools/vshadowmount.c
  AC_CHECK_HEADERS([errno.h])

  AC_HEADER_TIME

  dnl Functions included in vshadowtools/mount_file_system.c and vshadowtools/mount_file_entry.c
  AS_IF(
    [test "x$ac_cv_enable_winapi" = xno],
    [AC_CHECK_FUNCS([clock_gettime getegid geteuid time])
  ])
])

dnl Function to check if DLL support is needed
AC_DEFUN([AX_LIBVSHADOW_CHECK_DLL_SUPPORT],
  [AS_IF(
    [test "x$enable_shared" = xyes && test "x$ac_cv_enable_static_executables" = xno],
    [AS_CASE(
      [$host],
      [*cygwin* | *mingw* | *msys*],
      [AC_DEFINE(
        [HAVE_DLLMAIN],
        [1],
        [Define to 1 to enable the DllMain function.])
      AC_SUBST(
        [HAVE_DLLMAIN],
        [1])

      AC_SUBST(
        [LIBVSHADOW_DLL_EXPORT],
        ["-DLIBVSHADOW_DLL_EXPORT"])

      AC_SUBST(
        [LIBVSHADOW_DLL_IMPORT],
        ["-DLIBVSHADOW_DLL_IMPORT"])
      ])
    ])
  ])

