/* ---------------------------------------------------------------------
FilComparison: stands for Filter using signs of Comparison.

create: 2018/07/02 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef FIL_COMPARISON_H
#define FIL_COMPARISON_H

#include "filter.h"

using CompareFunc = std::function<bool(const Json &)>;

class FilComparison : public Filter {
  List<std::pair<Str,CompareFunc>> compare_funcs;
  const CompareFunc make_lambda(const Str &, const Json &);
  const List<std::pair<Str,CompareFunc>> convert_to_funcs(
    const List<std::tuple<Str,Str,Json>> &);
 protected:
  virtual void compute_impl(Json &, Set<Str> &) override;
 public:
  FilComparison(const std::tuple<Str,Str,Json> &);
  FilComparison(const List<std::tuple<Str,Str,Json>> &);
  FilComparison(
    ShPtr<GenElement>, const std::tuple<Str,Str,Json> &);
  FilComparison(
    ShPtr<GenElement>, const List<std::tuple<Str,Str,Json>> &);
  virtual ~FilComparison() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_fil_comparison(py::module &m)
{
  py::class_<FilComparison,PyUpdater<FilComparison>,Filter,Updater,ShPtr<FilComparison>>(m, "FilComparison")
    .def(py::init<const std::tuple<Str,Str,Json> &>())
    .def(py::init<const List<std::tuple<Str,Str,Json>> &>())
    .def(py::init<ShPtr<GenElement>,const std::tuple<Str,Str,Json> &>())
    .def(py::init<ShPtr<GenElement>,const List<std::tuple<Str,Str,Json>> &>());
}

#endif