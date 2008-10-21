/* Scalar multiplication routines */

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
#include <g2hec_Genus2_ops.h>
#include <g2hec_NAF.h>

NS_G2_START_IMPL

  bool_t scalar_mul(divisor& x, const divisor& a, const ZZ& n, 
                    bool_t (*method)(divisor&, const divisor&, const ZZ&))
{
  bool_t (*op)(divisor&, const divisor&, const ZZ&) 
    = ( method == NULL ? SAM : method );

  return op(x, a, n);
}
 

bool_t scalar_mul(divisor& x, const divisor& a, long n, 
                  bool_t (*method)(divisor&, const divisor&, const ZZ&))
{
  return scalar_mul(x, a, to_ZZ(n), method);
}


/* Supported scalar multiplication methods */

bool_t SAM(divisor& x, const divisor& a, const ZZ& n)
     // Square and multiply
     // cf. Pg 146, Alg. 9.1 of HOEHCC
{
  assert(a.is_valid_divisor());

  bool_t OK = TRUE;

  long nbits;

  divisor b;

  if (n < 0) { // n < 0
    OK = OK && SAM(x, a, -n);
    OK = OK && dnegate(x, x);
    return OK;
  }

  // n >= 0
  nbits = NumBits(n);
  b.set_unit(); // Set x = unit

  for( --nbits; nbits >= 0; --nbits) {
    OK = OK && add(b, b, b);

    if ( bit(n, nbits) ) 
      OK = OK && add(b, a, b);
  }

  assert(b.is_valid_divisor());

  x = b;  

#if DEBUG_LEVEL > 1
  cout << "SAM visited" << endl;
#endif

  return OK;

}

bool_t NAF(divisor& x, const divisor& a, const ZZ& n)
// Non-adjacent form
// cf. Alg. 9.14 of HOEHCC
{
  assert(a.is_valid_divisor());

  bool_t OK = TRUE;

  long nbits = NumBits(n), ibit;

  long c1, c2, n1, n2;

  divisor b;

  N_A_F naf;

  if ( !nbits ) { // n = 0
    x.set_unit();
    return OK;
  }

  if ( n < 0) {
    OK = OK && NAF(x, a, -n);
    OK = OK && dnegate(x, x);
  } else {
    /* Get NAF first */

    c2 = 0;
    n2 = bit(n, 0);

    for ( ibit = 0; ibit <= nbits; ibit++ ){
      c1 = c2;
      n1 = n2;

      if (ibit == nbits -1 || ibit == nbits)
        n2 = 0;
      else
        n2 = bit(n, ibit + 1);

      c2 = (c1 + n1 + n2)/2;

      naf.set(ibit, c1 + n1 - 2*c2);

    }

    /* Use NAF for computation */
    b.set_unit();

    for ( ibit = nbits; OK && ibit >= 0; --ibit ) {
      OK = OK && add(b, b, b);

      if (naf.get(ibit) == 1)
        OK = OK && add(b, b, a); // b = a + b
      else if (naf.get(ibit) == -1)
        OK = OK && sub(b, b, a); // b = b - a
      // Do nothing otherwise

    } //endfor ibit

  assert(b.is_valid_divisor());

  x = b;

  }

#if DEBUG_LEVEL > 1
  cout << "NAF visited" << endl;
#endif 

  return OK;

}

bool_t ML(divisor& x, const divisor& a, const ZZ& n)
// Montgomery's ladder: used to defend side channel attacks
// cf. Alg. 13.35 of HOEHCC
{
  assert(a.is_valid_divisor());

  bool_t OK = TRUE;

  long nbits = NumBits(n);

  divisor b1, b2;


  if ( !nbits ) { // n = 0
    x.set_unit();
    return OK;
  }

  if ( n < 0) {
    OK = OK && ML(x, a, -n);
    OK = OK && dnegate(x, x);
    return OK;
  }

  // Case n > 0
  b1 = a; b2 = a + a;     
  for ( --nbits; OK && nbits > 0; --nbits) {
    if ( !bit(n, nbits - 1) ) {
      OK = OK && add(b2, b1, b2); // b2 = b1 + b2
      OK = OK && add(b1, b1, b1); // b1 = [2]*b1

    } else { 
      OK = OK && add(b1, b1, b2); // b1 = b1 + b2;
      OK = OK && add(b2, b2, b2); // b2 = [2]*b2;

      assert(OK);  

    }

  }

  assert(b1.is_valid_divisor());
  x = b1;

  return OK;

}

NS_G2_END_IMPL
