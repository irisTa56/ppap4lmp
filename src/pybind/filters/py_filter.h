#ifndef PYBIND_FILTER_H
#define PYBIND_FILTER_H

#include <filters/filter.h>
#include <pybind/py_updater.h>

static void pybind_filter(py::module &m)
{
  py::class_<
    Filter,PyUpdater<Filter>,Updater,ShPtr<Filter>>(m, "Filter")
    .def(py::init<>());
}

#endif