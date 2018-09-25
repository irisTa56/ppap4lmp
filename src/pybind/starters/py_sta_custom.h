/*!
  @file src/pybind/starters/py_sta_custom.h
  @brief This file is for binding StaCustom class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/16
*/

#ifndef PYBIND_STA_CUSTOM_H
#define PYBIND_STA_CUSTOM_H

#include <starters/sta_custom.h>
#include <pybind/starters/py_starter.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind StaCustom class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of StaCustom
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          StaCustom::StaCustom
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief StaCustom::StaCustom
          @copydetails StaCustom::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails StaCustom::StaCustom
        </td>
      </tr>
    </table>
  */
  void py_sta_custom(py::module &m);
}

#endif