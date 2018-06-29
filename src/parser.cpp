/* ---------------------------------------------------------------------
Parser: is an abstract class to parse data from a file or other
Generators.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "parser.h"

/* ------------------------------------------------------------------ */

void Parser::compute(nlohmann::json &data)
{
  if (data == nullptr)
  {
    compute_impl(data);
  }
}
