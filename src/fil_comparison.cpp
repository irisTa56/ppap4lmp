/* ---------------------------------------------------------------------
FilComparison: stands for Filter using signs of Comparison.

create: 2018/07/02 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "fil_comparison.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(std::vector<Comparison> comps)
{
  for (const auto &item : comps)
  {
    comp_functions.push_back(std::make_pair(
      std::get<0>(item),
      make_lambda(std::get<1>(item), std::get<2>(item))));
  }
}

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  std::shared_ptr<Generator> gen,
  std::vector<Comparison> comps) : Filter(gen)
{
  for (const auto &item : comps)
  {
    comp_functions.push_back(std::make_pair(
      std::get<0>(item),
      make_lambda(std::get<1>(item), std::get<2>(item))));
  }
}

/* ------------------------------------------------------------------ */

void FilComparison::compute_impl(json &data)
{
  json tmp;

  for (auto &d : data)
  {
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

const CompFunction FilComparison::make_lambda(
  const std::string &oper, const json &rval)
{
  if (oper == "<")
  {
    return [rval](const json &j) {
      return j < rval ? true : false;
    };
  }
  else if (oper == ">")
  {
    return [rval](const json &j) {
      return j > rval ? true : false;
    };
  }
  else if (oper == "<=")
  {
    return [rval](const json &j) {
      return j <= rval ? true : false;
    };
  }
  else if (oper == ">=")
  {
    return [rval](const json &j) {
      return j >= rval ? true : false;
    };
  }
  else if (oper == "==")
  {
    return [rval](const json &j) {
      return j == rval ? true : false;
    };
  }
  else if (oper == "!=")
  {
    return [rval](const json &j) {
      return j != rval ? true : false;
    };
  }
  else
  {
    runtime_error("FilComparison supports six operators: '<', '>', '<=', '>=', '==' and '!='");
  }
}
