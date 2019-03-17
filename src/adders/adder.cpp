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
  Json &data,
  const int dataid)
{
  if (check_blacklist(dataid))
  {
    if (data == nullptr)
    {
      ut::runtime_error("Adder accepts nonempty data only");
    }

    auto id_exists = elem->optional_keys("id");

    Str myclassname
      = abi::__cxa_demangle(typeid(*this).name(), 0, 0, new int());

    elem->talk_with(myclassname);

    if (ext_generator)
    {
      ext_generator->talk_with(myclassname);
    }

    make_required_keys(elem);
    make_optional_keys(elem);

    compute_impl(data);

    elem->update_keys();

    if (id_exists != elem->optional_keys("id"))
    {
      ut::runtime_error("Adder cannot add 'id'");
    }
  }
}

/* ------------------------------------------------------------------ */
