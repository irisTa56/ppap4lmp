/* ---------------------------------------------------------------------
Adder: is an abstract class to add new properties to data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "adder.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void Adder::compute(
  Json &data,
  Set<Str> &datakeys,
  int dataid)
{
  if (check_blacklist(dataid))
  {
    if (data == nullptr)
    {
      runtime_error("Adder accepts nonempty data only");
    }

    compute_impl(data, datakeys);
  }
}