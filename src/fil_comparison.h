/* ---------------------------------------------------------------------
FilComparison: stands for Filter using signs of Comparison.

create: 2018/07/02 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef FIL_COMPARISON_H
#define FIL_COMPARISON_H

#include "filter.h"

using Comparison = std::tuple<std::string,std::string,nlohmann::json>;
using CompFunction = std::function<bool(const nlohmann::json &)>;

class FilComparison : public Filter {
 public:
  FilComparison(std::vector<Comparison>);
  FilComparison(std::shared_ptr<Generator>, std::vector<Comparison>);
  virtual ~FilComparison() = default;
 protected:
  virtual void compute_impl(nlohmann::json &) override;
 private:
  std::vector<std::pair<std::string,CompFunction>> comp_functions;
  const CompFunction make_lambda(
    const std::string &, const nlohmann::json &);
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_fil_comparison(py::module &m)
{
  py::class_<FilComparison,PyUpdater<FilComparison>,Filter,Updater,std::shared_ptr<FilComparison>>(m, "FilComparison")
    .def(py::init<std::vector<Comparison>>())
    .def(py::init<std::shared_ptr<Generator>,std::vector<Comparison>>());
}

#endif