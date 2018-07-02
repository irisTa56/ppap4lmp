/* ---------------------------------------------------------------------
FilComparison: stands for Filter using signs of Comparison.

create: 2018/07/02 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "fil_comparison.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(DictOfComparison comps)
{
  for (const auto &item : comps)
  {
    comp_functions[item.first] = make_lambda(item.second);
  }
}

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  std::shared_ptr<Generator> gen, DictOfComparison comps) : Filter(gen)
{
  for (const auto &item : comps)
  {
    comp_functions[item.first] = make_lambda(item.second);
  }
}

/* ------------------------------------------------------------------ */

void FilComparison::compute_impl(nlohmann::json &data)
{
  nlohmann::json tmp;

  int length = data.size();

  for (int i = 0; i != length; ++i)
  {
    auto d = data[i];
    bool pass = true;

    for (const auto &item : comp_functions)
    {
      if (!item.second(d[item.first]))
      {
        pass = false;
        break;
      }
    }

    if (pass)
    {
      tmp.push_back(d);
    }
  }

  data.swap(tmp);
}

/* ------------------------------------------------------------------ */

const CompFunction FilComparison::make_lambda(const Comparison &item)
{
  auto rval = item.second;

  if (item.first == "<")
  {
    return [rval](const nlohmann::json &j) {
      return j < rval ? true : false;
    };
  }
  else if (item.first == ">")
  {
    return [rval](const nlohmann::json &j) {
      return j > rval ? true : false;
    };
  }
  else if (item.first == "<=")
  {
    return [rval](const nlohmann::json &j) {
      return j <= rval ? true : false;
    };
  }
  else if (item.first == ">=")
  {
    return [rval](const nlohmann::json &j) {
      return j >= rval ? true : false;
    };
  }
  else if (item.first == "==")
  {
    return [rval](const nlohmann::json &j) {
      return j == rval ? true : false;
    };
  }
  else if (item.first == "!=")
  {
    return [rval](const nlohmann::json &j) {
      return j != rval ? true : false;
    };
  }
  else
  {
    runtime_error("FilComparison supports six operators: '<', '>', '<=', '>=', '==' and '!='");
  }
}
