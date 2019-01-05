/*!
  @file src/pybind/py_utils.h
  @brief This file is for binding utility functions to Python.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef PYBIND_UTILS_H
#define PYBIND_UTILS_H

#include <alias/pybind.h>
#include <utils/message.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind utility functions to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_method">
      <caption class="py_method">
        Python-side utility functions
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">`log_switch`</td>
        <td class="py_method">utils::log_switch</td>
        <td class="py_method">
          @copybrief utils::log_switch
        </td>
        <td class="py_method">
          @copydetails utils::log_switch
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
    </table>
  */
  void py_utils(py::module &m);
}

#endif
