/*!
  @file src/pybind/adders/py_add_wrapped_position.h
  @brief This file is for binding AddWrappedPosition class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/07
*/

#ifndef PYBIND_ADD_WRAPPED_POSITION_H
#define PYBIND_ADD_WRAPPED_POSITION_H

#include <adders/add_wrapped_position.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddWrappedPosition class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddWrappedPosition
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddWrappedPosition::AddWrappedPosition
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief AddWrappedPosition::AddWrappedPosition
          @copydetails AddWrappedPosition::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails AddWrappedPosition::AddWrappedPosition
        </td>
      </tr>
    </table>
  */
  void py_add_wrapped_position(py::module &m);
}

#endif