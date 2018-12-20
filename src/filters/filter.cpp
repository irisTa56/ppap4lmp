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
  Json &data,
  DataKeys &datakeys,
  const int dataid)
{
  if (check_blacklist(dataid))
  {
    if (data.is_array())
    {
      Str myclassname
        = abi::__cxa_demangle(typeid(*this).name(), 0, 0, new int());

      datakeys.set_checking_classname(myclassname);

      compute_impl(data, datakeys);

      datakeys.unset_checking_classname();
    }
    else
    {
      ut::warning("Non-array data will not be filtered");
    }
  }
}

/* ------------------------------------------------------------------ */
