#
# Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
#
# You may distribute under the terms of the Artistic License, as specified in
# the COPYING file.
#

dnl Process this file with autoconf to produce a configure script.

m4_define([rnumber_major_version],[2])
m4_define([rnumber_minor_version],[0])
m4_define([rnumber_micro_version],[2])
m4_define([rnumber_interface_age],[0])
m4_define([rnumber_binary_age],[0])
AC_INIT([rnumber],[rnumber_major_version.rnumber_minor_version.rnumber_micro_version])
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_LANG_CPLUSPLUS
AM_CPP_SETUP(3,4)

## Setup to use libtool.
AC_PROG_LIBTOOL

RNUMBER_MAJOR_VERSION=rnumber_major_version
RNUMBER_MINOR_VERSION=rnumber_minor_version
RNUMBER_MICRO_VERSION=rnumber_micro_version
RNUMBER_INTERFACE_AGE=rnumber_interface_age
RNUMBER_BINARY_AGE=rnumber_binary_age

AC_SUBST(RNUMBER_MAJOR_VERSION)
AC_SUBST(RNUMBER_MINOR_VERSION)
AC_SUBST(RNUMBER_MICRO_VERSION)
AC_SUBST(RNUMBER_INTERFACE_AGE)
AC_SUBST(RNUMBER_BINARY_AGE)

#########################################################################
#  Configure arguments 
#########################################################################

web_stuff=0
WEB_HOME=./web-home
AC_ARG_ENABLE(web-home,
[  --enable-web-home=<prefix>    Prefix directory to install web-stuff. (examples, html documentation, etc...)
                          If not specified, web materials are not installed.],
 if test x$enableval = x; then
    WEB_HOME=""
    web_stuff=false
 else
    WEB_HOME=$enableval
    web_stuff=true;
 fi
 AC_MSG_RESULT("Web home is $WEB_HOME")
)

AM_CONDITIONAL(WEB_STUFF, test x$web_stuff = xtrue)
AC_SUBST(WEB_HOME)

dnl On FreeBSD 3.0 (and perhaps some other systems) GNU m4 is
dnl called `gm4' where `m4' is the system's own m4.
AC_CHECK_PROGS(M4, gm4 m4, m4)

dnl Check for the desktop calculator program.
AC_PATH_PROG(DCPROG,dc)
if test "x$DCPROG" = x ; then
        AC_ERROR("Could not find program DC- this is required for the regression tests.")
fi

dnl Check for the location of Perl
AC_PATH_PROG(PERLPROG,perl)
if test "x$PERLPROG" = x ; then
        AC_ERROR("Could not find perl.  Check your path to make sure that it is present.")
fi

