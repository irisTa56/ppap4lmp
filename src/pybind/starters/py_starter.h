/*!
  @file src/pybind/starters/py_starter.h
  @brief This file is for binding Starter class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef PYBIND_STARTER_H
#define PYBIND_STARTER_H

#include <starters/starter.h>
#include <pybind/py_updater.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind Starter class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    Constructor of Starter class is hidden from Python,
    because the class is an abstract one.
  */
  void py_starter(py::module &m);
}

#endif