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
  const std::tuple<Str,Str,Json> &compare_expr_)
{
  compare_expr_list = {compare_expr_};
}

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  const Vec<std::tuple<Str,Str,Json>> &compare_expr_list_)
{
  compare_expr_list = compare_expr_list_;
}

/* ------------------------------------------------------------------ */

const JsonToBoolFunc FilComparison::make_compare_func(
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

const CompareFuncs FilComparison::make_compare_func_list()
{
  CompareFuncs compare_func_list;

  for (const auto &item : compare_expr_list)
  {
    auto &datakey = std::get<0>(item);
    auto &compare_oper = std::get<1>(item);
    auto &target_val = std::get<2>(item);

    compare_func_list.push_back(std::make_pair(
      datakey, make_compare_func(compare_oper, target_val)));
  }

  return compare_func_list;
}

/* ------------------------------------------------------------------ */

const bool FilComparison::check_if_pass_data_elem(
  const Json &elem_in_data,
  const CompareFuncs &compare_func_list)
{
  for (const auto &item : compare_func_list)
  {
    if (!item.second(elem_in_data[item.first])) return false;
  }

  return true;
}

/* ------------------------------------------------------------------ */

void FilComparison::compute_impl(
  Json &data,
  JsonToVoidFunc check_required_keys,
  JsonToBoolFunc check_optional_keys)
{
  const auto compare_func_list = make_compare_func_list();

  for (const auto &item : compare_func_list)
  {
    check_required_keys(item.first);
  }

  Json remaining_data = Json::array();

  for (const auto &d : data)
  {
    if (check_if_pass_data_elem(d, compare_func_list))
    {
      remaining_data.push_back(d);
    }
  }

  data.swap(remaining_data);
}
