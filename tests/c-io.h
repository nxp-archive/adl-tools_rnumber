//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//


#ifdef __cplusplus
extern "C" {
#endif

void * ss_create();
void ss_ends( void * ss);
const char * ss_str( void * ss);
void ss_destroy( void * ss);

#ifdef __cplusplus
}
#endif
