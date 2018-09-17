/*!
  @file src/pybind/adders_py/add_child_ids.h
  @brief This file has a function to bind AddChildIDs class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/19
  @details

  <b>Python-side constructor of AddChildIDs class</b>:
  <table class="py_table">
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %AddChildIDs</td>
      <td class="py_td">AddChildIDs::AddChildIDs</td>
      <td class="py_td">
        Constructor of AddChildIDs class.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c elem : Child object (such as an Element object
            containing atoms data).
          </li>
          <li>
            \c child_name_ : A string for name of the above child
            object.
          </li>
          <li>
            \c key_for_parent_id_ : A string for key in the child
            object corresponding to \c id property of parent object
            (such as an Element object containing molecules data).
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed AddChildIDs object.
      </td>
    </tr>
  </table>
*/

#ifndef PYBIND_ADD_CHILD_IDS_H
#define PYBIND_ADD_CHILD_IDS_H

#include <adders/add_child_ids.h>
#include <pybind/adders_py/adder.h>

/*!
  @brief Function to bind AddChildIDs class to Python.
*/
static void pybind_add_child_ids(py::module &m)
{
  py::class_<AddChildIDs,PyUpdater<AddChildIDs>,Adder,Updater,ShPtr<AddChildIDs>>(m, "AddChildIDs")
    .def(py::init<const ElPtr &,const Str &,const Str &>());
}

#endif