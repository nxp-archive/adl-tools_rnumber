/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
** ===========================================================================
*/
#ifndef RNumberVersion_h
#define RNumberVersion_h "$Id$"

extern const unsigned rnumber_major_version;
extern const unsigned rnumber_minor_version;
extern const unsigned rnumber_micro_version;
extern const unsigned rnumber_binary_age;
extern const unsigned rnumber_interface_age;

/*
** rnumber_get_version
**
** for each release.
**  +  RNUMBER_MICRO_VERSION += 1;
**  +  RNUMBER_INTERFACE_AGE += 1;
**  +  RNUMBER_BINARY_AGE += 1;
**  + if any functions have been added, set interface age is set to 0.
**  + if binary compatibility is broken, set binary age and interface age
**       to zero.
**
*/
void 
rnumber_get_version(unsigned &major,unsigned &minor, unsigned &micro);

char*
rnumber_check_version (unsigned int required_major,
		     unsigned int required_minor,
		     unsigned int required_micro);


#endif
