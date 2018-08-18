/* ---------------------------------------------------------------------
FilComparison: stands for Filter using signs of Comparison.

create: 2018/07/02 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "fil_comparison.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  const std::tuple<Str,Str,Json> &comp)
{
  compare_funcs = convert_to_funcs({comp});
}

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  const List<std::tuple<Str,Str,Json>> &comps)
{
  compare_funcs = convert_to_funcs(comps);
}

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  ShPtr<GenElement> elem,
  const std::tuple<Str,Str,Json> &comp) : Filter(elem)
{
  compare_funcs = convert_to_funcs({comp});
}

/* ------------------------------------------------------------------ */

FilComparison::FilComparison(
  ShPtr<GenElement> elem,
  const List<std::tuple<Str,Str,Json>> &comps) : Filter(elem)
{
  compare_funcs = convert_to_funcs(comps);
}

/* ------------------------------------------------------------------ */

const CompareFunc FilComparison::make_lambda(
  const Str &oper, const Json &rval)
{
  if (oper == "<")
  {
    return [rval](const Json &j) {
      return j < rval ? true : false;
    };
  }
  else if (oper == ">")
  {
    return [rval](const Json &j) {
      return j > rval ? true : false;
    };
  }
  else if (oper == "<=")
  {
    return [rval](const Json &j) {
      return j <= rval ? true : false;
    };
  }
  else if (oper == ">=")
  {
    return [rval](const Json &j) {
      return j >= rval ? true : false;
    };
  }
  else if (oper == "==")
  {
    return [rval](const Json &j) {
      return j == rval ? true : false;
    };
  }
  else if (oper == "!=")
  {
    return [rval](const Json &j) {
      return j != rval ? true : false;
    };
  }
  else
  {
    runtime_error(
      "FilComparison supports six operators: "
      "'<', '>', '<=', '>=', '==' and '!='");
    return CompareFunc();
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

void FilComparison::compute_impl(Json &data, Set<Str> &datakeys)
{
  for (const auto &item : compare_funcs)
  {
    if (!check_containment<Str>(datakeys, item.first))
    {
      runtime_error(
        "FilComparison cannot use nonexistent property: " + item.first);
      return;
    }
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
