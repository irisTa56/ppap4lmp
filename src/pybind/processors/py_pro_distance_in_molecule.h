/*!
  @file src/pybind/processors/py_pro_distance_in_molecule.h
  @brief This file is for binding ProDistanceInMolecule class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/25
*/

#ifndef PYBIND_PRO_DISTANCE_IN_MOLECULE_H
#define PYBIND_PRO_DISTANCE_IN_MOLECULE_H

#include <processors/pro_distance_in_molecule.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind ProDistanceInMolecule class to Python.
    @param m : A mutable reference to Python module.
    @return None.
    @details
    <table class="py_table">
      <caption>
        Python-side constructor of ProDistanceInMolecule
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %ProDistanceInMolecule</td>
        <td class="py_td">ProDistanceInMolecule::ProDistanceInMolecule</td>
        <td class="py_td">
          Constructor of ProDistanceInMolecule class
          for a snapshot of a simulation.
        </td>
        <td class="py_td">
          - \c mols : An Element object for molecules.
          - \c atoms : An Element object for atoms.
        </td>
        <td class="py_td">
          Constructed ProDistanceInMolecule object.
        </td>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %ProDistanceInMolecule</td>
        <td class="py_td">ProDistanceInMolecule::ProDistanceInMolecule</td>
        <td class="py_td">
          Constructor of ProDistanceInMolecule class
          for a trajectory of a simulation.
        </td>
        <td class="py_td">
          - \c pairs : List of pairs of two Element objects:
            the first object is for molecules
            and the second object is for atoms.
        </td>
        <td class="py_td">
          Constructed ProDistanceInMolecule object.
        </td>
      </tr>
    </table>

    Usage example of the constructor for a simulation trajectory.

    @code{.python}

      atoms_traj = [
        create(...) for i in range(0, 1000000, 1000)]




      molecules_traj = [
        create(StaMolecules(atoms))
          .append_updater(AddMap("id", "type", map_from_id_to_type))
        for atoms in atoms_traj]

      my_mapping = AddMap(
        "atomic-number", "mass",
        {
          6: 12.011,
          8: 15.999,
          9: 18.998
        }
      )
    @endcode

    <table class="py_table">
      <caption>
        Python-side methods of ProDistanceInMolecule
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c select</td>
        <td class="py_td">ProDistanceInMolecule::select</td>
        <td class="py_td">
          @copybrief ProDistanceInMolecule::select
        </td>
        <td class="py_td">
          - \c *args : A variable number of string keys specifying
            properties to be copied.
        </td>
        <td class="py_td">
          None.
        </td>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c get_results</td>
        <td class="py_td">ProDistanceInMolecule::get_results</td>
        <td class="py_td">
          @copybrief ProDistanceInMolecule::get_results
        </td>
        <td class="py_td">
          None.
        </td>
        <td class="py_td">
          List of JSON-like object consisting of copied properties.
        </td>
      </tr>
    </table>
  */
  void py_pro_distance_in_molecule(py::module &m);
}

#endif
