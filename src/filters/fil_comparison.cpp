/* ---------------------------------------------------------------------
FilComparison: stands for Filter using signs of Comparison.

create: 2018/07/02 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "fil_comparison.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  const std::tuple<Str,Str,Json> &comparison_)
{
  comparisons = {comparison_};
}

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  const Vec<std::tuple<Str,Str,Json>> &comparisons_)
{
  comparisons = comparisons_;
}

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  const ShPtr<Element> &elem,
  const std::tuple<Str,Str,Json> &comparison_) : Filter(elem)
{
  comparisons = {comparison_};
}

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  const ShPtr<Element> &elem,
  const Vec<std::tuple<Str,Str,Json>> &comparisons_) : Filter(elem)
{
  comparisons = comparisons_;
}

/* ------------------------------------------------------------------ */

const CompareFunc FilComparison::make_lambda(
  const Str &oper,
  const Json &rval)
{
  if (oper == "<")
  {
    return [rval](const Json &j) {
      return j < rval;
    };
  }
  else if (oper == ">")
  {
    return [rval](const Json &j) {
      return j > rval;
    };
  }
  else if (oper == "<=")
  {
    return [rval](const Json &j) {
      return j <= rval;
    };
  }
  else if (oper == ">=")
  {
    return [rval](const Json &j) {
      return j >= rval;
    };
  }
  else if (oper == "==")
  {
    return [rval](const Json &j) {
      return j == rval;
    };
  }
  else if (oper == "!=")
  {
    return [rval](const Json &j) {
      return j != rval;
    };
  }
  else
  {
    ut::runtime_error(
      "Supported operators for comparison are "
      "'<', '>', '<=', '>=', '==' and '!='");
  }
}

/* ------------------------------------------------------------------ */

const Vec<std::pair<Str,CompareFunc>> FilComparison::convert_to_funcs(
    const Vec<std::tuple<Str,Str,Json>> &comps)
{
  Vec<std::pair<Str,CompareFunc>> tmp;

  for (const auto &item : comps)
  {
    tmp.push_back(std::make_pair(
      std::get<0>(item),
      make_lambda(std::get<1>(item), std::get<2>(item))));
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

void FilComparison::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  auto compare_funcs = convert_to_funcs(comparisons);

  for (const auto &item : compare_funcs)
  {
    datakeys.required(item.first);
  }

  Json tmp = Json::array();

  for (const auto &d : data)
  {
    bool pass = true;

    for (const auto &item : compare_funcs)
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
