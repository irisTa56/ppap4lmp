/* ---------------------------------------------------------------------
Updater: is an abstract class to update data held by Generator.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "updater.h"
#include "generators.h"
#include "../utils.h"

/* ------------------------------------------------------------------ */

const bool Updater::check_blacklist(
  int dataid)
{
  bool pass = false;

  omp_set_lock(&omp_lock);

  if (!check_containment<int>(dataid_blacklist, dataid))
  {
    dataid_blacklist.insert(dataid);
    pass = true;
  }

  omp_unset_lock(&omp_lock);

  return pass;
}

/* ------------------------------------------------------------------ */

void Updater::remove_from_blacklist(
  int dataid)
{
  omp_set_lock(&omp_lock);

  dataid_blacklist.erase(dataid);

  omp_unset_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */
// assumed to be called by only Element::append_updater
ShPtr<Generator> Updater::get_ext_generator()
{
  return ext_generator;
}
