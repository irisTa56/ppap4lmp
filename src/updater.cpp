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

void Updater::remove_from_blacklist(const std::string &dataname)
{
  omp_set_lock(&omp_lock);

  dataname_blacklist.erase(dataname);

  omp_unset_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

const std::shared_ptr<Generator> Updater::get_generator()
{
  return reference_generator;
}

/* ------------------------------------------------------------------ */

const bool Updater::check_blacklist(const std::string &dataname)
{
  bool is_called = true;

  omp_set_lock(&omp_lock);

  if (dataname_blacklist.find(dataname) == dataname_blacklist.end())
  {
    dataname_blacklist.insert(dataname);
    is_called = false;
  }

  omp_unset_lock(&omp_lock);

  return is_called;
}
