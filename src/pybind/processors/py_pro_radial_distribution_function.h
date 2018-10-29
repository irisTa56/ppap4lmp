/*!
  @file src/pybind/processors/py_pro_radial_distribution_function.h
  @brief This file is for binding ProRadialDistributionFunction class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#ifndef PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_H
#define PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_H

#include <processors/pro_radial_distribution_function.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind ProRadialDistributionFunction class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of ProRadialDistributionFunction
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProRadialDistributionFunction::ProRadialDistributionFunction
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief ProRadialDistributionFunction::ProRadialDistributionFunction(
            const ElPtr &,
            const ElPtr &)
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProRadialDistributionFunction::ProRadialDistributionFunction(
            const ElPtr &,
            const ElPtr &)
        </td>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProRadialDistributionFunction::ProRadialDistributionFunction
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief ProRadialDistributionFunction::ProRadialDistributionFunction(
            const Vec<std::pair<ElPtr,ElPtr>> &)
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProRadialDistributionFunction::ProRadialDistributionFunction(
            const Vec<std::pair<ElPtr,ElPtr>> &)
        </td>
      </tr>
    </table>

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of ProRadialDistributionFunction
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c set_bin</td>
        <td class="py_method">ProRadialDistributionFunction::set_bin</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunction::set_bin
        </td>
        <td class="py_method">
          @copydetails ProRadialDistributionFunction::set_bin
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c bin_from_r_to_r_plus_dr</td>
        <td class="py_method">ProRadialDistributionFunction::bin_from_r_to_r_plus_dr</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunction::bin_from_r_to_r_plus_dr
        </td>
        <td class="py_method">
          @copydetails ProRadialDistributionFunction::bin_from_r_to_r_plus_dr
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c beyond_half_box_length</td>
        <td class="py_method">ProRadialDistributionFunction::beyond_half_box_length</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunction::beyond_half_box_length
        </td>
        <td class="py_method">
          @copydetails ProRadialDistributionFunction::beyond_half_box_length
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_r_axis</td>
        <td class="py_method">ProRadialDistributionFunction::get_r_axis</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunction::get_r_axis
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          One-dimensional Numpy-Array.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_rdf</td>
        <td class="py_method">ProRadialDistributionFunction::get_rdf</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunction::get_rdf
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          One-dimensional Numpy-Array.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_rdf_traj</td>
        <td class="py_method">ProRadialDistributionFunction::get_rdf_traj</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunction::get_rdf_traj
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          List of one-dimensional Numpy-Arrays.
        </td>
      </tr>
    </table>

    Usage example of ProRadialDistributionFunction class for computing
    radial distribution function of atoms
    with the following two conditions.
    Linearly connected four atoms form a molecule.
    Each atom has next two atoms in the same molecule as special bonds.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms_traj = [
      create(StaDumpAtoms("path/to/dump", i))
      for i in range(0, 1000000, 1000))
    ]

    for atoms in atoms_traj:
      atoms.append_updater(AddSpecialBonds(
        create(StaMolecules(atoms)),
        [[1, 2], [0, 2, 3], [0, 1, 3], [1, 2]]
      ))

    box_traj = [
      create(StaDumpBox("path/to/dump", i))
      for i in range(0, 1000000, 1000))
    ]

    for atoms, box in zip(atoms_traj, box_traj):
      atoms.append_updater(AddWrappedPosition(box))

    pro = ProRadialDistributionFunction(list(zip(atoms_traj, box_traj)))
    pro.set_bin(0.1, 200)

    execute_omp(pro)

    rdf = pro.get_rdf()
    </code></pre>
    @endhtmlonly
  */
  void py_pro_radial_distribution_function(py::module &m);
}

#endif
