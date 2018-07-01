/* ---------------------------------------------------------------------
Starter: is an abstract class to parse data from a file or other data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "starter.h"

/* ------------------------------------------------------------------ */

void Starter::compute(nlohmann::json &data)
{
  if (data == nullptr)
  {
    compute_impl(data);
  }
}

/* ------------------------------------------------------------------ */

const bool Starter::is_callable_as_initializer(std::string &datatype)
{
  if (datatype == "Element")
  {
    datatype = datatype_to_be_initialized;
    return true;
  }
  else
  {
    return false;
  }
}
