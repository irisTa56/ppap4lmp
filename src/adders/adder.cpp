/*!
  @file src/adders/adder.cpp
  @brief This file has an implementation of Adder class,
  which is a subclass of Updater class.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#include "adder.h"
#include "../utils/runtime_error.h"

namespace ut =  utils;

/* ------------------------------------------------------------------ */

void Adder::compute_body(
  const ElPtr &elem,
  Json &data)
{
  if (data == nullptr)
  {
    ut::runtime_error("Adder accepts nonempty data only");
  }

  compute_common(elem, data);

  auto id_exists_before = elem->check_optional_keys("id");

  elem->update_keys();

  auto id_exists_after = elem->check_optional_keys("id");

  if (id_exists_before != id_exists_after)
  {
    ut::runtime_error("Adder cannot add 'id'");
  }
}
