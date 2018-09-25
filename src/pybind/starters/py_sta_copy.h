/*!
  @file src/pybind/starters/py_sta_copy.h
  @brief This file is for binding StaCopy class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/20
*/

#ifndef PYBIND_STA_COPY_H
#define PYBIND_STA_COPY_H

#include <starters/sta_copy.h>
#include <pybind/starters/py_starter.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind StaCopy class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of StaCopy
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          StaCopy::StaCopy
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief StaCopy::StaCopy
          @copydetails StaCopy::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails StaCopy::StaCopy
        </td>
      </tr>
    </table>
  */
  void py_sta_copy(py::module &m);
}

#endif