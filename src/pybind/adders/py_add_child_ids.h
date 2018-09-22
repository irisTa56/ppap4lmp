/*!
  @file src/pybind/adders/py_add_child_ids.h
  @brief This file is for binding AddChildIDs class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/19
  @details

  <table class="py_table">
    <caption>
      Python-side constructor of AddChildIDs
    </caption>
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
        - \c elem : \e Child object (such as an Element object
          containing data for atoms).
        - \c child_name_ : A string for naming the above child object.
        - \c key_for_parent_id_ : A string for key in the child
          object corresponding to \c id property of parent object
          (such as an Element object containing data for molecules).
      </td>
      <td class="py_td">
        Constructed AddChildIDs object, which is appended to
        a \e parent object (such as an Element object containing data
        for molecules).
      </td>
    </tr>
  </table>

  Usage example of the constructor to add \c bead-ids property to
  an Element object for molecules.

  @code{.python}
    atoms = create(...)
    molecules = create(StaMolecules(atoms))
    beads = create(StaBeads(molecules, ...))

    molecules.append_updater(AddChildIDs(beads, "bead", "mol"))
  @endcode
*/

#ifndef PYBIND_ADD_CHILD_IDS_H
#define PYBIND_ADD_CHILD_IDS_H

#include <adders/add_child_ids.h>
#include <pybind/adders/py_adder.h>

//! Function to bind AddChildIDs class to Python.
static void pybind_add_child_ids(py::module &m)
{
  py::class_<AddChildIDs,PyUpdater<AddChildIDs>,Adder,Updater,ShPtr<AddChildIDs>>(m, "AddChildIDs")
    .def(py::init<const ElPtr &,const Str &,const Str &>());
}

#endif