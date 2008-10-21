/*++
    g2hec_rand.C: created 2008-09-03
--*/

#include <g2hec_rand.h>

NS_G2_START_IMPL

ZZ g2hec_rand()
{
  int fh;
  unsigned char seed_c[SEED_NBYTES]; // 128-bit buffer
  ZZ  seedZZ;

  fh = open("/dev/urandom", O_RDONLY);
  if ( fh == -1 )
    return ZZ::zero();
   
  if ( read(fh, seed_c, SEED_NBYTES) != SEED_NBYTES )
    return ZZ::zero();

  close(fh);

  ZZFromBytes(seedZZ, seed_c, SEED_NBYTES);

  return seedZZ;
}

NS_G2_END_IMPL
