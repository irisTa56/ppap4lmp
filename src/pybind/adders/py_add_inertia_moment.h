/*!
  @file src/pybind/py_adders/add_inertia_moment.h
  @brief This file has a function to bind AddInertiaMoment class to
  Python.
  @author Takayuki Kobayashi
  @date 2018/07/15
  @details

  <b>Python-side constructor of AddInertiaMoment class</b>:
  <table class="py_table">
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %AddInertiaMoment</td>
      <td class="py_td">AddInertiaMoment::AddInertiaMoment</td>
      <td class="py_td">
        Constructor of AddInertiaMoment class.
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
        Constructed AddInertiaMoment object.
      </td>
    </tr>
  </table>
*/

#ifndef PYBIND_ADD_INERTIA_MOMENT_H
#define PYBIND_ADD_INERTIA_MOMENT_H

#include <adders/add_inertia_moment.h>
#include <pybind/adders/py_adder.h>

/*!
  @brief Function to bind AddInertiaMoment class to Python.
*/
static void pybind_add_inertia_moment(py::module &m)
{
  py::class_<AddInertiaMoment,PyUpdater<AddInertiaMoment>,Adder,Updater,ShPtr<AddInertiaMoment>>(m, "AddInertiaMoment")
    .def(py::init<const ElPtr &>());
}

#endif