/*!
  @file src/pybind/starters/py_sta_molecules.h
  @brief This file is for binding StaMolecules class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/07
*/

#ifndef PYBIND_STA_MOLECULES_H
#define PYBIND_STA_MOLECULES_H

#include <starters/sta_molecules.h>
#include <pybind/starters/py_starter.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind StaMolecules class to Python.
    @param m : A mutable reference to Python module.
    @return None.
    @details
    <table class="py_table">
      <caption>
        Python-side constructor of StaMolecules
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %StaMolecules</td>
        <td class="py_td">StaMolecules::StaMolecules</td>
        <td class="py_td">
          Constructor of StaMolecules class.
        </td>
        <td class="py_td">
          - \c el_atoms : An Element object for atoms
            forming molecules to be computed.
        </td>
        <td class="py_td">
          Constructed StaMolecules object.
        </td>
      </tr>
    </table>

    Example of the constructor for a trajectory of typed molecules.
    The number of molecules is 100; molecules with odd \c id are type 1
    and the others are type 2.

    @code{.python}
      atoms_traj = [
        create(...) for i in range(0, 1000000, 1000)]

      map_from_id_to_type = {
        i + 1 : i%2 + 1 for i in range(100)
      }

      molecules_traj = [
        create(StaMolecules(atoms))
          .append_updater(AddMap("id", "type", map_from_id_to_type))
        for atoms in atoms_traj]
    @endcode
  */
  void py_sta_molecules(py::module &m);
}

#endif