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
#define FLD_TYPE_ZZ_pE.  Default is FLD_TYPE_ZZ_p.

I know, this is by no means convenient.  But the way in which NTL uses 
different fields makes it hard to switch between different types easily.
*/
#define FLD_TYPE_ZZ_p
/**************************************************************/

#ifdef FLD_TYPE_ZZ_p

  #include <NTL/ZZ_pXFactoring.h>

  typedef NTL_NNS ZZ_p field_t;
  typedef NTL_NNS ZZ_pX poly_t;
  typedef const poly_t poly_tc;

#endif


#ifdef FLD_TYPE_ZZ_pE
  #include <NTL/ZZ_pEXFactoring.h>

  typedef NTL_NNS ZZ_pE field_t;
  typedef NTL_NNS ZZ_pEX poly_t;
  typedef const poly_t poly_tc;

#endif

#ifdef FLD_TYPE_GF2

  #error "Field type GF2 not currently supported"

#endif

#ifdef FLD_TYPE_GF2E

/*
  #include <NTL/GF2EXFactoring.h>

  SET_POLY_TYPE(GF2EX);
*/
  #error "Field type GF2E not currently supported"

#endif


#endif /* NSFIELDTYPE_H */
