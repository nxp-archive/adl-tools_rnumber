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


#include "rnumber_proxy.h"
#include "bl-rnumber.h"

extern int GC_finalize_on_demand;
int rnumber_proxy_is_equal( obj_t lhs, obj_t rhs);

void set_GC_call_finalizers_to_zero()
{
  GC_finalize_on_demand = 0;
}

static char * rnumber_to_string( RNumber_proxy_t array, char *c, int len ) {
   return "<rnumber>";
}

static RNumber_proxy_t rnumber_output( RNumber_proxy_t array, FILE *fout ) {
  char * str = bl_rnumber_cstr(array);
  fprintf( fout, "0x%s", str);
  free (str);
  return array;
}

void rnumber_finalize( RNumber_proxy_t array ) {
  printf("%s:%d %s()", __FILE__, __LINE__, __FUNCTION__);
  rnumber_destroy(array->a_t.rnumber);
  array->a_t.rnumber = 0;
}

/* from bigloo2.5a/runtime/Clib/ccustom.c */
obj_t create_custom( long len );

RNumber_proxy_t proxy_from_rnumber( struct RNumber * rnumber)
{
  RNumber_proxy_t array;

  if( array = (RNumber_proxy_t)create_custom( sizeof(struct RNumber_proxy_a))) {

    array->custom.to_string  = rnumber_to_string;
    array->custom.output     = (hol_t (*)())rnumber_output;
    array->custom.final      = (void (*)(hol_t))rnumber_finalize;
    array->custom.identifier = RNUMBER_IDENTIFIER;
    array->custom.equal      = (int (*)(hol_t, hol_t))rnumber_proxy_is_equal;
    array->a_t.rnumber = rnumber;
    GC_register_finalizer( array, rnumber_finalize, 0, 0, 0 );
    return HOL_REF( array );
  } else {
    goto error;
  }

 error:
  RNUMBER_PROXY_ERROR( "proxy_from_rnumber" );
}

/*---------------------------------------------------------------------*/
/*    char                                                             */
/*    rnumber_proxyp ...                                               */
/*---------------------------------------------------------------------*/
char
rnumber_proxyp( obj_t o ) {
   return (CUSTOMP( o ) && (!strcmp( CUSTOM( o ).identifier, RNUMBER_IDENTIFIER)));
}

int rnumber_proxy_is_equal( obj_t lhs, obj_t rhs)
{
  int lhs_rnumber = rnumber_proxyp(lhs);
  int rhs_rnumber = rnumber_proxyp(rhs);
  int lhs_int = INTEGERP(lhs);
  int rhs_int = INTEGERP(rhs);

  printf("hello\n");
  if ( !(lhs_rnumber || lhs_int) || !(rhs_rnumber || rhs_int))
    return 0;
  
  if ( lhs_rnumber ) {
      if ( rhs_rnumber )
	return rnumber_rn_equal_rn(RNUM_FROM_PROXY(lhs), RNUM_FROM_PROXY(rhs));
      else
	return rnumber_rn_equal_ui(RNUM_FROM_PROXY(lhs), rhs->integer);
  } 
  if ( rhs_rnumber )
    return rnumber_rn_equal_rn(lhs->integer, RNUM_FROM_PROXY(rhs));
  else
    return lhs->integer == rhs->integer;
}
