/* ---------------------------------------------------------------------
Starter: is an abstract class to parse data from a file or other data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "starter.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void Starter::compute(json &data, const std::string &dataname)
{
  if (data == nullptr && !check_blacklist(dataname))
  {
    compute_impl(data);
  }
}

/* ------------------------------------------------------------------ */

void Starter::initialize_datatype(std::string &datatype)
{
  if (datatype.empty())
  {
    datatype = datatype_to_be_initialized;
  }
  else
  {
    runtime_error("Generator's datatype is already set");
  }
}
