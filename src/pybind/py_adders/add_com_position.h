/*!
  @file src/pybind/py_adders/add_com_position.h
  @brief This file has a function to bind AddCoMPosition class to
  Python.
  @author Takayuki Kobayashi
  @date 2018/07/13
  @details

  <b>Python-side constructor of AddCoMPosition class</b>:
  <table class="py_table">
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %AddCoMPosition</td>
      <td class="py_td">AddCoMPosition::AddCoMPosition</td>
      <td class="py_td">
        Constructor of AddCoMPosition class.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c elem : An Element object, which is used for creating
            another Element object where the constructed object is
            appended to. For example, the former Element object is the
            one containing atoms data, and the latter is the one
            containing molecules data generated using the atoms.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed AddCoMPosition object.
      </td>
    </tr>
  </table>
*/

#ifndef PYBIND_ADD_COM_POSITION_H
#define PYBIND_ADD_COM_POSITION_H

#include <adders/add_com_position.h>
#include <pybind/py_adders/adder.h>

/*!
  @brief Function to bind AddCoMPosition class to Python.
*/
static void pybind_add_com_position(py::module &m)
{
  py::class_<AddCoMPosition,PyUpdater<AddCoMPosition>,Adder,Updater,ShPtr<AddCoMPosition>>(m, "AddCoMPosition")
    .def(py::init<const ElPtr &>());
}

#endif