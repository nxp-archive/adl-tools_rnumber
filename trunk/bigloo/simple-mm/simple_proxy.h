//
// Copyright (C) 2005 by Freescale Semiconductor Inc.  All rights reserved.
//
// You may distribute under the terms of the Artistic License, as specified in
// the COPYING file.
//

#include <bigloo.h>
#include "simple.h"

#define CUSTOM_T struct custom

void simple_set_call_finalizers();

typedef union simple_proxy
{
    CUSTOM_T custom;
    struct simple_proxy_a {
      CUSTOM_T cust;
      struct Simple * simple;
    } a_t;
} *simple_proxy_t;

/*---------------------------------------------------------------------*/
/*    Big arrays serialization identification                          */
/*---------------------------------------------------------------------*/
#define SIMPLE_IDENTIFIER "simple.simple"
typedef obj_t hol_t;
#  define HOL_REF( v ) ((simple_proxy_t)(BREF( v )))
#  define SIMPLE_PROXY_ERROR( msg ) printf( msg )

/*---------------------------------------------------------------------*/
/*    void                                                             */
/*    unmake_bigarray ...                                              */
/*---------------------------------------------------------------------*/
void
unmake_simple_t( simple_proxy_t array );

simple_proxy_t make_simple_t();
