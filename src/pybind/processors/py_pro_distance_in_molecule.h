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

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of ProDistanceInMolecule
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProDistanceInMolecule::ProDistanceInMolecule
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief ProDistanceInMolecule::ProDistanceInMolecule(
            const ElPtr &,
            const ElPtr &)
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProDistanceInMolecule::ProDistanceInMolecule(
            const ElPtr &,
            const ElPtr &)
        </td>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProDistanceInMolecule::ProDistanceInMolecule
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief ProDistanceInMolecule::ProDistanceInMolecule(
            const Vec<std::pair<ElPtr,ElPtr>> &)
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProDistanceInMolecule::ProDistanceInMolecule(
            const Vec<std::pair<ElPtr,ElPtr>> &)
        </td>
      </tr>
    </table>

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of ProDistanceInMolecule
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c set_indices</td>
        <td class="py_method">ProDistanceInMolecule::set_indices</td>
        <td class="py_method">
          @copybrief ProDistanceInMolecule::set_indices
        </td>
        <td class="py_method">
          @copydetails ProDistanceInMolecule::set_indices
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c set_moltype</td>
        <td class="py_method">ProDistanceInMolecule::set_moltype</td>
        <td class="py_method">
          @copybrief ProDistanceInMolecule::set_moltype
        </td>
        <td class="py_method">
          @copydetails ProDistanceInMolecule::set_moltype
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_distance_array</td>
        <td class="py_method">ProDistanceInMolecule::get_distance_array</td>
        <td class="py_method">
          @copybrief ProDistanceInMolecule::get_distance_array
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          Two-dimensional Numpy-Array.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_distance2_array</td>
        <td class="py_method">ProDistanceInMolecule::get_distance2_array</td>
        <td class="py_method">
          @copybrief ProDistanceInMolecule::get_distance2_array
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          Two-dimensional Numpy-Array.
        </td>
      </tr>
    </table>

    Usage example of ProDistanceInMolecule class for a trajectory of
    molecules without \c type property.
    Distance between the \e 0 th atom and \e 100 th atom is computed.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms_traj = [
      create(StaDumpAtoms("path/to/dump", i))
      for i in range(0, 1000000, 1000))
    ]

    molecules_traj = [
      create(StaMolecules(atoms)) for atoms in atoms_traj
    ]

    pro = ProDistanceInMolecule(list(zip(atoms_traj, molecules_traj)))
    pro.set_indices(0, 100)

    InvOMP(pro).execute()

    average_r2 = pro.get_distance2_array().mean()
    </code></pre>
    @endhtmlonly
  */
  void py_pro_distance_in_molecule(py::module &m);
}

#endif
