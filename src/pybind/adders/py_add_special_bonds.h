/*!
  @file src/pybind/adders/py_add_special_bonds.h
  @brief This file is for binding AddSpecialBonds class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/19
  @details

  The term <i>special bonds</i> is somewhat confusing because one of
  special bonds is not a bond but, for example, an atom connected with
  special bond. That is, \e i th atom has \e j th atom as one of
  the special bonds when the two atoms interact with each other through
  some kind of bonded potential(s). AddSpecialBonds uses zero-based
  index of atom in a molecule to determine special bonds.

  <table class="py_table">
    <caption>
      Python-side constructor of AddSpecialBonds
    </caption>
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %AddSpecialBonds</td>
      <td class="py_td">AddSpecialBonds::AddSpecialBonds</td>
      <td class="py_td">
        Constructor of AddSpecialBonds class for one molecular type.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c el_mols : A molecular Element object consisting of
            a atomic (or bead) Element object where the constructed
            object is appended to.
          </li>
          <li>
            \c scheme : List of list of zero-based index of atoms in a
            molecule. For example, \e i th atom has \e j th atom as
            one of the special bonds when \e i th list of the \c scheme
            contains \e j.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed AddSpecialBonds object.
      </td>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %AddSpecialBonds</td>
      <td class="py_td">AddSpecialBonds::AddSpecialBonds</td>
      <td class="py_td">
        Constructor of AddSpecialBonds class for multiple molecular
        types.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c el_mols : A molecular Element object consisting of
            a atomic (or bead) Element object where the constructed
            object is appended to.
          </li>
          <li>
            \c schemes : Dictionary where the keys are molecular types
            and the values are lists of list of zero-based index of
            atoms in a molecule. Definition of the each list is the
            same as for the case of one molecular type.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed AddSpecialBonds object.
      </td>
    </tr>
  </table>

  Example of the constructor for a molecule consisting of linearly
  connected four atoms. Bond-length and bond-angle potentials are
  considered.

  \code{.python}
    atoms = create(...)
    mols = create(StaMolecules(atoms))

    my_sbonds = AddSpecialBonds(
      mols,
      [
        [1, 2],
        [0, 2, 3],
        [0, 1, 3],
        [1, 2]
      ]
    )

    atoms.append_updater(my_sbonds)
  \endcode

  Example of the constructor for two types of molecule: the first one
  consists of linearly connected four atoms, and the second one
  consists of linearly connected five atoms. Bond-length and
  bond-angle potentials are considered.

  \code{.python}
    atoms = create(...)
    mols = create(StaMolecules(atoms))

    my_sbonds = AddSpecialBonds(
      mols,
      {
        1: [
          [1, 2],
          [0, 2, 3],
          [0, 1, 3],
          [1, 2]
        ],
        2: [
          [1, 2],
          [0, 2, 3],
          [0, 1, 3, 4],
          [1, 2, 4],
          [2, 3]
        ]
      }
    )

    atoms.append_updater(my_sbonds)
  \endcode
*/

#ifndef PYBIND_ADD_SPECIAL_BONDS_H
#define PYBIND_ADD_SPECIAL_BONDS_H

#include <adders/add_special_bonds.h>
#include <pybind/adders/py_adder.h>

//! Function to bind AddSpecialBonds class to Python.
static void pybind_add_special_bonds(py::module &m)
{
  py::class_<AddSpecialBonds,PyUpdater<AddSpecialBonds>,Adder,Updater,ShPtr<AddSpecialBonds>>(m, "AddSpecialBonds")
    .def(py::init<const ElPtr &,const Vec<Vec<int>> &>())
    .def(py::init<const ElPtr &,const Map<int,Vec<Vec<int>>> &>());
}

#endif