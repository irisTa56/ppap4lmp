/*!
  @file src/pybind/adders/py_add_rename.h
  @brief This file is for binding AddRename class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/17
*/

#ifndef PYBIND_ADD_RENAME_H
#define PYBIND_ADD_RENAME_H

#include <adders/add_rename.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddRename class to Python.
    @param m : A mutable reference to Python module.
    @return None.
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
          - \c key_old_ : A string key for an existing property to be
            renamed.
          - \c key_new_ : A string key by which the old key
            for the existing property is renamed.
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
          @copybrief AddRename::overwrite
        </td>
        <td class="py_td">
          - c do_overwrite_ : A boolean, whether overwriting is
            allowed or not (default is \c True).
        </td>
        <td class="py_td">
          This AddRename object.
        </td>
      </tr>
    </table>
  */
  void py_add_rename(py::module &m);
}

#endif