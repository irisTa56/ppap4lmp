/* ---------------------------------------------------------------------
Adder: is an abstract class to add new properties to data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "adder.h"

/* ------------------------------------------------------------------ */

void Adder::compute(json &data, const std::string &dataname)
{
  if (data != nullptr && !check_blacklist(dataname))
  {
    compute_impl(data);
  }
}

/* ------------------------------------------------------------------ */

const bool Adder::is_callable(const std::string &datatype)
{
  if (
    !callable_datatypes.empty()
    && callable_datatypes.find(datatype) == callable_datatypes.end())
  {
    return false;
  }

  return true;
}