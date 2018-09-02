#ifndef PYBIND_FIL_COMPARISON_H
#define PYBIND_FIL_COMPARISON_H

#include <filters/fil_comparison.h>
#include <pybind/filter.h>

static void pybind_fil_comparison(py::module &m)
{
  py::class_<FilComparison,PyUpdater<FilComparison>,Filter,Updater,ShPtr<FilComparison>>(m, "FilComparison")
    .def(py::init<const std::tuple<Str,Str,Json> &>())
    .def(py::init<const List<std::tuple<Str,Str,Json>> &>())
    .def(py::init<ShPtr<Element>,const std::tuple<Str,Str,Json> &>())
    .def(py::init<ShPtr<Element>,const List<std::tuple<Str,Str,Json>> &>());
}

#endif