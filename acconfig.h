#ifndef _ACCONFIG_H
#define _ACCONFIG_H 1

/* package & version name */
#undef VERSION
#undef PACKAGE

/* feature tests that are used during library creation only */
#undef HAVE_WORKING_BASENAME

/* autoheader reqiures all defines inside acconfig.h, so all
   defines from <x>--config.h are added here inside of #if 0 */
#if 0
#undef BITNUM_CXX_HAVE_NAMESPACES
#undef BITNUM_CXX_HAVE_AUTO_PTR
#undef BITNUM_CXX_HAVE_MEMBER_TEMPLATES
#undef BITNUM_CXX_HAVE_MUTABLE
#undef BITNUM_CXX_HAVE_PARTIAL_SPECIALIZATION
#undef BITNUM_CXX_GAUB
#undef BITNUM_CXX_AMBIGUOUS_TEMPLATES
#undef BITNUM_MAJOR_VERSION
#undef BITNUM_MICRO_VERSION
#undef BITNUM_MINOR_VERSION
#endif

/* autoheader adds more tests below this */
@TOP@
@BOTTOM@

#endif /* _ACCONFIG_H */
