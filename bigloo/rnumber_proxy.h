/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
**
** This file has the code taht allows us to attach rnumber objects to
** bigloos garbage collector.
** ===========================================================================
*/


#ifndef rnumber_proxy_h
#define rnumber_proxy_h

#include <bigloo.h>
/*#include "bl-rnumber.h"*/

#define CUSTOM_T struct custom

void set_GC_call_finalizers_to_zero();

typedef union rnumber_proxy
{
    CUSTOM_T custom;
    struct RNumber_proxy_a {
      CUSTOM_T cust;
      struct RNumber * rnumber;
    } a_t;
} *RNumber_proxy_t;

/*---------------------------------------------------------------------*/
/*    Big arrays serialization identification                          */
/*---------------------------------------------------------------------*/
#define RNUMBER_IDENTIFIER "rnumber.rnumber"
typedef obj_t hol_t;
#  define HOL_REF( v ) ((RNumber_proxy_t)(BREF( v )))
#  define RNUMBER_PROXY_ERROR( msg ) printf( msg )

/*---------------------------------------------------------------------*/
/*    void                                                             */
/*    unmake_bigarray ...                                              */
/*---------------------------------------------------------------------*/
void rnumber_finalize( RNumber_proxy_t array );

RNumber_proxy_t proxy_from_rnumber( struct RNumber * rnumber);
#endif
