/* Divisor negation */

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
#include <g2hec_Genus2_ops.h>

NS_G2_START_IMPL

bool_t dnegate(divisor& x, const divisor& a)
     // x + a = [1, 0]
{
  bool_t OK = a.is_valid_divisor();

  assert(OK);

  poly_t u = a.get_upoly(), v = a.get_vpoly();

  x.set_upoly(u);

  x.set_vpoly( (-v - a.get_curve().get_h()) % u );

  x.update();

  assert(x.is_valid_divisor());

  return OK;
}

NS_G2_END_IMPL
