/*!
  @file src/pybind/adders/py_add_wrapped_position.h
  @brief This file is for binding AddWrappedPosition class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/07
  @details

  <table class="py_table">
    <caption>
      Python-side constructor of AddWrappedPosition
    </caption>
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %AddWrappedPosition</td>
      <td class="py_td">AddWrappedPosition::AddWrappedPosition</td>
      <td class="py_td">
        Constructor of AddWrappedPosition class.
      </td>
      <td class="py_td">
        - \c elem : An Element object containing data for
          the simulation box.
      </td>
      <td class="py_td">
        Constructed AddWrappedPosition object.
      </td>
    </tr>
  </table>
*/

#ifndef PYBIND_ADD_WRAPPED_POSITION_H
#define PYBIND_ADD_WRAPPED_POSITION_H

#include <adders/add_wrapped_position.h>
#include <pybind/adders/py_adder.h>

//! Function to bind AddWrappedPosition class to Python.
static void pybind_add_wrapped_position(py::module &m)
{
  py::class_<AddWrappedPosition,PyUpdater<AddWrappedPosition>,Adder,Updater,ShPtr<AddWrappedPosition>>(m, "AddWrappedPosition")
    .def(py::init<const ElPtr &>());
}

#endif