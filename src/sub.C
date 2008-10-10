/* Divisor subtraction */

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <g2hec_Genus2_ops.h>

NS_G2_START_IMPL

bool_t sub(divisor& x, const divisor& a, const divisor& b)
{
  divisor c;
  return ( dnegate(c, b) && add(x, a, c) );
}

NS_G2_END_IMPL
