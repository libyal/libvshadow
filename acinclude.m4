dnl Function to detect if libvshadow dependencies are available
AC_DEFUN([AX_LIBVSHADOW_CHECK_LOCAL],
 [dnl Check for internationalization functions in libvshadow/libvshadow_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

