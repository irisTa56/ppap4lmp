/* ---------------------------------------------------------------------
Adder: is an abstract class to add new properties to data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "adder.h"

/* ------------------------------------------------------------------ */

void Adder::compute(nlohmann::json &data)
{
  if (data != nullptr && !is_called)
  {
    is_called = true;
    compute_impl(data);
  }
}

/* ------------------------------------------------------------------ */

const bool Adder::is_callable(const std::string &datatype)
{
  if (datatype == "Element")
  {
    return false;
  }
  else if (callable_datatypes.size())
  {
    if (callable_datatypes.find(datatype) == callable_datatypes.end())
    {
      return false;
    }
  }

  return true;
}