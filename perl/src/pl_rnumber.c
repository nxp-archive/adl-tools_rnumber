/*
** ===========================================================================
** $RCSfile$
** $Revision$
** $Date$
** $Author$
**
** Handwritten functions for perl wrapper.
** ===========================================================================
*/

#ifdef __cplusplus
#include <math.h>
#include <stdlib.h>
extern "C" {
#endif
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include <string.h>
#ifdef __cplusplus
}
#endif

XS(_wrap_stringp) {
    int  _result;
    unsigned int  _arg0;
    int argvi = 0;
    dXSARGS ;

    cv = cv;
    if ((items < 1) || (items > 1)) 
        croak("Usage: stringp(scalar);");
    _result = (SvPOK(ST(0)) != 0);
    ST(argvi) = sv_newmortal();
    sv_setiv(ST(argvi++),(IV) _result);
    XSRETURN(argvi);
}

XS(_wrap_integerp) {
    int  _result;
    unsigned int  _arg0;
    int argvi = 0;
    dXSARGS ;

    cv = cv;
    if ((items < 1) || (items > 1)) 
        croak("Usage: stringp(scalar);");

    printf("svIOK  returns %d\n", SvIOK(ST(0)));
    printf("svNOK  returns %d\n", SvNOK(ST(0)));
    printf("svPOK  returns %d\n", SvPOK(ST(0)));
    printf("svIOKp returns %d\n", SvIOKp(ST(0)));
    printf("svNOKp returns %d\n", SvNOKp(ST(0)));
    printf("svPOKp returns %d\n", SvPOKp(ST(0)));
    _result = (SvIOK(ST(0)) != 0);
    ST(argvi) = sv_newmortal();
    sv_setiv(ST(argvi++),(IV) _result);
    XSRETURN(argvi);
}


#ifdef __cplusplus
extern "C"
#endif
int rnumber_predicate_init()
{
  char *file = __FILE__;
  newXS("rnumber::stringp", _wrap_stringp, file);
  newXS("rnumber::integerp", _wrap_integerp, file);
  return 1;
}
