/* ---------------------------------------------------------------------
FilSet: stands for Filter using Set of values.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "fil_set.h"

#include "utils.h"

/* ------------------------------------------------------------------ */

FilSet::FilSet(DictOfJsonSet value_sets_)
{
  value_sets = value_sets_;
}

/* ------------------------------------------------------------------ */

FilSet::FilSet(
  std::shared_ptr<Generator> gen, DictOfJsonSet value_sets_) : Filter(gen)
{
  value_sets = value_sets_;
}

/* ------------------------------------------------------------------ */

void FilSet::compute_impl(nlohmann::json &data)
{
  for (auto it = data.begin(); it != data.end(); ++it)
  {
    for (const auto &item : value_sets)
    {
      auto set = item.second;

      if (set.find((*it)[item.first]) == set.end())
      {
        data.erase(it);
        it--;
      }
    }
  }
}
