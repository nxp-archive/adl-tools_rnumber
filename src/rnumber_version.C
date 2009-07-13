//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//

//
// Provides a function for obtaining version information
//
// $Id$
//

#include "rnumber_feature.h"
#include "rnumber_version.h"

const unsigned rnumber_major_version = RNUMBER_MAJOR_VERSION;
const unsigned rnumber_minor_version = RNUMBER_MINOR_VERSION;
const unsigned rnumber_micro_version = RNUMBER_MICRO_VERSION;
const unsigned rnumber_binary_age    = RNUMBER_BINARY_AGE;
const unsigned rnumber_interface_age = RNUMBER_INTERFACE_AGE;

void 
rnumber_get_version(unsigned &major,unsigned &minor,unsigned &micro )
{
  major = rnumber_major_version;
  minor = rnumber_minor_version;
  micro = rnumber_micro_version;
}

const char*
rnumber_check_version (unsigned int required_major,
		     unsigned int required_minor,
		     unsigned int required_micro)
{
  if (required_major > RNUMBER_MAJOR_VERSION)
    return "rnumber version too old (major mismatch)";
  if (required_major < RNUMBER_MAJOR_VERSION)
    return "rnumber version too new (major mismatch)";
  if (required_minor > RNUMBER_MINOR_VERSION)
    return "rnumber version too old (minor mismatch)";
  if (required_minor < RNUMBER_MINOR_VERSION)
    return "rnumber version too new (minor mismatch)";
  if (required_micro < RNUMBER_MICRO_VERSION - RNUMBER_BINARY_AGE)
    return "rnumber version too new (micro mismatch)";
  if (required_micro > RNUMBER_MICRO_VERSION)
    return "rnumber version too old (micro mismatch)";
  return 0;
}
