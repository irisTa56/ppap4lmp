/*!
  @file src/starters/sta_copy.cpp
  @brief This file has an implementation of StaCopy class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/09/20
*/

#include "sta_copy.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

StaCopy::StaCopy(
  const ElPtr &elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void StaCopy::compute_impl(
  Json &data)
{
  auto elem = ext_generator->get_element();
  data = elem->get_data();
}

/* ------------------------------------------------------------------ */

void StaCopy::compute(
  const ElPtr &elem,
  const int dataid)
{
  auto &data = elem->get_mutable_data();

  if (check_blacklist(dataid))
  {
    if (data == nullptr)
    {
      compute_impl(data);
      elem->update_keys();
    }
    else
    {
      ut::runtime_error("Starter accepts empty data only");
    }
  }
}

/* ------------------------------------------------------------------ */
