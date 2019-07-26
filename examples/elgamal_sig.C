/* Example: local ElGamal signature */

/* The following data are from the paper "Construction of Secure Random Curves
 * of Genus 2 over Prime Fields" by Gaudry and Schost. 
 *
 * Use curve C: y^2 =  x^5 + 2682810822839355644900736 * x3 
 + 226591355295993102902116 * x2 + 2547674715952929717899918 * x 
 + 4797309959708489673059350.
 * with 
 * p = 5*10^24 + 8503491

 * The Jacobian of this curve has a prime order
 * N = 24999999999994130438600999402209463966197516075699 (164bit).
 * We shall choose a nonunit point g of this order on the Jacobian to be the 
 * base point.

 */

#include <g2hec_nsfieldtype.h>
#include <g2hec_Genus2_ops.h>
#include <unistd.h>

#define f3 "2682810822839355644900736"
#define f2 "226591355295993102902116"
#define f1 "2547674715952929717899918"
#define f0 "4797309959708489673059350"
#define ps "5000000000000000008503491"
#define N "24999999999994130438600999402209463966197516075699"

#define str_to_ZZ_p(x) to_ZZ_p(to_ZZ(x))

NS_G2_CLIENT

/* An almost bijection from Jacobian to {1, 2, ..., n-1} 
 * which maps [u(x), v(x)] to u0^2 + u1^2 mod n.
*/
static ZZ from_divisor_to_ZZ(const divisor& div, const ZZ& n)
{
  poly_t u = div.get_upoly();
  ZZ temp = AddMod(sqr(rep(u.rep[0])), sqr(rep(u.rep[1])), n);
  return ( IsZero(temp) ? to_ZZ(1) : temp );
}

int main() 
{
  /* Set PRNG seed */
  SetSeed(to_ZZ(1234567890));

  /* Set prime */
  ZZ p = to_ZZ(ps);

  field_t::init(p); // define GF(p)

  ZZ order = to_ZZ(N);

  ZZ x, k, b, m; // Private key x, random number k, parameter b, message m

  ZZ f_a;

  g2hcurve curve;

  divisor g, h, a;

  poly_t f;

  SetCoeff(f, 5, 1);
  SetCoeff(f, 4, 0);
  SetCoeff(f, 3, str_to_ZZ_p(f3));
  SetCoeff(f, 2, str_to_ZZ_p(f2));
  SetCoeff(f, 1, str_to_ZZ_p(f1));
  SetCoeff(f, 0, str_to_ZZ_p(f0));
  curve.set_f(f);
  curve.update();

  g.set_curve(curve);

  /* Base point g */
  do {
    g.random();
  } while (g.is_unit());

  /* message m */
  RandomBnd(m, order);

  /* private key x <> 0 */
  do {
    RandomBnd(x, order);
  } while (IsZero(x));

  /* public key h = [x]g */
  h = x * g;

  /* random number k <> 0*/
  do {
    RandomBnd(k, order);
  } while (IsZero(k));

  cout << "Generating ElGmal signature..." << endl;
  sleep(3);

  a = k * g;

  f_a = from_divisor_to_ZZ(a, order);

  /* b = (m - x*f(a))/k mod N */
  b = MulMod(m - x * f_a, InvMod(k, order), order);

  cout << "ElGmal signature generated!" << endl;
  sleep(3);

  /* Signature verification */
  if ( f_a * h + b * a == m * g )
    cout << "ElGamal signature verification succeeded!" << endl;
  else
    cout << "ElGamal signature verification failed!" << endl;

   return 0;
}
