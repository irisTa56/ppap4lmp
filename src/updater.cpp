/* ---------------------------------------------------------------------
Updater: is an abstract class to update data held by Generator.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "updater.h"

/* ------------------------------------------------------------------ */

const bool Updater::is_callable(const std::string &classname)
{
  return false;
}

/* ------------------------------------------------------------------ */

const bool Updater::is_callable_as_initializer(std::string &classname)
{
  return false;
}

/* ------------------------------------------------------------------ */

const std::shared_ptr<Generator> Updater::get_generator()
{
  return reference_generator;
}
