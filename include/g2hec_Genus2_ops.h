/*++

Copyright (c) 2008

Module Name:
    g2hec_Genus2_ops.h

Summary:
    Definitions for genus 2 (imaginary) hyperelliptic curve arithmetic.
    Curves are of the form y^2 + h(x)y = f(x), w/ deg(f)=5.
    The group operations in the Jacobian variety of the curve are implemented
with both explicit formulas and the generic Cantor's algorithm.
    
Author:
    Ning Shang  2008-07-28  Created

Notes:
    TBD
    

--*/

#ifndef GENUS2_OPS_H
#define GENUS2_OPS_H

// The following headers need to be included for initial setup
/* Start include headers */
#include "g2hec_nstools.h"
#include "g2hec_nsfieldtype.h"
/* End include headers */

/* Some types */
//enum bool_t { FALSE = 0, TRUE = 1};
//typedef enum bool_t bool_t;
typedef bool bool_t;
#define FALSE 0
#define TRUE 1

typedef long ndeg_t;

// Divisor degree
enum divdeg_t { DEGREE_1 = 1, DEGREE_2 = 2};
typedef enum divdeg_t divdeg_t;


/* For C++ */
//#ifdef __cplusplus
//extern "C"{
//#endif 

NTL_CLIENT

NS_G2_OPEN_NS

/* genus 2 */
const long genus = 2;

  /* Determine the polynomial type according to field type */
#define DETERMINE_POLY_TYPE 
/* Genus 2 hyperelliptic curve class */
class g2hcurve {
  private:
  poly_t fpoly; // f(x), degree 5 for genus 2

  poly_t hpoly; // h(x), degree <=2 for genus 2

  bool_t is_nonsingular;

  bool_t is_genus_2;

  public:
  g2hcurve()
  : is_nonsingular(FALSE),
    is_genus_2(FALSE)
    { 
      // Default constructor points f, h to polynomial 0
    }

  g2hcurve(const poly_tc& poly1, const poly_tc& poly2) 
  : fpoly(poly1),
    hpoly(poly2)
    { 
      // C-tor
    }

  g2hcurve(const g2hcurve& hcurve) 
  : fpoly(hcurve.fpoly),
    hpoly(hcurve.hpoly),
    is_nonsingular(hcurve.is_nonsingular),
    is_genus_2(hcurve.is_genus_2)
    { 
      // Copy constructor
    }

  g2hcurve& operator=(const g2hcurve& hcurve) // assignment
  {
    if (this == &hcurve) return *this;

    fpoly = hcurve.fpoly;
    hpoly = hcurve.hpoly;
    is_nonsingular = hcurve.is_nonsingular;
    is_genus_2 = hcurve.is_genus_2;
    return *this;
  }

  ~g2hcurve() {} // D-tor

  void set_f(const poly_tc& poly); // Set f(x) for curve

  void set_h(const poly_tc& poly); // Set h(x) for curve

  void update(); // Check and reset is_nonsingular and is_genus_2 flags

  const poly_tc& get_f() const;

  const poly_tc& get_h() const;

  bool_t is_valid_curve() const; // Return TRUE if is_nonsingular && is_genus_2

  g2hcurve& random(); // Generate a random valid curve


};


/* Divisor definition:
a divisor in a Jacobian variety of a genus 2 curve is given by a pair
of polynomials [u(x), v(x)], where deg(u) is at most 2 and deg(v) is at 
most 1.
*/
class divisor {
 private: 
  poly_t upoly;  // degree at most 2

  poly_t vpoly; // degree at most 1

  static g2hcurve s_hcurve; //  underlying curve
  // Defined as a static data member.  Only one curve exists at one time.
  // s_hcurve need to be initialized in implementation. ("divisor.c")

  bool_t is_valid; // Flag if divisor is valid

 public:
  divisor() // Default C-tor. Set u=1, v=0, s_hcurve=default
  : upoly(to_ZZ_pX(1)), 
    vpoly(to_ZZ_pX(0)), 
    is_valid(FALSE)
    {
    
    }

  divisor(const poly_tc& polyu, const poly_tc& polyv, const g2hcurve& curve) 
// C-tor
  : upoly(polyu), 
    vpoly(polyv),
    is_valid(FALSE)
  {
    s_hcurve = curve; // static member
  }


  divisor(const divisor& div) // Copy c-tor
  : upoly(div.upoly), 
    vpoly(div.vpoly),
    is_valid(div.is_valid)
    {
    }

  divisor& operator=(const divisor& div) // Assignment
    { 
      if (this == &div) return *this;

      upoly = div.upoly; vpoly = div.vpoly; is_valid = div.is_valid;
      return *this;
    }

  ~divisor() {};  // D-tor

  void set_upoly(poly_tc& poly) {upoly = poly;} // Set upoly

