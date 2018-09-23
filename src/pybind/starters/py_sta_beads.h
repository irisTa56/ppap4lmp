/*!
  @file src/pybind/starters/py_sta_beads.h
  @brief This file is for binding StaBeads class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/18
*/

#ifndef PYBIND_STA_BEADS_H
#define PYBIND_STA_BEADS_H

#include <starters/sta_beads.h>
#include <pybind/starters/py_starter.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind StaBeads class to Python.
    @param m : A mutable reference to Python module.
    @return None.
    @details
    <table class="py_table">
      <caption>
        Python-side constructor of StaBeads
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %StaBeads</td>
        <td class="py_td">StaBeads::StaBeads</td>
        <td class="py_td">
          Constructor of StaBeads class for one molecular type.
        </td>
        <td class="py_td">
          - \c el_mols : A molecular Element object consisting of
            a bead Element object where the constructed object is
            appended to.
          - \c scheme : List of dictionaries describing
            coarse-grain mapping scheme. Each dictionary corresponds to
            each bead in a molecule, and contains three items:
            \c indices-in-mol is an array of zero-based index of atoms
            in a molecule, \c type is type of the bead, and \c weights
            is an array of floats for weighting factors of the atoms.
            The last two items are optional.
        </td>
        <td class="py_td">
          Constructed StaBeads object.
        </td>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %StaBeads</td>
        <td class="py_td">StaBeads::StaBeads</td>
        <td class="py_td">
          Constructor of StaBeads class for multiple molecular types.
        </td>
        <td class="py_td">
          - \c el_mols : A molecular Element object consisting of
            a bead Element object where the constructed object is
            appended to.
          - \c schemes : Dictionary from molecular type to list of
            dictionaries describing coarse-grain scheme for a molecule
            of that type. Description of each list is the same
            as for the case of one molecular type.
        </td>
        <td class="py_td">
          Constructed StaBeads object.
        </td>
      </tr>
    </table>

    Example of the constructor for beads consisting of five atoms
    in a molecule; the molecule consists of four beads,
    and all the beads are type 1.

    @code{.python}
      atoms = create(...)
      molecules = create(StaMolecules(atoms))

      my_beads = StaBeads(
        molecules,
        [
          {"type": 1, "indices-in-mol": [0, 1, 2, 3, 4]},
          {"type": 1, "indices-in-mol": [5, 6, 7, 8, 9]},
          {"type": 1, "indices-in-mol": [10, 11, 12, 13, 14]},
          {"type": 1, "indices-in-mol": [15, 16, 17, 18, 19]}
        ]
      )

      beads = create(my_beads)
    @endcode

    Example of the constructor; some beads belong to molecules
    whose type is 1 and the others belong to molecules whose type is 2.
    The number of molecules is 100; molecules with odd \c id are type 1
    and the others are type 2. All the beads for molecular type 1
    consist of five atoms and their types are 1. All the beads
    for molecular type 2 consist of four atoms and their types are 2.

    @code{.python}
      atoms = create(...)
      molecules = create(StaMolecules(atoms))

      map_from_id_to_type = {
        i + 1 : i%2 + 1 for i in range(100)
      }

      molecules.append_updater(
        AddMap("id", "type", map_from_id_to_type))

      my_beads = StaBeads(
        molecules,
        {
          1: [
            {"type": 1, "indices-in-mol": [0, 1, 2, 3, 4]},
            {"type": 1, "indices-in-mol": [5, 6, 7, 8, 9]},
            {"type": 1, "indices-in-mol": [10, 11, 12, 13, 14]},
            {"type": 1, "indices-in-mol": [15, 16, 17, 18, 19]}
          ],
          2: [
            {"type": 2, "indices-in-mol": [0, 1, 2, 3]},
            {"type": 2, "indices-in-mol": [4, 5, 6, 7]},
            {"type": 2, "indices-in-mol": [8, 9, 10, 11]},
            {"type": 2, "indices-in-mol": [12, 13, 14, 15]}
          ]
        }
      )

      beads = create(my_beads)
    @endcode
  */
  void py_sta_beads(py::module &m);
}

#endif