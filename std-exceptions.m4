dnl See whether c++ lib has std exceptions
dnl this sets EXCEPTION_FILE to "local_exceptions.h" or <exceptions>
dnl GCC_STD_EXCEPTIONS
AC_DEFUN(AM_DECL_STD_EXCEPTIONS,
[dnl
 AC_TRY_COMPILE(
 [
   #include <stdexcept>
 ],[
   std::runtime_error ( "runtime error" );
   cout << "test" << endl;
 ],[
   STD_LIB_EXCEPTIONS=true;
   EXCEPTION_FILE="<stdexcept>"
   AC_MSG_RESULT(c++ library has standard exceptions.)
 ],[
   AC_MSG_RESULT(c++ library does not have standard exceptions local_exceptions.h will be used)
   EXCEPTION_FILE="\"local_exceptions.h\""
 ]) dnl end of AC_TRY_COMPILE
])

dnl])
