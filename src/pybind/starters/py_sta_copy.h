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
    @details
    <table class="py_table">
      <caption>
        Python-side constructor of StaCopy
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %StaCopy</td>
        <td class="py_td">StaCopy::StaCopy</td>
        <td class="py_td">
          Constructor of StaCopy class.
        </td>
        <td class="py_td">
          - \c elem : An Element object to be copied.
        </td>
        <td class="py_td">
          Constructed StaCopy object.
        </td>
      </tr>
    </table>
  */
  void py_sta_copy(py::module &m);
}

#endif