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
    @details
    <table class="py_table">
      <caption>
        Python-side constructor of StaCustom
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %StaCustom</td>
        <td class="py_td">StaCustom::StaCustom</td>
        <td class="py_td">
          Constructor of StaCustom class.
        </td>
        <td class="py_td">
          - \c json_ : A JSON-like object (complex of \e dict
            and \e list) to be set as Element::data of
            a new Element object.
        </td>
        <td class="py_td">
          Constructed StaCustom object.
        </td>
      </tr>
    </table>
  */
  void py_sta_custom(py::module &m);
}

#endif