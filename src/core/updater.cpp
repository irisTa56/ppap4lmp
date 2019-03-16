/*!
  @file src/core/updater.cpp
  @brief This file has an implementation of Updater class,
  which is one of the cores of this program.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#include "updater.h"

/* ------------------------------------------------------------------ */

Updater::Updater()
{
  omp_init_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

void Updater::make_required_keys(
  const ElPtr &elem)
{
  required_keys = [elem](const Json &key_) {
    elem->required_keys(key_);
  };
}

/* ------------------------------------------------------------------ */

void Updater::make_optional_keys(
  const ElPtr &elem)
{
  optional_keys = [elem](const Json &key_) {
    return elem->optional_keys(key_);
  };
}

/* ------------------------------------------------------------------ */

bool Updater::check_blacklist(
  const int dataid)
{
  bool pass = false;

  omp_set_lock(&omp_lock);

  if (dataid_blacklist.find(dataid) == dataid_blacklist.end())
  {
    dataid_blacklist.insert(dataid);
    pass = true;
  }

  omp_unset_lock(&omp_lock);

  return pass;
}

/* ------------------------------------------------------------------ */

void Updater::remove_from_blacklist(
  const int dataid)
{
  omp_set_lock(&omp_lock);

  dataid_blacklist.erase(dataid);

  omp_unset_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

const ShPtr<Generator> &Updater::get_ext_generator()
{
  return ext_generator;
}

/* ------------------------------------------------------------------ */
