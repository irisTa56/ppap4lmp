/*!
  @file src/pybind/filters/py_fil_comparison.cpp
  @brief This file is for binding FilComparison class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_fil_comparison.h"

void pybind::py_fil_comparison(py::module &m)
{
  py::class_<FilComparison,PyUpdater<FilComparison>,Filter,Updater,ShPtr<FilComparison>>(m, "FilComparison")
    .def(py::init<const std::tuple<Str,Str,Json> &>())
    .def(py::init<const Vec<std::tuple<Str,Str,Json>> &>());
}
