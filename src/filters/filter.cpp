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

void Filter::compute_body(
  const ElPtr &elem,
  Json &data)
{
  if (data.is_array())
  {
    compute_common(elem, data);
  }
  else
  {
    ut::warning("Non-array data will not be filtered");
  }
}
