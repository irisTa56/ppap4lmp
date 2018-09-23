/*!
  @file src/pybind/adders/py_adder.h
  @brief This file is for binding Adder class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef PYBIND_ADDER_H
#define PYBIND_ADDER_H

#include <adders/adder.h>
#include <pybind/py_updater.h>


//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind Adder class to Python.
    @param m : A mutable reference to Python module.
    @return None.
    @details Constructor of Adder class is hidden from Python,
    because the class is an abstract one.
  */
  void py_adder(py::module &m);
}

#endif