/*!
  @file src/pybind/filters/py_filter.h
  @brief This file is for binding Filter class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/30
*/

#ifndef PYBIND_FILTER_H
#define PYBIND_FILTER_H

#include <filters/filter.h>
#include <pybind/py_updater.h>

/*!
  @brief Function to bind Filter class to Python.
  @details Constructor of Filter class is hidden from Python,
  because the class is an abstract one.
*/
static void pybind_filter(py::module &m)
{
  py::class_<
    Filter,PyUpdater<Filter>,Updater,ShPtr<Filter>>(m, "Filter")
    .def(py::init<>());
}

#endif