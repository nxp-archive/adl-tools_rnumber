dnl check for zlib.
dnl TJD_PATH_ZLIB ( path, action-if-found, action-if-not-found )
dnl if no path is given this macro looks in /usr/lib then /usr/local/lib
dnl this sets ZLIB_CFLAGS, and ZLIB_LIBS
AC_DEFUN([TJD_PATH_ZLIB],
[dnl
if test x$1 = x; then
  ac_zlib_std="yes"
  ac_zlib_prefix=/usr
else
  ac_zlib_std="no"
  ac_zlib_prefix=$1
fi

ac_zlib_include=$ac_zlib_prefix/include
ac_zlib_lib=$ac_zlib_prefix/lib

AC_MSG_CHECKING([will look in $ac_zlib_include for zlib header file
         will look in $ac_zlib_lib for zlib library (libz.so, libz.a) ])

# look first in /usr/include, if zlib.h is not found there
# look in /usr/local/include. When looking for the library,
# you have to only look where the header was first found
if [ test -f $ac_zlib_include/zlib.h ] ; then
  AC_MSG_RESULT([found $ac_zlib_include/zlib.h])
else
  if test x$ac_zlib_std = "xyes"; then
    AC_MSG_RESULT([zlib.h not found in $ac_zlib_include, will try /usr/local/include])
    ac_zlib_prefix=/usr/local
    ac_zlib_include=$ac_zlib_prefix/include
    ac_zlib_lib=$ac_zlib_prefix/lib
    if [ test -f $ac_zlib_include/zlib.h ] ; then
      AC_MSG_RESULT([found $ac_zlib_include/zlib.h])
    else
      AC_MSG_ERROR([zlib.h is not in $ac_zlib_include])
    fi
  else	
    AC_MSG_ERROR([zlib.h is not in $ac_zlib_include])
  fi
fi

if [ test -f $ac_zlib_lib/libz.so ] ; then
  AC_MSG_RESULT(found $ac_zlib_lib/libz.so )
  ZLIB_EXT="so"
else
  if [ test -f $ac_zlib_lib/libz.a ] ; then
    AC_MSG_RESULT(found $ac_zlib_lib/libz.a )
    ZLIB_EXT="a"
  else
    AC_MSG_ERROR([libz.so nor libz.a is not in $ac_zlib_lib])
  fi
fi

ZLIB_CFLAGS="-I $ac_zlib_include"
ZLIB_LIBS="$ac_zlib_lib/libz.$ZLIB_EXT"

ac_save_CXXFLAGS="$CXXFLAGS"
ac_save_LIBS="$LIBS"
CXXFLAGS=$ZLIB_CFLAGS
LIBS=$ZLIB_LIBS
AC_MSG_CHECKING(looking for zlib)
AC_TRY_RUN([

#include <stdio.h>
#include <zlib.h>
#include <string.h>
int
main ()
{
  const char * version;
  int n;

  version = zlibVersion();
  n = strcmp ( version, ZLIB_VERSION );
  if ( n != 0 )
    {
     printf ( "Error: library and header do no match.\n", n);
     printf ( "zlib library version from header '%s'\n", ZLIB_VERSION );
     printf ( "zlib library version from lib '%s'\n", version );
      return 1;
    }
  return 0;
}

],dnl action if true
  AC_MSG_RESULT([found])
,dnl action if false
[dnl
echo ""
echo "zlib was not found. If you have it installed in a non-standard place"
echo "(ie. not /usr/local) then you should use the --with-zlib=<path> option"
echo "to configure, where <path> is the root directory of the zlib"
echo "installation. libz.so should be in <path>/lib and zlib.h should be in"
echo "<path>/include."
echo ""
echo "If you do not have zlib. You will have to download and install it. It"
echo "can be found at"
echo "ftp://ftp.freesoftware.com/pub/infozip/zlib/zlib.tar.gz"
echo ""
AC_MSG_ERROR(zlib could not be found)
],
AC_MSG_ERROR([cross compiling not supported])
) dnl end AC_TRY_RUN checking for zlib

CXXFLAGS=$ac_save_CXXFLAGS
LIBS=$ac_save_LIBS
])
