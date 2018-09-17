/*!
  @file src/pybind/py_adders/add_map.h
  @brief This file has a function to bind AddMap class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/26
  @details

  <b>Python-side constructor of AddMap class</b>:
  <table class="py_table">
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %AddMap</td>
      <td class="py_td">AddMap::AddMap</td>
      <td class="py_td">
        Constructor of AddMap class.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c key_ref_ : A string key for a reference property: an
            existing property to be used as domain of mapping (see also
            the 3rd argument).
          </li>
          <li>
            \c key_new_ : A string key for a new property to be added.
            Values of the new property are determined by mapping (see
            also the 3rd argument).
          </li>
          <li>
            \c mapping_ : Dictionary defining mapping from values of
            the reference property to values of the new property. Keys
            of the dictionary corresponds to domain of the mapping and
            values of the dictionary corresponds to codomain of the
            mapping. Note that the keys must cover all values of the
            reference property.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed AddMap object.
      </td>
    </tr>
  </table>

  <p>
    Example of the constructor for mapping from <c>atomic-number</c> to
    \c mass.

    \code{.python}
      my_add_map = AddMap(
        "atomic-number", "mass",
        {
          6: 12.011,
          8: 15.999,
          9: 18.998
        }
      )
    \endcode
  </p>

  <b>Python-side methods of AddMap class</b>:
  <table class="py_table">
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c overwrite</td>
      <td class="py_td">AddMap::overwrite</td>
      <td class="py_td">
        Allow overwriting an existing property whose name is the same
        as new property to be added.
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
        This AddMap object.
      </td>
    </tr>
  </table>
*/

#ifndef PYBIND_ADD_MAP_H
#define PYBIND_ADD_MAP_H

#include <adders/add_map.h>
#include <pybind/py_adders/adder.h>

/*!
  @brief Function to bind AddMap class to Python.
*/
static void pybind_add_map(py::module &m)
{
  py::class_<AddMap,PyUpdater<AddMap>,Adder,Updater,ShPtr<AddMap>>(m, "AddMap")
    .def(py::init<const Str &,const Str &,const Map<Json,Json> &>())
    .def(
      "overwrite", &AddMap::overwrite,
      py::arg("do_overwrite_") = true);
}

#endif