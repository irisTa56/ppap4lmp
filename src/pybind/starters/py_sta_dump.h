/*!
  @file src/pybind/starters/py_sta_dump.h
  @brief This file is for binding StaDump class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef PYBIND_STA_DUMP_H
#define PYBIND_STA_DUMP_H

#include <starters/sta_dump.h>
#include <pybind/starters/py_starter.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind StaDump class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    Constructor of StaDump class is hidden from Python,
    because the class is an abstract one.
  */
  void py_sta_dump(py::module &m);
}

#endif