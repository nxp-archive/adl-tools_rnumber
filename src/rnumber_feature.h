/*
** ===========================================================================
** $RCSfile$
** $Revision: 42 $
** $Date: 2002-07-15 20:55:48 -0500 (Mon, 15 Jul 2002) $
** $Author: tdukes $
** ===========================================================================
*/

#ifndef __RutilFeature_h__
#define __RutilFeature_h__ "$Id: rnumber_feature.h.in 42 2002-07-16 01:55:48Z tdukes $"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* compile time version
 */
#define RNUMBER_MAJOR_VERSION				(2)
#define RNUMBER_MINOR_VERSION				(1)
#define RNUMBER_MICRO_VERSION				(10)
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
