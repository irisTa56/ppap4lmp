/* ---------------------------------------------------------------------
Adder: is an abstract class to add new properties to data in Generator.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "adder.h"

/* ------------------------------------------------------------------ */

void Adder::compute(nlohmann::json &data)
{
  if (data != nullptr && !is_called)
  {
    compute_impl(data);
    is_called = true;
  }
}