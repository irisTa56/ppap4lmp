/* ---------------------------------------------------------------------
Filter: is an abstract class to filter data.

create: 2018/06/30 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "filter.h"
#include "../utils.h"

/* ------------------------------------------------------------------ */

Filter::Filter(
  ShPtr<GenElement> elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void Filter::compute(
  Json &data,
  Set<Str> &datakeys,
  int dataid)
{
  if (check_blacklist(dataid))
  {
    if (ext_generator)
    {
      if (data != nullptr)
      {
        message("Non-empty data will be overwritten");
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
      message("Non-array data will not be filtered");
    }
  }
}
