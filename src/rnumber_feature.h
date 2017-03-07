/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
** ===========================================================================
*/

#ifndef __RutilFeature_h__
#define __RutilFeature_h__ "$Id$"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* compile time version
 */
#define RNUMBER_MAJOR_VERSION				(2)
#define RNUMBER_MINOR_VERSION				(1)
#define RNUMBER_MICRO_VERSION				(29)
#define RNUMBER_BINARY_AGE				(0)
#define RNUMBER_INTERFACE_AGE				(0)
#define	RNUMBER_CHECK_VERSION(major,minor,micro)	\
    (RNUMBER_MAJOR_VERSION > (major) || \
     (RNUMBER_MAJOR_VERSION == (major) && RNUMBER_MINOR_VERSION > (minor)) || \
     (RNUMBER_MAJOR_VERSION == (major) && RNUMBER_MINOR_VERSION == (minor) && \
      RNUMBER_MICRO_VERSION >= (micro)))



#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
