/*!
  @file src/filters/filter.cpp
  @brief This file has an implementation of the Filter class, which is
  a subclass of the Updater class.
  @author Takayuki Kobayashi
  @date 2018/06/30
  @details For more details, please see the header file,
  src/filters/filter.h.
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
      compute_impl(data, datakeys);
    }
    else
    {
      ut::warning("Non-array data will not be filtered");
    }
  }
}

/* ------------------------------------------------------------------ */
