dnl AM_CPP_SETUP
dnl
dnl This performs a variety of checks related to C++ usage and sets various
dnl variables accordingly.  The idea is that you include the variable CPPSETUP
dnl when defining CXXFLAGS.
dnl
dnl If the --enable-opt option is set, then OPT is set to a flag.
dnl
dnl Test to see if --enable-profile is set.  If it is, we clear FPIC (if
dnl on Solaris).
dnl
dnl If --enable-profile is set, PROFILE is set to a flag.
dnl 
dnl If --enable-efence is set, we set EFENCE to the location of the library
dnl and substitute that variable.  The user can specify a location of Electric Fence
dnl by supplying a value for this option.
dnl
dnl Test to see if fpic is needed.  We assume it is required Solaris.
dnl If it is required, we set the variable FPIC to the contents of the flag.
dnl
dnl We also define, and substitute, the variable RFLAG, which is set to something
dnl that should act as an option to encode a path for library lookup.  You can use
dnl this in a config file, e.g. "@RFLAG@/foo/bar".
dnl
AC_DEFUN(AM_CPP_SETUP,
[dnl

AC_MSG_CHECKING( to see if -fPIC is needed)
MY_OS=`/usr/bin/env uname -s`
if test x$MY_OS = xSunOS ; then
   AC_MSG_RESULT([yes])
   FPIC="-fPIC"
else
   FPIC=
   AC_MSG_RESULT([no])
fi

RFLAG="-Wl,-R"
AC_SUBST(RFLAG)

AC_ARG_ENABLE(opt,
[  --enable-opt    Enable optimization flag (-O3), disables debug],
 OPT="$CXXFLAGS -O3"
 AC_MSG_RESULT([Optimizing with -O3]),
)

AC_ARG_ENABLE(static,
[  --enable-static    Enable static building],
 FPIC=""
 AC_MSG_RESULT([Static build selected.]),
)

PROFILE=
AC_ARG_ENABLE(profile,
[  --enable-profile    Enable profiling],
 PROFILE="-pg"
 AC_MSG_RESULT("Profiling with -pg")
 if test x$OS = xSunOS ; then
   echo "Turning off position-independent code b/c we're on Solaris and we are profiling."
   FPIC=
 fi,
)

default_efence="/nfs/ibmoto/tools/tlv4/raptor/lib/obj.SunOS/libefence.a"

AC_ARG_ENABLE(efence,
[  --enable-efence=<location>    link test programs with electric fence. If no location
                                 is given, /nfs/ibmoto/tools/tlv4/raptor/lib/obj.SunOS/libefence
                                 is used],
 if test x$enableval = x; then
   EFENCE=$default_efence
 else
   EFENCE=$enableval
 fi
 if test -f $EFENCE; then
   AC_MSG_RESULT([using '$EFENCE' for electric fence])
 else
   AC_MSG_ERROR(electric fence could not be found as file $EFENCE)
 fi
AC_MSG_RESULT(linking with electric fence - $EFENCE),
EFENCE=""
AC_MSG_RESULT(efence will not be used)
)
AC_SUBST(EFENCE)

dnl
dnl Include this flag in CXXFLAGS.
dnl
CPPSETUP="$OPT $FPIC $PROFILE"

])
