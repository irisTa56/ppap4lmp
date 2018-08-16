/* ---------------------------------------------------------------------
Filter: is an abstract class to filter data.

create: 2018/06/30 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef FILTER_H
#define FILTER_H

#include "updater.h"

class Filter : public Updater {
 public:
  Filter() = default;
  Filter(ShPtr<GenElement>);
  virtual ~Filter() = default;
  virtual void compute(Json &, Set<Str> &, int) override;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_filter(py::module &m)
{
  py::class_<
    Filter,PyUpdater<Filter>,Updater,ShPtr<Filter>>(m, "Filter")
    .def(py::init<>())
    .def(py::init<ShPtr<GenElement>>());
}

#endif