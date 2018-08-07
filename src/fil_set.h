/* ---------------------------------------------------------------------
FilSet: stands for Filter using Set of values.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef FIL_SET_H
#define FIL_SET_H

#include "filter.h"

using DictOfJsonSet
  = std::unordered_map<std::string,std::unordered_set<json>>;

class FilSet : public Filter {
  DictOfJsonSet value_sets;
 protected:
  virtual void compute_impl(json &) override;
 public:
  FilSet(DictOfJsonSet);
  FilSet(std::shared_ptr<Generator>, DictOfJsonSet);
  virtual ~FilSet() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_fil_set(py::module &m)
{
  py::class_<FilSet,PyUpdater<FilSet>,Filter,Updater,std::shared_ptr<FilSet>>(m, "FilSet")
    .def(py::init<DictOfJsonSet>())
    .def(py::init<std::shared_ptr<Generator>,DictOfJsonSet>());
}

#endif