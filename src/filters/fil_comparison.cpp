/*!
  @file src/filters/fil_comparison.cpp
  @brief This file has an implementation of FilComparison class,
  which is a subclass of Filter class.
  @author Takayuki Kobayashi
  @date 2018/07/02
*/

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

const Vec<std::pair<Str,CompareFunc>> FilComparison::convert_to_funcs()
{
  Vec<std::pair<Str,CompareFunc>> tmp;

  for (const auto &item : comparisons)
  {
    tmp.push_back(std::make_pair(
      std::get<0>(item),
      make_lambda(std::get<1>(item), std::get<2>(item))));
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

void FilComparison::compute_impl(
  Json &data)
{
  auto compare_funcs = convert_to_funcs();

  for (const auto &item : compare_funcs)
  {
    required(item.first);
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

/* ------------------------------------------------------------------ */
