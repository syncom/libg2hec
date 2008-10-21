/* Example: local Diffie-Hellman key exchange */
/* Note that because we have a static g2hcurve member s_hcurve in the
divisor class and this memeber may result in chaos when we swith moduli, 
we require that there is only one modulus per process
*/

#include <g2hec_nsfieldtype.h>
#include <assert.h>
#include <g2hec_Genus2_ops.h>

#undef MAX_STRING_LEN 
#define MAX_STRING_LEN 300

NS_G2_CLIENT

int main() 
{
  /* Set PRNG seed */
  SetSeed(to_ZZ(19800729));

  char p[MAX_STRING_LEN];

  cout << "Please choose your modulus p (up to " 
       << MAX_STRING_LEN << " decimal digits):" << endl;
  cout << "p = ";
  cin.getline(p, MAX_STRING_LEN);

  ZZ pZZ = to_ZZ(p);

   field_t::init(pZZ); // define GF(p)

   ZZ a, b;

   g2hcurve curve;

   divisor P, Q1, Q2;

   curve.random();

   P.set_curve(curve);

   RandomBnd(a, pZZ*pZZ);

   RandomBnd(b, pZZ*pZZ);

   /* base point P */
   P.random();

   Q1 = a * P;

   Q2 = b * P;

   if ( b * Q1 == a * Q2 ) 
     cout << "DH key exchange succeeded!" << endl;
   else
     cout << "DH key exchange failed!" << endl;

   return 0;
}
