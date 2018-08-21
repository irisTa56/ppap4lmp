/* ---------------------------------------------------------------------
Starter: is an abstract class to parse data from a file or other data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "starter.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void Starter::compute(
  Json &data,
  Set<Str> &datakeys,
  int dataid)
{
  if (check_blacklist(dataid))
  {
    if (data == nullptr)
    {
      compute_impl(data, datakeys);
    }
    else
    {
      runtime_error("Starter accepts empty data only");
    }
  }
}
