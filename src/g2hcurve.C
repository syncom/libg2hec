/* Implementation of curve routines over V. Shoup's NTL library */

// The following headers are included by "Genus2_ops.h"
//#include <iostream>
//#include <cstdlib>

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <g2hec_Genus2_ops.h>

NS_G2_START_IMPL

void g2hcurve :: set_f (const poly_tc& poly) 
{
  fpoly = poly;
}

void g2hcurve :: set_h (const poly_tc& poly)
{
  hpoly = poly;
}

void g2hcurve :: update ()
{
  // Set is_genus_2
  if ( deg(fpoly) == 5 && deg(hpoly) <=2 )
    is_genus_2 = TRUE;
  else
    is_genus_2 = FALSE;

  // Set is_nonsingular
  /* Curve y^2 + h(x)*y = f(x) is nonsingular if and only if
   no point on the curve over alg closure satisfies 
   (1) 2*y + h(x) = 0 and (2) f' - h'*y = 0.
   For odd characteristic, this means the function 
    f(x) + ( h(x)/2 )^2 
   has no multiple root.

   For characteristic 2, this requires h(x) <> 0 (c.f. Example 14.9 of 
HOEHCC).  We do not support even characteristic for now (Aug. 4, 2008).
  */

  #if ( _FLD_TYPE == ZZ_p ) || (  _FLD_TYPE == ZZ_pE )
  do {
    poly_t testpoly = fpoly + hpoly*hpoly/4, testpoly_diff;

    // testpoly_diff = testpoly's derivative
    diff(testpoly_diff, testpoly);

    is_nonsingular = IsOne( GCD(testpoly, testpoly_diff) );

  } while (0);

  #elif ( _FLD_TYPE == GF2 ) || ( _FLD_TYPE == GF2E )
    #error "Characteristic 2 not yet supported"

  #else
    #error "Unsupported field type"

  #endif

}

const poly_tc& g2hcurve :: get_f() const 
{
  return fpoly;
}

const poly_tc& g2hcurve :: get_h() const
{
  return hpoly;
}

bool_t g2hcurve :: is_valid_curve() const
{
  /* Returns TRUE only if curve is nonsingular, of genus 2 and
has leading coefficient 1
   */
  return (is_nonsingular && is_genus_2 && IsOne(LeadCoeff(fpoly)));
}

g2hcurve& g2hcurve :: random()
{
  // Set number of trials to 100. This should suffice most of the time.

  for (long ntrial = 100; ntrial > 0; ntrial--) {
    NTL_NNS random(fpoly, 6);
    SetCoeff(fpoly, 5, 1); // Make sure of degree 5 and monic
    NTL_NNS random(hpoly, 3);
    update();

    if (is_valid_curve())
      return *this;
  }
  
  cerr << "Random genus 2 curve not generated" << endl;
  abort();
}

std::ostream& operator<<(std::ostream& s, const g2hcurve& a)
{
  s << "Curve: y^2 + h(x)*y = f(x)" << endl;

  // print h(x)
  s << "       h(x) = ";

  print_poly(a.get_h(), &s);

  // Print f(x)
  s << "       f(x) = ";

  print_poly(a.get_f(), &s);


  // Print curve info
  if (a.is_valid_curve())
    s << "       Genus 2 curve is nonsingular" << endl;
  else
    s << "       Curve is singular, or not genus 2, or f(x) is not monic" 
      << endl;
  return s;
}

void print_poly(poly_tc& poly, std::ostream *s) {
  ndeg_t degree = deg(poly);

  if (degree >=0){
    for (ndeg_t i = degree ; i > 0; i-- ) {

      if ( IsZero(coeff(poly, i)) ) {

        // do nothing 

     } else if ( IsOne(coeff(poly, i)) ) {

        if (i == 1)
          *s << (i == degree ? "" : " + ") << "x" ;
        else 
          *s << (i == degree ? "" : " + ") << "x^" << i;

      } else {

        if (i == 1)
          *s << (i == degree ? "" : " + ") << coeff(poly, i) << "*x";
        else 
          *s << (i == degree ? "" : " + ") << coeff(poly, i) << "*x^" << i;

      }

    } // endfor 

    if (!IsZero(coeff(poly, 0)))
      *s << (degree == 0 ? "" : " + ") << coeff(poly, 0);

    cout << endl;

  } else { // 0 polynomial
    *s << 0 << endl;
  }
}

NS_G2_END_IMPL


