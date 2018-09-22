/*!
  @file src/pybind/starters/py_sta_custom.h
  @brief This file is for binding StaCustom class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/16
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

#ifndef PYBIND_STA_CUSTOM_H
#define PYBIND_STA_CUSTOM_H

#include <starters/sta_custom.h>
#include <pybind/starters/py_starter.h>

//! Function to bind StaCustom class to Python.
static void pybind_sta_custom(py::module &m)
{
  py::class_<StaCustom,PyUpdater<StaCustom>,Starter,Updater,ShPtr<StaCustom>>(m, "StaCustom")
    .def(py::init<const Json &>());
}

#endif