#!/bin/sh
MAKE=`which gnumake`
if test ! -x "$MAKE" ; then MAKE=`which gmake` ; fi
if test ! -x "$MAKE" ; then MAKE=`which make` ; fi
HAVE_GNU_MAKE=`$MAKE --version|grep -c "Free Software Foundation"`

if test "$HAVE_GNU_MAKE" != "1"; then 
echo !!!! ERROR: You need GNU make to build BitNum; 
echo !!!! $MAKE is not GNU make;
exit 1; 
fi

echo Found GNU Make at $MAKE ... good.
echo This script runs configure and make...
echo Put remember necessary arguments for configure on command line.

srcdir=`dirname $0`
echo "srcdir $srcdir"
test -z "$srcdir" && srcdir=.

PKG_NAME="BitNum"

(test -f $srcdir/configure.in \
  && test -d $srcdir/src \
  && test -f $srcdir/src/RNumber.C) || {
    echo -n "Error: Directory "\`$srcdir\'" does not look like the"
    echo " top-level $PKG_NAME directory"
    exit 1
}

. $srcdir/macros/autogen.sh

