/*!
  @file src/core/updater.cpp
  @brief This file has an implementation of Updater class,
  which is one of the cores of this program.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#include "updater.h"

/* ------------------------------------------------------------------ */

bool Updater::check_compute_request_for(
  const int elementid)
{
  bool compute_required;

  #pragma omp critical (check_skippable_elementids)
  {
    compute_required
      = skippable_elementids.find(elementid) == skippable_elementids.end();

    if (compute_required)
    {
      skippable_elementids.insert(elementid);
    }
  }

  return compute_required;
}

/* ------------------------------------------------------------------ */

void Updater::compute(
  const ElPtr &elem,
  const int elementid,
  Json &data)
{
  if (check_compute_request_for(elementid))
  {
    compute_body(elem, data);
  }
}

/* ------------------------------------------------------------------ */

void Updater::compute_common(
  const ElPtr &elem,
  Json &data)
{
  Str myclassname
    = abi::__cxa_demangle(typeid(*this).name(), 0, 0, new int());

  elem->accessed_by_instance_of(myclassname);

  if (ext_generator)
  {
    ext_generator->accessed_by_instance_of(myclassname);
  }

  compute_impl(
    data,
    [elem](const Json &key_)
      {
        elem->check_required_keys(key_);
      },
    [elem](const Json &key_)
      {
        return elem->check_optional_keys(key_);
      });
}

/* ------------------------------------------------------------------ */

void Updater::remove_from_skippable_elementids(
  const int elementid)
{
  #pragma omp critical (remove_skippable_elementid)
  {
    skippable_elementids.erase(elementid);
  }
}

/* ------------------------------------------------------------------ */

const ShPtr<Generator> &Updater::get_ext_generator()
{
  return ext_generator;
}
