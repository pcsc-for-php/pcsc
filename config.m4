dnl $Id$
dnl config.m4 for PC/SC extension

PHP_ARG_ENABLE(pcsc, PC/SC Smart Card support for PHP,
[  --enable-pcsc          Enable PC/SC Smart Card support])

dnl Check whether the extension is enabled at all
if test "$PHP_PCSC" != "no"; then
  if test -r $PHP_PCSC/include/PCSC/winscard.h; then
    PCSC_DIR=$PHP_PCSC
  else
    AC_MSG_CHECKING(for PC/SC in default path)
    for i in /usr/local /usr; do
      if test -r $i/include/PCSC/winscard.h; then
        PCSC_DIR=$i
        AC_MSG_RESULT(found in $i)
        break
      fi
    done
  fi

  if test -z "$PCSC_DIR"; then
    AC_MSG_RESULT(not found)
    AC_MSG_ERROR(Please reinstall the pcsc-lite distribution -
    winscard.h should be in <pcsc-dir>/include/PCSC/)
  fi
  AC_MSG_RESULT($PCSC_DIR)
  AC_MSG_RESULT($PCSC_DIR)
  AC_MSG_RESULT($PCSC_DIR)
  PHP_ADD_INCLUDE($PCSC_DIR/include/PCSC/)
  dnl PHP_EVAL_LIBLINE($PCSC_LIBS, PCSC_SHARED_LIBADD)
  PHP_ADD_LIBRARY_WITH_PATH(pcsclite, "$PCSC_DIR/lib/", PCSC_SHARED_LIBADD)
  
  dnl Finally, tell the build system about the extension and what files are needed
  PHP_NEW_EXTENSION(pcsc, pcsc.c, $ext_shared)
  PHP_INSTALL_HEADERS([php_pcsc.h])
  PHP_SUBST(PCSC_SHARED_LIBADD)
fi

