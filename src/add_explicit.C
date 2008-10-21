/* Genus 2 divisor group law via explicit formulas.

Divisor addition: Algorithm 14.19 of "Handbook of EAHCC"

Divisor doubling: Algorithm 14.21 of "Handbook of EAHCC"

Special cases are handled by calling add_cantor()

*/

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
#include <g2hec_Genus2_ops.h>

NS_G2_START_IMPL

static bool_t add_diff(divisor& x, const divisor& a, const divisor& b)
     // x = a + b where a != b via explicit formulas
     // c.f. Algorithm 14.9 of HOEHCC
     // Assumes upolys of a and b are both of degree 2 and have no common
     // factor.
{
  /* Variables 
We choose to use local variables for now to make the function thread safe.
Note that this may affect the performance of the program as opposed to 
the method of passing along the temporary variables.
  */

  bool_t OK = TRUE;

  const field_t f4 = coeff(a.get_curve().get_f(), 4), 
                h1 = coeff(a.get_curve().get_h(), 1), 
                h2 = coeff(a.get_curve().get_h(), 2),
                h0 = coeff(a.get_curve().get_h(), 0), 
    u11 = coeff(a.get_upoly(), 1), u10 = coeff(a.get_upoly(), 0),
    u21 = coeff(b.get_upoly(), 1), u20 = coeff(b.get_upoly(), 0),
    v11 = coeff(a.get_vpoly(), 1), v10 = coeff(a.get_vpoly(), 0),
    v21 = coeff(b.get_vpoly(), 1), v20 = coeff(b.get_vpoly(), 0);

  field_t z1, z2, z3, z4, r, inv1, inv0, w0, w1, w2, w3, s1p, s0p,
    w4, w5, s0pp, l2p, l1p, l0p, u0p, u1p, v1p, v0p;

  poly_t up, vp;

  /* Explicit formulas */

  /* Step 1: 
     Compute r = Res(u1, u2).
   z1 = u11 - u21, z2 = u20 - u10, z3 = u11*z1 + z2, z4 = z1*u10, 
   r = z2*z3 + z4*z1 
  */
  z1 = u11 - u21;
  z2 = u20 - u10;
  z3 = u11*z1 + z2;
  z4 = z1*u10;
  r = z2*z3 + z4*z1;

  assert(!IsZero(r));  // Res(u1, u2)<>0, i.e., GCD(u1, u2) = 1

  /* Step 2: 
     inv1 = z1, inv0 = z3 
  */
  inv1 = z1; 
  inv0 = z3;

  /* Step 3: 
     w0 = v10 - v20, w1 = v11 - v21, w2 = inv0*w0, w3 = inv1*w1, 
     s1p = (inv0 + inv1)*(w0 + w1) - w2 - w3*(1 + u11), s0p = w2 - z4*w1
     If s1p = 0, handled by Cantor's algorithm. 
  */
  w0 = v10 - v20; 
  w1 = v11 - v21; 
  w2 = inv0*w0; 
  w3 = inv1*w1;
  s1p = (inv0 + inv1)*(w0 + w1) - w2 - w3*(1 + u11);

  // Special case
  if (IsZero(s1p)) 
    return add_cantor(x, a, b);

  s0p = w2 - z4*w1;
  

  /* Step 4:
     w1 = 1/(r*s1p), w2 = r*w1, w3 = s1p^2*w1, w4 = r*w2, w5 = w4^2, 
     s0pp = s0p*w2
  */ 
  w1 = 1/(r*s1p);
  w2 = r*w1;
  w3 = sqr(s1p)*w1;
  w4 = r*w2;
  w5 = sqr(w4);
  s0pp = s0p*w2;

  /* Step 5:
     l2p = u21 + s0pp, l1p = u21*s0pp + u20, l0p = u20*s0pp
  */
  l2p = u21 + s0pp;
  l1p = u21*s0pp + u20;
  l0p = u20*s0pp;

  /* Step 6:
     u0p = (s0pp - u11)*(s0pp - z1 + h2*w4) - u10,
     u0p = u0p + l1p + (h1 + 2*v21)*w4 + (2*u21 + z1 - f4)*w5,
     u1p = 2*s0pp - z1 + h2*w4 - w5
  */
  u0p = (s0pp - u11)*(s0pp - z1 + h2*w4) - u10;
  u0p = u0p + l1p + (h1 + 2*v21)*w4 + (2*u21 + z1 - f4)*w5;
  u1p = 2*s0pp - z1 + h2*w4 - w5;

  /* Step 7:
     w1 = l2p - u1p, w2 = u1p*w1 + u0p - l1p, v1p = w2*w3 - v21 - h1 + h2*u1p,
     w2 = u0p*w1 - l0p, v0p = w2*w3 - v20 - h0 + h2*u0p
  */
  w1 = l2p - u1p;
  w2 = u1p*w1 + u0p - l1p;
  v1p = w2*w3 - v21 - h1 + h2*u1p;
  w2 = u0p*w1 - l0p;
  v0p = w2*w3 - v20 - h0 + h2*u0p;

  /* Step 8:
     return [up, vp] = [x^2 + u1p*x + u0p, v1p*x + v0p]
  */ 
  SetCoeff(up, 2, 1);
  SetCoeff(up, 1, u1p);
  SetCoeff(up, 0, u0p);

  SetCoeff(vp, 1, v1p);
  SetCoeff(vp, 0, v0p);

  x.set_upoly(up); 
  x.set_vpoly(vp);

  x.update();

#if DEBUG_LEVEL > 1
  cout << "Entered add_diff()" << endl;
  cout << x << endl;
#endif

  assert(OK = ( OK && x.is_valid_divisor()) );

  return OK;
}

