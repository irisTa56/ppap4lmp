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

void Filter::compute(nlohmann::json &data, const std::string &dataname)
{
  if (data == nullptr && reference_generator)
  {
    data = reference_generator->get_data();
  }

  if (data.is_array() && !check_blacklist(dataname))
  {
    compute_impl(data);
  }
  else if (!data.is_array())
  {
    message("Non-array data will not be filtered");
  }
}

/* ------------------------------------------------------------------ */

void Filter::initialize_datatype(std::string &datatype)
{
  if (!reference_generator)
  {
    runtime_error(
      "Filter constructed without Generator cannot be initial updater");
  }

  if (datatype.empty())
  {
    datatype = reference_generator->get_datatype();
  }
  else
  {
    runtime_error("Generator's datatype is already set");
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

  return true;
}
