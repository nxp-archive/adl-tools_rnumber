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
#undef RNUMBER_CXX_HAVE_NAMESPACES
#undef RNUMBER_CXX_HAVE_AUTO_PTR
#undef RNUMBER_CXX_HAVE_MEMBER_TEMPLATES
#undef RNUMBER_CXX_HAVE_MUTABLE
#undef RNUMBER_CXX_HAVE_PARTIAL_SPECIALIZATION
#undef RNUMBER_CXX_GAUB
#undef RNUMBER_CXX_AMBIGUOUS_TEMPLATES
#undef RNUMBER_MAJOR_VERSION
#undef RNUMBER_MICRO_VERSION
#undef RNUMBER_MINOR_VERSION
#endif

/* autoheader adds more tests below this */
@TOP@
@BOTTOM@

#endif /* _ACCONFIG_H */
