dnl AM_PATH_BITNUM([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND [, MODULES]]]])
dnl Test for BITNUM, and define BITNUM_CFLAGS, BITNUM_LIBS, BITNUM_STATIC_LIBS and BITNUM_HELPERS
dnl
AC_DEFUN(AM_PATH_BITNUM,
[dnl 
   AC_PATH_PROG(BITNUM_CONFIG, bitnum-config, no)
   min_bitnum_version=ifelse([$1], ,0.0.1,$1)
   AC_MSG_CHECKING(for bitnum version $min_bitnum_version)
   no_bitnum="" 
   enable_bitnumtest="yes"
   if test "$BITNUM_CONFIG" = "no" ; then
     no_bitnum=yes
   else 
     BITNUM_CFLAGS=`$BITNUM_CONFIG $bitnum_config_args --cflags`
     BITNUM_LIBS=`$BITNUM_CONFIG $bitnum_config_args --libs`
     BITNUM_STATIC_LIBS=`$BITNUM_CONFIG $bitnum_config_args --static-libs`
     BITNUM_HELPERS=`$BITNUM_CONFIG $bitnum_config_args --helper-path`
     bitnum_config_major_version=`$BITNUM_CONFIG $bitnum_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
     bitnum_config_minor_version=`$BITNUM_CONFIG $bitnum_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
     bitnum_config_micro_version=`$BITNUM_CONFIG $bitnum_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
     if test "x$enable_bitnumtest" = "xyes" ; then
       ac_save_CFLAGS="$CFLAGS"
       ac_save_CXXFLAGS="$CXXFLAGS"
       ac_save_LIBS="$LIBS"
       CFLAGS="$CFLAGS $BITNUM_CFLAGS"
       CXXFLAGS=$CFLAGS
       LIBS="$BITNUM_STATIC_LIBS $LIBS"
dnl
dnl Now check if the installed bitnum is sufficiently new. (Also sanity
dnl checks the results of bitnum-config to some extent).
dnl
      rm -f conf.bitnumtest
      AC_TRY_RUN([
#include <bitnum/bitnum.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int 
main ()
{
  int major, minor, micro;
  char *tmp_version;

  system ("touch conf.bitnumtest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = strdup("$min_bitnum_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_bitnum_version");
     exit(1);
   }

  printf("bitnum version %d.%d.%d.\n", bitnum_major_version, 
	bitnum_minor_version, bitnum_micro_version );

  if ((bitnum_major_version != $bitnum_config_major_version) ||
      (bitnum_minor_version != $bitnum_config_minor_version) ||
      (bitnum_micro_version != $bitnum_config_micro_version))
    {
      printf("\n*** 'bitnum-config --version' returned %d.%d.%d, but BITNUM (%d.%d.%d)\n", 
             $bitnum_config_major_version, $bitnum_config_minor_version, $bitnum_config_micro_version,
             bitnum_major_version, bitnum_minor_version, bitnum_micro_version);
      printf ("*** was found! If bitnum-config was correct, then it is best\n");
      printf ("*** to remove the old version of BITNUM. You may also be able to fix the error\n");
      printf("*** by modifying your LD_LIBRARY_PATH enviroment variable, or by editing\n");
      printf("*** /etc/ld.so.conf. Make sure you have run ldconfig if that is\n");
      printf("*** required on your system.\n");
      printf("*** If bitnum-config was wrong, set the environment variable BITNUM_CONFIG\n");
      printf("*** to point to the correct copy of bitnum-config, and remove the file config.cache\n");
      printf("*** before re-running configure\n");
    } 
#if defined (BITNUM_MAJOR_VERSION) && defined (BITNUM_MINOR_VERSION) && defined (BITNUM_MICRO_VERSION)
  else if ((bitnum_major_version != BITNUM_MAJOR_VERSION) ||
	   (bitnum_minor_version != BITNUM_MINOR_VERSION) ||
           (bitnum_micro_version != BITNUM_MICRO_VERSION))
    {
      printf("*** BITNUM header files (version %d.%d.%d) do not match\n",
	     BITNUM_MAJOR_VERSION, BITNUM_MINOR_VERSION, BITNUM_MICRO_VERSION);
      printf("*** library (version %d.%d.%d)\n",
	     bitnum_major_version, bitnum_minor_version, bitnum_micro_version);
    }
#endif /* defined (BITNUM_MAJOR_VERSION) ... */
  else
    {
      if ((bitnum_major_version > major) ||
        ((bitnum_major_version == major) && (bitnum_minor_version > minor)) ||
        ((bitnum_major_version == major) && (bitnum_minor_version == minor) && (bitnum_micro_version >= micro)))
      {
        return 0;
       }
     else
      {
        printf("\n*** An old version of BITNUM (%d.%d.%d) was found.\n",
               bitnum_major_version, bitnum_minor_version, bitnum_micro_version);
        printf("*** You need a version of BITNUM newer than %d.%d.%d. The latest version of\n",
	       major, minor, micro);
        printf("*** BITNUM is always available from ftp://ftp.bitnum.org.\n");
        printf("***\n");
        printf("*** If you have already installed a sufficiently new version, this error\n");
        printf("*** probably means that the wrong copy of the bitnum-config shell script is\n");
        printf("*** being found. The easiest way to fix this is to remove the old version\n");
        printf("*** of BITNUM, but you can also set the BITNUM_CONFIG environment to point to the\n");
        printf("*** correct copy of bitnum-config. (In this case, you will have to\n");
        printf("*** modify your LD_LIBRARY_PATH enviroment variable, or edit /etc/ld.so.conf\n");
        printf("*** so that the correct libraries are found at run-time))\n");
      }
    }
  return 1;
}
],dnl action if true
,dnl action if false
 no_bitnum=yes,dnl
dnl action if cross-compiling
[echo $ac_n "cross compiling; assumed OK... $ac_c"])dnl end of AC_TRY_RUN

       CFLAGS="$ac_save_CFLAGS"
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_bitnum" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$BITNUM_CONFIG" = "no" ; then
       echo "*** The bitnum-config script installed by BITNUM could not be found"
       echo "*** If BITNUM was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the BITNUM_CONFIG environment variable to the"
       echo "*** full path to bitnum-config."
     else
       if test -f conf.bitnumtest ; then
        :
       else
          echo "*** Could not run BITNUM test program, checking why..."
          CFLAGS="$CFLAGS $BITNUM_CFLAGS"
					CXXFLGAS="$CXXFLAGS $BITNUM_CFLAGS"
          LIBS="$LIBS $BITNUM_STATIC_LIBS"
          AC_TRY_LINK([
#include <bitnum/bitnum.h>
#include <stdio.h>
],      [ return ((bitnum_major_version) || (bitnum_minor_version) || (bitnum_micro_version)); ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding BITNUM or finding the wrong"
          echo "*** version of BITNUM. If it is not finding BITNUM, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location.  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system. Some systems don't support /etc/ld.so.conf. On"
	  echo "*** those systems you must use LD_LIBRARY_PATH."
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"
          echo "***" ],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means BITNUM was incorrectly installed"
          echo "*** or that you have moved BITNUM since it was installed. In the latter case, you"
          echo "*** may want to edit the bitnum-config script: $BITNUM_CONFIG" ])
          CFLAGS="$ac_save_CFLAGS"
          CXXFLAGS="$ac_save_CXXFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     BITNUM_CFLAGS=""
     BITNUM_LIBS=""
     ifelse([$3], , :, [$3])
  fi

  AC_SUBST(BITNUM_CFLAGS)
  AC_SUBST(BITNUM_LIBS)
  AC_SUBST(BITNUM_STATIC_LIBS)
  AC_SUBST(BITNUM_HELPERS)
  rm -f conf.bitnumtest
])
