#!/bin/sh
MAKE=`which gnumake`
if test ! -x "$MAKE" ; then MAKE=`which gmake` ; fi
if test ! -x "$MAKE" ; then MAKE=`which make` ; fi
HAVE_GNU_MAKE=`$MAKE --version|grep -c "Free Software Foundation"`

if test "$HAVE_GNU_MAKE" != "1"; then 
echo !!!! ERROR: You need GNU make to build rnumber; 
echo !!!! $MAKE is not GNU make;
exit 1; 
fi

echo Found GNU Make at $MAKE ... good.
echo This script runs configure and make...
echo Put remember necessary arguments for configure on command line.

srcdir=`dirname $0`
echo "srcdir $srcdir"
test -z "$srcdir" && srcdir=.

PKG_NAME="rnumber"

(test -f $srcdir/configure.in \
  && test -d $srcdir/src \
  && test -f $srcdir/src/RNumber.C) || {
    echo -n "Error: Directory "\`$srcdir\'" does not look like the"
    echo " top-level $PKG_NAME directory"
    exit 1
}

# Run this to generate all the initial makefiles, etc.

(autoconf --version ) < /dev/null > /dev/null 2>&1 || {
  echo
  echo "Error: You must have \`autoconf'  installed to compile rnumber."
  echo "It is available at ftp://ftp.gnu.org/pub/gnu/"
  exit 1;
}

(grep "^AM_PROG_LIBTOOL" $srcdir/configure.in >/dev/null) && {
  (libtool --version) < /dev/null > /dev/null 2>&1 || {
    echo
    echo "Error: You must have \`libtool' installed to compile rnumber."
    echo "It is available at ftp://ftp.gnu.org/pub/gnu/"
    exit 1;
  }
}

(automake --version) < /dev/null > /dev/null 2>&1 || {
  echo
  echo "Error: You must have \`automake' installed to compile rnumber."
  echo "It is available at ftp://ftp.gnu.org/pub/gnu/automake-1.3.tar.gz"
  exit 1;
}

# if no automake, don't bother testing for aclocal
test -n "$NO_AUTOMAKE" || (aclocal --version) < /dev/null > /dev/null 2>&1 || {
  echo
  echo "Error: Missing \`aclocal'. Make sure you have \`automake'"
  echo "installed version 1.3 or later."
  echo "It is available at ftp://ftp.gnu.org/pub/gnu/automake-1.3.tar.gz"
  exit 1;
}

if test -z "$*"; then
  echo "autogen.sh: Running \`configure' with no arguments."
  echo "Arguments may be passed on the \`$0\` command line."
fi

case $CC in
    xlc )
	am_opt=--include-deps;;
esac

for configure_in in `find $srcdir -name configure.in -print`
do 
  directory=`dirname $configure_in`
  if test -f $directory/NO-AUTO-GEN; then
    echo skipping $directory -- flagged as no auto-gen
  else
    echo processing $directory
    macrodirs=`sed -n -e 's,AM_ACLOCAL_INCLUDE(\(.*\)),\1,gp' < $configure_in`
    ( cd $directory
      aclocalinclude="$ACLOCAL_FLAGS"
      for k in $macrodirs; do
  	if test -d $k; then
          aclocalinclude="$aclocalinclude -I $k"
  	else 
	  echo "Warning: No such directory \`$k'.  Ignored."
        fi
      done
      if grep "^AM_PROG_LIBTOOL" configure.in >/dev/null; then
	echo "autogen.sh: Running libtoolize..."
	libtoolize --force --copy
      fi
      echo "autogen.sh: Running aclocal $aclocalinclude ..."
      aclocal $aclocalinclude
      if grep "^AM_CONFIG_HEADER" configure.in >/dev/null; then
	echo "autogen.sh: Running autoheader..."
	autoheader
      fi
      echo "autogen.sh: Running automake --gnu $am_opt ..."
      automake --add-missing --gnu $am_opt
      echo "autogen.sh: Running autoconf ..."
      autoconf
    )
  fi
done

conf_flags="--enable-maintainer-mode --enable-compile-warnings"

if test x$NOCONFIGURE = x; then
  echo "autogen.sh: Running $srcdir/configure $conf_flags " "$@" "..."
  $srcdir/configure $conf_flags "$@" \
  && echo Now type \`make\' to compile $PKG_NAME || exit 1
else
  echo Skipping configure process.
fi
