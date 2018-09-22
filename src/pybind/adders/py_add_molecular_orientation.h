/*!
  @file src/pybind/adders/py_add_molecular_orientation.h
  @brief This file is for binding AddMolecularOrientation class to
  Python.
  @author Takayuki Kobayashi
  @date 2018/07/16
  @details

  <table class="py_table">
    <caption>
      Python-side constructor of AddMolecularOrientation
    </caption>
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %AddMolecularOrientation</td>
      <td class="py_td">AddMolecularOrientation::Updater</td>
      <td class="py_td">
        Constructor of AddMolecularOrientation class.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            None.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed AddMolecularOrientation object.
      </td>
    </tr>
  </table>

  Usage example of the constructor to add molecular orientation to
  an Element object for molecules.

  @code{.python}
    atoms = create(...)
    molecules = create(StaMolecules(atoms))

    molecules.append_updater(AddCoMPosition(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
    molecules.append_updater(AddMolecularOrientation())
  @endcode
*/

#ifndef PYBIND_ADD_MOLECULAR_ORIENTATION_H
#define PYBIND_ADD_MOLECULAR_ORIENTATION_H

#include <adders/add_molecular_orientation.h>
#include <pybind/adders/py_adder.h>

//! Function to bind AddMolecularOrientation class to Python.
static void pybind_add_molecular_orientation(py::module &m)
{
  py::class_<AddMolecularOrientation,PyUpdater<AddMolecularOrientation>,Adder,Updater,ShPtr<AddMolecularOrientation>>(m, "AddMolecularOrientation")
    .def(py::init<>());
}

#endif