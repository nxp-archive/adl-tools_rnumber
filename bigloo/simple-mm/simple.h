//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//


#ifndef Simple_h
#define Simple_h

#ifdef __cplusplus 
extern "C" 
{ 
  class Simple; 
#else 
  struct Simple;
#endif 

  struct Simple * simple_create();

  void simple_destroy(struct Simple * simple);

  struct Simple * simple_create_from_int( int x);

  void simple_set_x(struct Simple * simple, int x) ;
  int simple_get_x(struct Simple * simple);

#ifdef __cplusplus
}
#endif

#endif
