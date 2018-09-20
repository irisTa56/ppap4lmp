/*!
  @file src/pybind/filters/py_fil_set.h
  @brief This file is for binding FilSet class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/01
  @details

  <table class="py_table">
    <caption>
      Python-side constructor of FilSet
    </caption>
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %FilSet</td>
      <td class="py_td">FilSet::FilSet</td>
      <td class="py_td">
        Constructor of FilSet class.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c value_sets_ : Dictionary from a string key of property
            to acceptable values of that property.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed FilSet object.
      </td>
    </tr>
  </table>

  Usage example of the constructor for a filter removing atoms
  whose \c type property is not 1, 2, or 3.

  \code{.python}
    atoms = create(...)
    atoms.append_updater(FilSet({"type": {1, 2, 3}}))
  \endcode

  Usage example of the constructor for a filter removing atoms
  whose \c type property is not 1, 2, or 3, and whose \c id property
  is not a multiple of 3 less than 1000.

  \code{.python}
    atoms = create(...)
    atoms.append_updater(FilSet({
      "type": {1, 2, 3},
      "id": set(range(3, 1000, 3))
    }))
  \endcode
*/

#ifndef PYBIND_FIL_SET_H
#define PYBIND_FIL_SET_H

#include <filters/fil_set.h>
#include <pybind/filters/py_filter.h>

//! Function to bind FilSet class to Python.
static void pybind_fil_set(py::module &m)
{
  py::class_<FilSet,PyUpdater<FilSet>,Filter,Updater,ShPtr<FilSet>>(m, "FilSet")
    .def(py::init<const Map<Str,Set<Json>> &>());
}

#endif