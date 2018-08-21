/* ---------------------------------------------------------------------
FilSet: stands for Filter using Set of values.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef FIL_SET_H
#define FIL_SET_H

#include "filter.h"

class FilSet : public Filter {
  Dict<Str,Set<Json>> value_sets;
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  FilSet(
    const Dict<Str,Set<Json>> &value_sets_);
  FilSet(
    ShPtr<GenElement> elem,
    const Dict<Str,Set<Json>> &value_sets_);
  virtual ~FilSet() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_fil_set(py::module &m)
{
  py::class_<FilSet,PyUpdater<FilSet>,Filter,Updater,ShPtr<FilSet>>(m, "FilSet")
    .def(py::init<const Dict<Str,Set<Json>> &>())
    .def(py::init<ShPtr<GenElement>,const Dict<Str,Set<Json>> &>());
}

#endif