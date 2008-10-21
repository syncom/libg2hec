#ifndef POLYTYPE_H
#define POLYTYPE_H
/* Set NTL polynomial type */


#include "g2hec_Genus2_ops.h"


#if _FLD_TYPE == ZZ_p
    #include <NTL/ZZ_pXFactoring.h>
    SET_POLY_TYPE(ZZ_pX)
#elif _FLD_TYPE == ZZ_pE
    #include <NTL/ZZ_pEXFactoring.h>
    SET_POLY_TYPE(ZZ_pEX)
#elif _FLD_TYPE == GF2E
    #include <NTL/GF2EXFactoring.h>
    SET_POLY_TYPE(GF2EX)
#else 
    #error "Unsupported field type"
#endif

#endif
