/*!
  @file src/pybind/filters/py_filter.cpp
  @brief This file is for binding Filter class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_filter.h"

void pybind::py_filter(py::module &m)
{
  py::class_<
    Filter,PyUpdater<Filter>,Updater,ShPtr<Filter>>(m, "Filter")
    .def(py::init<>());
}
