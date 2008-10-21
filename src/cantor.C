/* Cantor's algorithm for computing divisor composition x = a + b.

Algorithm 14.7 of "Handbook of Elliptic and Hyperelliptic Curve Cryptography",
H. Cohen, et al.
*/

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
#include <g2hec_Genus2_ops.h>

NS_G2_START_IMPL

bool_t add_cantor(divisor& x, const divisor& a, const divisor& b)
{
  bool_t OK = TRUE;

  if (!a.is_valid_divisor() || !b.is_valid_divisor()) {
    OK = FALSE;
  } else {
    poly_tc u1 = a.get_upoly();
    poly_tc v1 = a.get_vpoly(); 
    poly_tc u2 = b.get_upoly(); 
    poly_tc v2 = b.get_vpoly();
    poly_tc f = x.get_curve().get_f();
    poly_tc h = x.get_curve().get_h();
    poly_t d1, d, e1, e2, c1, c2, temp1, temp2, u, v;

    // Step 1: d1 = gcd(u1, u2) 
    //[extended Euclid's algorithm gives d1 = e1*u1 + e2*u2 ]
    XGCD(d1, e1, e2, u1, u2);

    // Step 2: d = gcd(d1, v1+v2+h)
    // [d = c1*d1 + c2*(v1 + v2 + h)]
    temp1 = v1 + v2 + h;
    XGCD(d, c1, c2, d1, temp1);

    // Step 3: s1 = c1*e1, s2 = c1*e2, s3 = c2
    // Step 4: u = u1*u2/d^2
    // v= (s1*u1*v2 + s2*u2*v1 + s3*(v1*v2 + f))/d mod u

    u = (u1 * u2)/(d*d);

    temp1 = (c1*e1*u1*v2 + c1*e2*u2*v1 + c2*(v1*v2 + f))/d;

    v = temp1 % u;

    // Step 5-8:
    // 5. repeat
    // 6. u' = (f - v*h -v^2)/u, v' = -(h+v) mod u'
    // 7. u = u', v = v'
    // 8. until deg u <= genus = 2
    for ( ;deg(u) > genus; ) {
      temp1 = (f - v*h - v*v)/u;
      temp2 = (-h - v) % temp1;
      u = temp1; v = temp2;
    } // endfor

    // Step 9: make u monic
    MakeMonic(u);

    // Step 10: return [u, v]
    x.set_upoly(u);
    x.set_vpoly(v);
    x.update();
    assert(x.is_valid_divisor());
  }

  return OK;
}

NS_G2_END_IMPL
