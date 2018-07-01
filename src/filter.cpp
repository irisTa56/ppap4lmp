/* ---------------------------------------------------------------------
Filter: is an abstract class to filter data.

create: 2018/06/30 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "filter.h"

#include "utils.h"

/* ------------------------------------------------------------------ */

Filter::Filter(std::shared_ptr<Generator> gen)
{
  reference_generator = gen;
}

/* ------------------------------------------------------------------ */

void Filter::compute(nlohmann::json &data)
{
  if (data == nullptr && reference_generator)
  {
    data = reference_generator->get_data();
  }

  if (data.is_array() && !is_called)
  {
    is_called = true;
    compute_impl(data);
  }
  else if (!data.is_array())
  {
    message("Non-array data will not be filtered");
  }
}

/* ------------------------------------------------------------------ */

const bool Filter::is_callable(const std::string &datatype)
{
  if (reference_generator)
  {
    message(
      "Filter constructed with Generator must be initial updater");

    return false;
  }
  else if (datatype == "Element")
  {
    return false;
  }

  return true;
}

/* ------------------------------------------------------------------ */

const bool Filter::is_callable_as_initializer(std::string &datatype)
{
  if (!reference_generator)
  {
    message(
      "Filter constructed without Generator cannot be initial updater");

    return false;
  }

  if (datatype == "Element")
  {
    datatype = reference_generator->get_datatype();
    return true;
  }

  return false;
}
