/*!
  @file src/pybind/adders/py_add_child_positions.h
  @brief This file is for binding AddChildPositions class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef PYBIND_ADD_CHILD_POSITIONS_H
#define PYBIND_ADD_CHILD_POSITIONS_H

#include <adders/add_child_positions.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddChildPositions class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddChildPositions
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddChildPositions::AddChildPositions
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief AddChildPositions::AddChildPositions
          @copydetails AddChildPositions::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails AddChildPositions::AddChildPositions
        </td>
      </tr>
    </table>
  */
  void py_add_child_positions(py::module &m);
}

#endif