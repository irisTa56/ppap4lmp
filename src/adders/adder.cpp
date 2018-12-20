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

void Adder::compute(
  Json &data,
  DataKeys &datakeys,
  const int dataid)
{
  if (check_blacklist(dataid))
  {
    if (data == nullptr)
    {
      ut::runtime_error("Adder accepts nonempty data only");
    }

    auto id_exists = datakeys.optional("id");

    datakeys.set_checking_classname(
      abi::__cxa_demangle(typeid(*this).name(), 0, 0, new int()));

    compute_impl(data, datakeys);

    datakeys.unset_checking_classname();

    if (id_exists != datakeys.optional("id"))
    {
      ut::runtime_error("Adder cannot add 'id'");
    }
  }
}

/* ------------------------------------------------------------------ */
