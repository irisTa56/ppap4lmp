/*!
  @file src/pybind/adders/py_add_inertia_moment.h
  @brief This file is for binding AddInertiaMoment class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/15
  @details

  <table class="py_table">
    <caption>
      Python-side constructor of AddInertiaMoment
    </caption>
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
        - \c elem : \e A child object (such as an Element object
          containing data for atoms).
      </td>
      <td class="py_td">
        Constructed AddInertiaMoment object, which is appended to
        a \e parent object (such as an Element object containing data
        for molecules).
      </td>
    </tr>
  </table>

  Usage example of the constructor to add elements of inertia moment
  to an Element object for molecules.

  @code{.python}
    atoms = create(...)
    molecules = create(StaMolecules(atoms))

    molecules.append_updater(AddCoMPosition(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
  @endcode
*/

#ifndef PYBIND_ADD_INERTIA_MOMENT_H
#define PYBIND_ADD_INERTIA_MOMENT_H

#include <adders/add_inertia_moment.h>
#include <pybind/adders/py_adder.h>

//! Function to bind AddInertiaMoment class to Python.
static void pybind_add_inertia_moment(py::module &m)
{
  py::class_<AddInertiaMoment,PyUpdater<AddInertiaMoment>,Adder,Updater,ShPtr<AddInertiaMoment>>(m, "AddInertiaMoment")
    .def(py::init<const ElPtr &>());
}

#endif