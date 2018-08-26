/* ---------------------------------------------------------------------
Filter: is an abstract class to filter data.

create: 2018/06/30 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "filter.h"
#include "../utils/message.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

Filter::Filter(
  const ShPtr<Element> &elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void Filter::compute(
  Json &data,
  DataKeys &datakeys,
  const int dataid)
{
  if (check_blacklist(dataid))
  {
    if (ext_generator)
    {
      if (data != nullptr)
      {
        ut::warning("Non-empty data will be overwritten");
      }

      auto elem = ext_generator->get_element();
      data = elem->get_data();
      datakeys = elem->get_keys();
    }

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
