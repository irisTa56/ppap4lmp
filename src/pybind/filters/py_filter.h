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

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind Filter class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    Constructor of Filter class is hidden from Python,
    because the class is an abstract one.
  */
  void py_filter(py::module &m);
}

#endif