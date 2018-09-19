#include "sta_copy.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

StaCopy::StaCopy(
  const ElPtr &elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void StaCopy::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  auto elem = ext_generator->get_element();
  data = elem->get_data();
  datakeys = elem->get_keys();
}

/* ------------------------------------------------------------------ */

void StaCopy::compute(
  Json &data,
  DataKeys &datakeys,
  const int dataid)
{
  if (check_blacklist(dataid))
  {
    if (data == nullptr)
    {
      compute_impl(data, datakeys);
    }
    else
    {
      ut::runtime_error("Starter accepts empty data only");
    }
  }
}

/* ------------------------------------------------------------------ */
