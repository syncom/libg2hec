/*++
Module Name:
    g2hec_nsfieldtype.h

Summary:
    field_t and poly_t settings

Note:
    Needs to be included by the main module g2hec_Genus2_ops.h.
    Currently only ZZ_p and ZZ_pX are supported field types.
--*/

#ifndef NSFIELDTYPE_H
#define NSFIELDTYPE_H

/**************************************************************/
/*  To support ZZ_pE, must change the following to
#define _FLD_TYPE ZZ_pE.  Default is ZZ_p.

I know, this is by no means convenient.  But the way in which NTL uses 
different fields makes it hard to switch between different types easily.
*/
 #define _FLD_TYPE ZZ_p
/**************************************************************/

  /* SET_POLY_TYPE(T) sets the type of the polynomials 
  it needs to be invoked by the client before the polynomials 
  are defined. 
  Example: SET_POLY_TYPE(ZZ_pX)
  */

#define SET_POLY_TYPE(T) \
typedef NTL_NNS _FLD_TYPE field_t; \
typedef NTL_NNS T poly_t; \
typedef const poly_t poly_tc

#if _FLD_TYPE == ZZ_p

  #include <NTL/ZZ_pXFactoring.h>

  SET_POLY_TYPE(ZZ_pX);

#elif _FLD_TYPE == ZZ_pE
  #include <NTL/ZZ_pEXFactoring.h>

  SET_POLY_TYPE(ZZ_pEX);

#elif _FLD_TYPE == GF2

  #error "Field type GF2 not currently supported"

#elif _FLD_TYPE == GF2E

/*
  #include <NTL/GF2EXFactoring.h>

  SET_POLY_TYPE(GF2EX);
*/
  #error "Field type GF2E not currently supported"

#else 
  #error "Unsupported field type"

#endif


#endif /* NSFIELDTYPE_H */
