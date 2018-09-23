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
    @details
    <table class="py_table">
      <caption>
        Python-side functions
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c log_switch</td>
        <td class="py_td">utils::log_switch</td>
        <td class="py_td">
          Switch on/off logging (logging is disabled by default).
        </td>
        <td class="py_td">
          - \c input : Boolean whether enable the logging or not.
        </td>
        <td class="py_td">
          None.
        </td>
      </tr>
    </table>
  */
  void py_utils(py::module &m);
}

#endif
