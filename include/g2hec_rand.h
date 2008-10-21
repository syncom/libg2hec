/*++
Copyright (c) 2008

Module Name:
    g2hec_rand.h

Summary:
    G2HEC's pseudo random number seeding tool.  It first tries to use
    the file /dev/urandom as a source of random bits.  If it fails, 
    then G2HEC falls back to deterministic random number generator.
    Upon successful execution, a seed of 128 bits is returned.

Author:
    Ning Shang 2008-09-03 Created
--*/

#ifndef G2HEC_RAND_H
#define G2HEC_RAND_H

#include <fcntl.h>
#include <NTL/ZZ.h>
#include "g2hec_nstools.h"

#define SEED_NBYTES 16

NTL_CLIENT
NS_G2_OPEN_NS

ZZ g2hec_rand();

NS_G2_CLOSE_NS

#endif /* G2HEC_RAND_H */
