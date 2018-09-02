/* ---------------------------------------------------------------------
FilComparison: stands for Filter using signs of Comparison.

create: 2018/07/02 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef FIL_COMPARISON_H
#define FIL_COMPARISON_H

#include <filters/filter.h>

using CompareFunc = std::function<bool(const Json &)>;

class FilComparison : public Filter {
  List<std::tuple<Str,Str,Json>> comparisons;
  const CompareFunc make_lambda(
    const Str &oper,
    const Json &rval);
  const List<std::pair<Str,CompareFunc>> convert_to_funcs(
    const List<std::tuple<Str,Str,Json>> &comps);
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  FilComparison(
    const std::tuple<Str,Str,Json> &comparison_);
  FilComparison(
    const List<std::tuple<Str,Str,Json>> &comparisons_);
  FilComparison(
    ShPtr<GenElement> elem,
    const std::tuple<Str,Str,Json> &comparison_);
  FilComparison(
    ShPtr<GenElement> elem,
    const List<std::tuple<Str,Str,Json>> &comparisons_);
  virtual ~FilComparison() = default;
};

#endif