  void set_vpoly(poly_tc& poly) {vpoly = poly;} // Set vpoly

  void set_curve(const g2hcurve& curve) // Set hcurve
    { divisor::s_hcurve = curve; }

  void update(); // Check and update is_valid flag. Must be called by client
  // after any set_ routine is called

  const poly_tc& get_upoly() const // Get upoly
    { return upoly; }

  const poly_tc& get_vpoly() const // Get vpoly
    { return vpoly; }

  const g2hcurve& get_curve() const // Return curve
    { return s_hcurve; }

  bool_t is_valid_divisor() const; // Return TRUE if s_hcurve.is_valid_curve
  // and [u, v] is an element of the Jacobian of the curve. Client must 
  // call it to check validity of divisor before doing arithmetic.

  bool_t is_unit();

  void set_unit(); 

  divisor& random(); // If s_hcurve is valid, set divisor to a random valid 
                     // divisor of degree 2

  divisor& random(divdeg_t dgr); // If s_hcurve is valid set divisor to a 
                         //random valid divisor of degree dgr. drg takes
                         // value DEGREE_1 or DEGREE_2
};

/******************************************************\
  Divisor Arithmetic
\******************************************************/
/* Procedure version */
  bool_t add_cantor(divisor& x, const divisor& a, const divisor& b);
  // x = a + b via Cantor's algorithm

  bool_t add(divisor& x, const divisor& a, const divisor& b);
  // x = a + b via explicit formulas; execptions are handled by calling
  // add_cantor()

  bool_t sub(divisor& x, const divisor& a, const divisor& b);
  // x = a - b

  bool_t dnegate(divisor& x, const divisor& a);
  // x = -a

  bool_t scalar_mul(divisor& x, const divisor& a, const ZZ& n, 
                    bool_t (*method)(divisor&, const divisor&, const ZZ&));
  // x = [n]*a. The following methods are exported: 
// (1) Square and multiply: SAM
// (2) Non-adjacent form: NAF
// (3) Montgomery's ladder: ML
// When no method is specified, SAM is used as default.

bool_t scalar_mul(divisor& x, const divisor& a, long n, 
                  bool_t (*method)(divisor&, const divisor&, const ZZ&));

/* Supported scalar multiplication methods */
bool_t SAM(divisor& x, const divisor& a, const ZZ& n);
     // Square and multiply

bool_t NAF(divisor& x, const divisor& a, const ZZ& n);
// Non-adjacent form

bool_t ML(divisor& x, const divisor& a, const ZZ& n);
// Montgomery's ladder



/* Operator version */
  inline divisor operator+(const divisor& a, const divisor& b)
  {divisor x; add(x, a, b); return x;}

  inline divisor operator-(const divisor& a, const divisor& b)
  {divisor x; sub(x, a, b); return x;}

  inline divisor operator-(const divisor& a)
  {divisor x; dnegate(x, a); return x;}

  inline divisor operator*(long n, const divisor& a)
  {divisor x; scalar_mul(x, a, n, NULL); return x;}

  inline divisor operator*(const divisor& a, long n)
  {divisor x; scalar_mul(x, a, n, NULL); return x;}

  inline divisor operator*(const ZZ& n, const divisor& a)
  {divisor x; scalar_mul(x, a, n, NULL); return x;}

  inline divisor operator*(const divisor& a, const ZZ& n)
  {divisor x; scalar_mul(x, a, n, NULL); return x;}

/******************************************************\
  Comparisons
\******************************************************/
inline bool_t operator==(const g2hcurve& a, const g2hcurve& b)
{
  return (a.get_f() == b.get_f() && a.get_h() == b.get_h());
}

inline bool_t operator!=(const g2hcurve& a, const g2hcurve& b)
{
  return (!(a==b));
}

inline bool_t on_same_curve(const divisor& a, const divisor& b)
       // Return TRUE if a and b have the same underlying curve
       // Since the g2hcurve data member is implemented as static,
     // this is always true. This function is not needed.
     
 //{return ( a.get_curve() == b.get_curve() );}
{return TRUE;}

  inline bool_t operator==(const divisor& a, const divisor& b)
  {
    return (on_same_curve(a, b) && 
           a.get_upoly() == b.get_upoly() && 
            a.get_vpoly() == b.get_vpoly());
   }

  inline bool_t operator!=(const divisor& a, const divisor& b)
  {
    return ( !(a == b) );
  }

/******************************************************\
  I/O
\******************************************************/
/* Print polynomial */
void print_poly(poly_tc& poly, std::ostream* s);

/* Print curve */
  std::ostream& operator<<(std::ostream& s, const g2hcurve& a);

/* Print divisor */
  std::ostream& operator<<(std::ostream& s, const divisor& a);



NS_G2_CLOSE_NS

//#ifdef __cplusplus
//}
//#endif

#endif /* GENUS2_OPS_H */
