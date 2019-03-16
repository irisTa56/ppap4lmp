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
  const ElPtr &elem,
  DataKeys &datakeys,
  const int dataid)
{
  auto &data = elem->get_mutable_data();

  if (check_blacklist(dataid))
  {
    if (data == nullptr)
    {
      ut::runtime_error("Adder accepts nonempty data only");
    }

    auto id_exists = elem->optional("id");

    Str myclassname
      = abi::__cxa_demangle(typeid(*this).name(), 0, 0, new int());

    elem->set_checking_classname(myclassname);
    make_required(elem);
    make_optional(elem);

    if (ext_generator)
    {
      ext_generator->set_checking_classname(myclassname);
    }

    compute_impl(data, datakeys);

    if (id_exists != elem->optional("id"))
    {
      ut::runtime_error("Adder cannot add 'id'");
    }
  }
}

/* ------------------------------------------------------------------ */
