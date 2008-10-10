/*++
Module Name: 
   g2hec_NAF.h

Summary:
    A class provding minimum functinality with non-adjacent forms

--*/

#ifndef NS_G2_NAF_H
#define NS_G2_NAF_H

NTL_CLIENT

NS_G2_OPEN_NS

// Nonadjacent form class
class N_A_F {
 private:
  ZZ naf; // Use two bits to store -1, 0, and 1: 
  // 00 -> 0, 10 -> -1, 01 ->1

 public:
  long get(long i) 
    // Get i-th position id
    {
      if ( bit(naf, 2*i) ) return 1; // bit 2*i is set, must be case: 01
      if ( bit(naf, 2*i + 1) ) return -1; // case: 10
      return 0;  // case: 00
    }

  void set(long i, long id)
    // Set i-th position id
    {
      switch( id ) {
      case 1:
        SetBit(naf, 2*i);  
        if ( bit(naf, 2*i + 1) ) SwitchBit(naf, 2*i + 1); // Set 01
        break;

      case -1:
        SetBit(naf, 2*i + 1);  
        if ( bit(naf, 2*i) ) SwitchBit(naf, 2*i); // Set 10
        break;

      case 0:
        if ( bit(naf, 2*i) ) SwitchBit(naf, 2*i); 
        if ( bit(naf, 2*i + 1) ) SwitchBit(naf, 2*i + 1); // Set 00
        break;
      }
    }
}; // End of class N_A_F

NS_G2_CLOSE_NS

#endif /* NS_G2_NAF_H */
