/* ---------------------------------------------------------------------
Updater: is an abstract class to update data held by Generator.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "updater.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

const bool Updater::check_blacklist(int dataid)
{
  bool is_called = true;

  omp_set_lock(&omp_lock);

  if (dataid_blacklist.find(dataid) == dataid_blacklist.end())
  {
    dataid_blacklist.insert(dataid);
    is_called = false;
  }

  omp_unset_lock(&omp_lock);

  return is_called;
}

/* ------------------------------------------------------------------ */

void Updater::remove_from_blacklist(int dataid)
{
  omp_set_lock(&omp_lock);

  dataid_blacklist.erase(dataid);

  omp_unset_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */
// assumed to be called by only GenElement::append_updater
ShPtr<Generator> Updater::get_ext_generator()
{
  return ext_generator;
}
