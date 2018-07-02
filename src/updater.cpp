/* ---------------------------------------------------------------------
Updater: is an abstract class to update data held by Generator.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "updater.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void Updater::initialize_datatype(std::string &datatype)
{
  if (!datatype.empty())
  {
    message("Generator's datatype is already set");
  }
}

/* ------------------------------------------------------------------ */

const bool Updater::is_callable(const std::string &datatype)
{
  return false;
}

/* ------------------------------------------------------------------ */

const std::shared_ptr<Generator> Updater::get_generator()
{
  return reference_generator;
}
