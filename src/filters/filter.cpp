/*!
  @file src/filters/filter.cpp
  @brief This file has an implementation of Filter class,
  which is a subclass of Updater class.
  @author Takayuki Kobayashi
  @date 2018/06/30
*/

#include "filter.h"
#include "../utils/message.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

void Filter::compute(
  const ElPtr &elem,
  DataKeys &datakeys,
  const int dataid)
{
  auto &data = elem->get_mutable_data();

  if (check_blacklist(dataid))
  {
    if (data.is_array())
    {
      Str myclassname
        = abi::__cxa_demangle(typeid(*this).name(), 0, 0, new int());

      elem->set_checking_classname(myclassname);
      make_required(elem);
      make_optional(elem);

      compute_impl(data, datakeys);
    }
    else
    {
      ut::warning("Non-array data will not be filtered");
    }
  }
}

/* ------------------------------------------------------------------ */
