/* ---------------------------------------------------------------------
Adder: is an abstract class to add new properties to data in Generator.

create: 2018/06/24 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "adder.h"

/* ------------------------------------------------------------------ */

void Adder::compute(nlohmann::json &data, const std::string &dataname)
{
  if (dataname_blacklist.find(dataname) == dataname_blacklist.end())
  {
    dataname_blacklist.insert(dataname);
    compute_impl(data);
  }
}