dnl find bigloo
BIGLOO=
BIGLOOBINDINGS=yes
AC_ARG_ENABLE(bigloo-bindings,
	AC_HELP_STRING([--enable-bigloo-bindings],[Enable the building of Bigloo bindings.  Default is true.]),
	BIGLOOBINDINGS=$enableval,
)
if test "x$BIGLOOBINDINGS" != xno ; then
	dnl <find bigloo>
	AC_PATH_PROG(BIGLOOPROG,bigloo)
	if test "x$BIGLOOPROG" = x ; then
		AC_MSG_RESULT([no.  Could not find bigloo. Check your path to make sure it is present. Bigloo is available from http://www-sop.inria.fr/mimosa/fp/Bigloo/.])
	else
	   	BIGLOO=bigloo
		AC_MSG_CHECKING([that Bigloo is new enough])
	   	BIGLOO_REVISION=`bigloo -revision`
	   	BIGLOO_MAJOR=`echo $BIGLOO_REVISION | \
	   	           sed 's/\([[0-9]]*\).\([[0-9]]*\)\([[a-zA-Z]]*\)/\1/'`
	   	BIGLOO_MINOR=`echo $BIGLOO_REVISION | \
	   	           sed 's/\([[0-9]]*\).\([[0-9]]*\)\([[a-zA-Z]]*\)/\2/'`
	   	BIGLOO_MICRO=`echo $BIGLOO_REVISION | \
	   	           sed 's/\([[0-9]]*\).\([[0-9]]*\)\([[a-zA-Z]]*\)/\3/'`
	   	if test $BIGLOO_MAJOR -ge 2 ;then 
	   	  if test $BIGLOO_MINOR -ge 8; then
	   	        BIGLOO_NEW_ENOUGH=yes;
                        AC_MSG_CHECKING([bigloo sysputc level])
			if test $BIGLOO_MICRO = a; then
                           AC_MSG_RESULT([1])
			   BIGLOO_SYSPUTC=1; 
			else
                           if test $BIGLOO_MICRO = b; then
                             AC_MSG_RESULT([1])
                             BIGLOO_SYSPUTC=1; 
                           else
                             AC_MSG_RESULT([2])
			     BIGLOO_SYSPUTC=2;
			   fi
                        fi
	   	  else
	   	        BIGLOO=
	   	        BIGLOO_NEW_ENOUGH=no;
	   	  fi
	   	else
	   	        BIGLOO=;
	   	        BIGLOO_NEW_ENOUGH=no; 
	   	fi
		if [[ ${BIGLOO_NEW_ENOUGH} = yes ]] ; then
	   		AC_MSG_RESULT([yes.  Bigloo is new enough (need 2.8a or newer)])
			AC_MSG_CHECKING([for Bigloo installation directory])
			LIBBASE=$(bigloo -eval "(begin (display *ld-library-dir*) (quit))")
		   	BIGLOO_LIBDIR="${LIBBASE}/bigloo/${BIGLOO_REVISION}"
			if [[ -d ${BIGLOO_LIBDIR} ]] ; then
				AC_MSG_RESULT([yes:  ${BIGLOO_LIBDIR}])
			   	AC_SUBST(BIGLOO_LIBDIR)
			   	if test $GCC_MAJOR -ge 3; then
			   	   BIGLOO_GCC3X="-lgcc_s"
		   		else
			   	   BIGLOO_GCC3X=""
			   	fi
			   	AC_SUBST(BIGLOO_GCC3X)
			else
				AC_MSG_RESULT([no.  Library directory ${BIGLOO_LIBDIR} does not exist.])
			fi
	   	else
			AC_MSG_RESULT([no.  Bigloo not current enough:  2.8a required, found ${BIGLOO_REVISION}])
		fi
	fi
fi

if [[ x${BIGLOO} = x ]] ; then
	AC_MSG_WARN([The building of Bigloo bindings has been disabled.])
fi

AC_SUBST([BIGLOO])
AM_CONDITIONAL(WITHOUT_BIGLOO,test x$BIGLOO = x)

if test x$BIGLOO = x; then
   AC_MSG_WARN([Bigloo bindings will not be built.])
fi

dnl find swig
PERL=
PERLBINDINGS=yes
AC_ARG_ENABLE(perl-bindings,
	AC_HELP_STRING([--disable-perl-bindings],[Enable the building of Perl bindings.  Default is true.]),
	PERLBINDINGS=$enableval,
)
if test "x$PERLBINDINGS" != xno ; then
        AC_PATH_PROG(SWIGPROG,swig)
        if test "x$SWIGPROG" = x ; then
        AC_WARN("Could not find swig. Check your path to make sure it is present.")
           AC_WARN("Swig is available from http://www.swig.org/.")
        AC_WARN("Since swig is needed for the perl bindings\, the perl bindings will *not* be built.")
           PERL=
        else
           PERL=perl
           PERL_ARCH_INCL="-I `perl -e 'use Config;print $Config{archlib};'`/CORE"
           PERL_CC_FLAGS="-fPIC `perl -e 'use Config; print $Config{ccflags}'`"
           AC_MSG_RESULT([SWIG: $SWIGPROG])
           AC_MSG_RESULT([SWIG: $PERL_ARCH_INCL])
           AC_MSG_RESULT([SWIG: $PERL_CC_FLAGS])
        fi
else
        echo "The building of Perl bindings has been disabled."
fi
AC_SUBST(PERL_ARCH_INCL)
AC_SUBST(PERL_CC_FLAGS)
AC_SUBST([PERL])
AM_CONDITIONAL(WITHOUT_SWIG,test x$PERL = x)

dnl find scribe. If scribe is not available, don't build the documentation
AC_PATH_PROG(SCRIBEPROG,scribe)
if test "x$SCRIBEPROG" = x ; then
   AC_WARN("Could not find scribe. Check your path to make sure it is present.")
   AC_WARN("Scribe is available from http://www-sop.inria.fr/mimosa/Manuel.Serrano/scribe/")
   AC_WARN("Since scribe is needed for the documentation\, the documentation will *not* be built.")
   DOC=
else
   DOC=doc
   AC_MSG_RESULT("SCRIBE $SCRIBEPROG")
fi
AC_SUBST([DOC])
AM_CONDITIONAL(WITHOUT_DOC,test x$DOC = x)


dnl C++ compiler feature check start here
dnl moved the c++ compiler alittle to make the basename check work right..
AC_LANG_CPLUSPLUS

CXXFLAGS="-Wall -g $CPPSETUP"

AC_SUBST(PROFILE)
AC_SUBST(ACLOCAL_FLAGS)
AC_SUBST(CXXFLAGS)
AC_SUBST(BIGLOO_REVISION)
AC_SUBST(BIGLOO_SYSPUTC)
AC_SUBST(EXPLTEMPLATES)
AC_PROG_INSTALL
AC_STDC_HEADERS

AC_CONFIG_FILES([\
   Makefile \
   macros/Makefile \
   include/Makefile \
   src/rnumber_feature.h \
   src/Makefile \
   bigloo/Makefile \
   bigloo/src/Makefile \
   bigloo/src/rnumber-version.h \
   bigloo/src/rnumber/Makefile \
   bigloo/src/bl-rnumber.init \
   bigloo/tests/Makefile \
   perl/Makefile \
   perl/src/Makefile \
   perl/tests/Makefile \
   tests/Makefile])

#   doc/Makefile \
#   doc/user/Makefile \

AC_CONFIG_FILES([rnumber-config],[chmod +x,-w rnumber-config])

AC_OUTPUT
