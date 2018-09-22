/*!
  @file src/pybind/adders/py_add_rename.h
  @brief This file is for binding AddRename class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/17
  @details

  <table class="py_table">
    <caption>
      Python-side constructor of AddRename
    </caption>
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %AddRename</td>
      <td class="py_td">AddRename::AddRename</td>
      <td class="py_td">
        Constructor of AddRename class.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c key_old_ : A string key for an existing property to be
            renamed.
          </li>
          <li>
            \c key_new_ : A string key by which the old key of the
            existing property is renamed.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed AddRename object.
      </td>
    </tr>
  </table>

  <table class="py_table">
    <caption>
      Python-side methods of AddRename
    </caption>
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c overwrite</td>
      <td class="py_td">AddRename::overwrite</td>
      <td class="py_td">
        Allow overwriting an existing property by a renamed property
        (another existing property) with the same name.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c do_overwrite_ : A boolean, whether overwriting is
            allowed or not. No argument leads to allowing overwriting.
          </li>
        </ul>
      </td>
      <td class="py_td">
        This AddRename object.
      </td>
    </tr>
  </table>
*/

#ifndef PYBIND_ADD_RENAME_H
#define PYBIND_ADD_RENAME_H

#include <adders/add_rename.h>
#include <pybind/adders/py_adder.h>

//! Function to bind AddRename class to Python.
static void pybind_add_rename(py::module &m)
{
  py::class_<AddRename,PyUpdater<AddRename>,Adder,Updater,ShPtr<AddRename>>(m, "AddRename")
    .def(py::init<const Str &,const Str &>())
    .def(
      "overwrite", &AddRename::overwrite,
      py::arg("do_overwrite_") = true);
}

#endif