static bool_t doubling(divisor& x, const divisor& a) 
     // x = a + a via explicit formulas

{  /* Variables 
We choose to use local variables for now to make the function thread safe.
Note that this may affect the performance of the program as opposed to 
the method of passing along the temporary variables.
  */
 
  bool_t OK = TRUE;


  const field_t f4 = coeff(a.get_curve().get_f(), 4), 
                f3 = coeff(a.get_curve().get_f(), 3),
                f2 = coeff(a.get_curve().get_f(), 2),
                h1 = coeff(a.get_curve().get_h(), 1), 
                h2 = coeff(a.get_curve().get_h(), 2),
                h0 = coeff(a.get_curve().get_h(), 0), 
    u1 = coeff(a.get_upoly(), 1), u0 = coeff(a.get_upoly(), 0),
    v1 = coeff(a.get_vpoly(), 1), v0 = coeff(a.get_vpoly(), 0);

  field_t v1t, v0t, w0, w1, w2, w3, r, inv1p, inv0p, w4, t1p, t0p, s1p,
    s0p, w5, s0pp, l2p, l1p, l0p, u0p, u1p, v1p, v0p;

  poly_t up, vp;
 
  /* Explicit formulas */
 
  /* Step 1: 
     v1t = h1 + 2*v1 - h2*u1, v0t = h0 + 2*v0 - h2*u0 
  */
  v1t = h1 + 2*v1 - h2*u1; 
  v0t = h0 + 2*v0 - h2*u0;

  /* Step 2: 
     w0 = v1^2, w1 = u1^2, w2 = v1t^2, w3 = u1*v1t, 
     r = u0*w2 + v0t*(v0t - w3) 
  */
  w0 = sqr(v1); 
  w1 = sqr(u1);
  w2 = sqr(v1t);
  w3 = u1*v1t;
  r = u0*w2 + v0t*(v0t - w3);
  assert(!IsZero(r));

  /* Step 3:
     inv1p = -v1t, inv0p = v0t - w3 
  */
   inv1p = -v1t;
   inv0p = v0t - w3;

  /* Step 4: 
     w3 = f3 + w1, w4 = 2*u0, t1p = 2*(w1 - f4*u1) + w3 - w4 - h2*v1,
     t0p = u1*(2*w4 - w3 + f4*u1 + h2*v1) + f2 - w0 - 2*f4*u0 - h1*v1 - h2*v0
  */
   w3 = f3 + w1;
   w4 = 2*u0;
   t1p = 2*(w1 - f4*u1) + w3 - w4 - h2*v1;
   t0p = u1*(2*w4 - w3 + f4*u1 + h2*v1) + f2 - w0 - 2*f4*u0 - h1*v1 - h2*v0;

  /* Step 5:
     w0 = t0p*inv0p, w1 = t1p*inv1p, 
     s1p = (inv0p + inv1p)*(t0p + t1p) - w0 - w1*(1+u1),
     s0p = w0 - u0*w1.

     If s1p = 0, call add_cantor().
  */
   w0 = t0p*inv0p;
   w1 = t1p*inv1p;
   s1p = (inv0p + inv1p)*(t0p + t1p) - w0 - w1*(1+u1);

#if DEBUG_LEVEL > 1
   cout << "r = " << r << endl;
   cout << "s1p = " << s1p << endl;
#endif 

  // Special case
  if (IsZero(s1p)) 
    return add_cantor(x, a, a);

   s0p = w0 - u0*w1;

  /* Step 6:
     w1 = 1/(r*s1p), w2 = r*w1, w3 = s1p^2*w1, w4 = r*w2, w5 = w4^2,
     s0pp = s0p*w2
   */
  w1 = 1/(r*s1p);
  w2 = r*w1;
  w3 = sqr(s1p)*w1;
  w4 = r*w2;
  w5 = sqr(w4);
  s0pp = s0p*w2;

  /* Step 7:
     l2p = u1 + s0pp, l1p = u1*s0pp + u0, l0p = u0*s0pp
  */
   l2p = u1 + s0pp;
   l1p = u1*s0pp + u0;
   l0p = u0*s0pp;

  /* Step 8:
     u0p = s0pp^2 + w4*(h2*(s0pp - u1) + 2*v1 + h1) + w5*(2*u1 - f4),
     u1p = 2*s0pp + h2*w4 - w5
  */
   u0p = sqr(s0pp) + w4*(h2*(s0pp - u1) + 2*v1 + h1) + w5*(2*u1 - f4);
   u1p = 2*s0pp + h2*w4 - w5;

  /* Step 9:
     w1 = l2p - u1p, w2 = u1p*w1 + u0p - l1p, v1p = w2*w3 - v1 - h1 + h2*u1p,
     w2 = u0p*w1 - l0p, v0p = w2*w3 - v0 - h0 + h2*u0p
  */
   w1 = l2p - u1p; 
   w2 = u1p*w1 + u0p - l1p;
   v1p = w2*w3 - v1 - h1 + h2*u1p;
   w2 = u0p*w1 - l0p;
   v0p = w2*w3 - v0 - h0 + h2*u0p;

  /* Step 10:
     return [up, vp]
  */
  SetCoeff(up, 2, 1);
  SetCoeff(up, 1, u1p);
  SetCoeff(up, 0, u0p);

  SetCoeff(vp, 1, v1p);
  SetCoeff(vp, 0, v0p);

  x.set_upoly(up); 
  x.set_vpoly(vp);

  x.update();

#if DEBUG_LEVEL > 1
  cout << "Entered doubling(). " << endl;
  //  cout << x << endl;
#endif

  assert(OK = OK && x.is_valid_divisor());
  return OK;
}

bool_t add(divisor& x, const divisor& a, const divisor& b)
     // This subroutine wraps other functions that does the actual
     // divisor arithmetic. It checks the validity of input divisors
     // so that other subroutines it calls do not need to do so.
{
  bool_t OK = TRUE;


  /* Reduce overhead of checking with NDEBUG flag */
  assert(OK = OK && a.is_valid_divisor() && b.is_valid_divisor());

  if (deg(a.get_upoly()) == genus && deg(b.get_upoly()) == genus) {

    if (a == - b) {
      x.set_unit();
      OK = TRUE;
      return OK;
    }

    if (a != b && IsOne(GCD(a.get_upoly(), b.get_upoly()))) { 
      // Addition 
      OK = OK && add_diff(x, a, b);
      return OK;

    } else if (a == b && IsOne(GCD(a.get_curve().get_h() + 
                            2*a.get_vpoly(), a.get_upoly())) ) { 
      // Doubling
      // Exclude the case when one point of the divisor is equal to 
      // its opposite

      OK = OK && doubling(x, a);
      return OK;
    }


  }

   // Call add_cantor() to handle other cases
  OK = OK && add_cantor(x, a, b);
  
  return OK;
}

NS_G2_END_IMPL
