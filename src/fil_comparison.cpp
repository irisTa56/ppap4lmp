/* ---------------------------------------------------------------------
FilComparison: stands for Filter using signs of Comparison.

create: 2018/07/02 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "fil_comparison.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  const std::tuple<Str,Str,Json> &comparison_)
{
  comparisons = {comparison_};
}

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  const List<std::tuple<Str,Str,Json>> &comparisons_)
{
  comparisons = comparisons_;
}

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  ShPtr<GenElement> elem,
  const std::tuple<Str,Str,Json> &comparison_) : Filter(elem)
{
  comparisons = {comparison_};
}

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  ShPtr<GenElement> elem,
  const List<std::tuple<Str,Str,Json>> &comparisons_) : Filter(elem)
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
    runtime_error(
      "FilComparison supports six operators: "
      "'<', '>', '<=', '>=', '==' and '!='");
  }
}

/* ------------------------------------------------------------------ */

const List<std::pair<Str,CompareFunc>> FilComparison::convert_to_funcs(
    const List<std::tuple<Str,Str,Json>> &comps)
{
  List<std::pair<Str,CompareFunc>> tmp;

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
  Set<Str> &datakeys)
{
  auto compare_funcs = convert_to_funcs(comparisons);

  for (const auto &item : compare_funcs)
  {
    check_key(datakeys, item.first);
  }

  Json tmp;

  for (auto &d : data)
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
