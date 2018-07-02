/* ---------------------------------------------------------------------
FilComparison: stands for Filter using signs of Comparison.

create: 2018/07/02 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef FIL_COMPARISON_H
#define FIL_COMPARISON_H

#include "filter.h"

using Comparison = std::pair<std::string,nlohmann::json>;
using CompFunction = std::function<bool(const nlohmann::json &)>;
using DictOfComparison = std::unordered_map<std::string,Comparison>;

class FilComparison : public Filter {
 public:
  FilComparison(DictOfComparison);
  FilComparison(std::shared_ptr<Generator>, DictOfComparison);
  virtual ~FilComparison() = default;
 protected:
  virtual void compute_impl(nlohmann::json &) override;
 private:
  std::unordered_map<std::string,CompFunction> comp_functions;
  const CompFunction make_lambda(const Comparison &);
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_fil_comparison(py::module &m)
{
  py::class_<FilComparison,PyUpdater<FilComparison>,Filter,Updater,std::shared_ptr<FilComparison>>(m, "FilComparison")
    .def(py::init<DictOfComparison>())
    .def(py::init<std::shared_ptr<Generator>,DictOfComparison>());
}

#endif