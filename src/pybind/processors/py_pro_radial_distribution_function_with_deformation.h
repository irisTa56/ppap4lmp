/*!
  @file src/pybind/processors/py_pro_radial_distribution_function_with_deformation.h
  @brief This file is for binding ProRadialDistributionFunctionWithDeformation class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#ifndef PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H
#define PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H

#include <processors/pro_radial_distribution_function_with_deformation.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind ProRadialDistributionFunctionWithDeformation class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of ProRadialDistributionFunctionWithDeformation
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProRadialDistributionFunctionWithDeformation::ProRadialDistributionFunction
        </td>
        <td class="py_constructor" colspan="2">
          Constructor of ProRadialDistributionFunctionWithDeformation class
          for a snapshot of simulation.
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProRadialDistributionFunctionWithDeformation::ProRadialDistributionFunction(
            const ElPtr &,
            const ElPtr &)
        </td>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProRadialDistributionFunctionWithDeformation::ProRadialDistributionFunction
        </td>
        <td class="py_constructor" colspan="2">
          Constructor of ProRadialDistributionFunctionWithDeformation class
          for multiple snapshots of simulation.
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProRadialDistributionFunctionWithDeformation::ProRadialDistributionFunction(
            const Vec<std::pair<ElPtr,ElPtr>> &)
        </td>
      </tr>
    </table>

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of ProRadialDistributionFunctionWithDeformation
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
        <td class="py_method">ProRadialDistributionFunctionWithDeformation::set_bin</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunctionWithDeformation::set_bin
        </td>
        <td class="py_method">
          @copydetails ProRadialDistributionFunctionWithDeformation::set_bin
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
        <tr class="py_method">
        <td class="py_method">\c set_margin</td>
        <td class="py_method">ProRadialDistributionFunctionWithDeformation::set_margin</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunctionWithDeformation::set_margin
        </td>
        <td class="py_method">
          @copydetails ProRadialDistributionFunctionWithDeformation::set_margin
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c bin_from_r_to_r_plus_dr</td>
        <td class="py_method">ProRadialDistributionFunctionWithDeformation::bin_from_r_to_r_plus_dr</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunctionWithDeformation::bin_from_r_to_r_plus_dr
        </td>
        <td class="py_method">
          @copydetails ProRadialDistributionFunctionWithDeformation::bin_from_r_to_r_plus_dr
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c beyond_half_box_length</td>
        <td class="py_method">ProRadialDistributionFunctionWithDeformation::beyond_half_box_length</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunctionWithDeformation::beyond_half_box_length
        </td>
        <td class="py_method">
          @copydetails ProRadialDistributionFunctionWithDeformation::beyond_half_box_length
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_r_axis</td>
        <td class="py_method">ProRadialDistributionFunctionWithDeformation::get_r_axis</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunctionWithDeformation::get_r_axis
        </td>
        <td class="py_method">
          A.
        </td>
        <td class="py_method">
          One-dimensional Numpy-Array.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_rdf</td>
        <td class="py_method">ProRadialDistributionFunctionWithDeformation::get_rdf</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunctionWithDeformation::get_rdf
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
        <td class="py_method">ProRadialDistributionFunctionWithDeformation::get_rdf_traj</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunctionWithDeformation::get_rdf_traj
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          List of one-dimensional Numpy-Arrays.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_gyration_radius</td>
        <td class="py_method">ProRadialDistributionFunctionWithDeformation::get_gyration_radius</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunctionWithDeformation::get_gyration_radius
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          Dictionary from string keys to one-dimensional Numpy-Arrays.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_gyration_radius_traj</td>
        <td class="py_method">ProRadialDistributionFunctionWithDeformation::get_gyration_radius_traj</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunctionWithDeformation::get_gyration_radius_traj
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          Dictionary from string keys to lists of one-dimensional Numpy-Arrays.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_squared_gyration_radius</td>
        <td class="py_method">ProRadialDistributionFunctionWithDeformation::get_squared_gyration_radius</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunctionWithDeformation::get_squared_gyration_radius
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          Dictionary from string keys to one-dimensional Numpy-Arrays.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_squared_gyration_radius_traj</td>
        <td class="py_method">ProRadialDistributionFunctionWithDeformation::get_squared_gyration_radius_traj</td>
        <td class="py_method">
          @copybrief ProRadialDistributionFunctionWithDeformation::get_squared_gyration_radius_traj
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          Dictionary from string keys to lists of one-dimensional Numpy-Arrays.
        </td>
      </tr>
    </table>

    Usage example of ProRadialDistributionFunctionWithDeformation class
    for computing radial distribution function of beads.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    ProRDFWD = ProRadialDistributionFunctionWithDeformation

    n_samples = 1000
    interval = 1000

    atoms_traj = [create(
      StaDumpAtoms("/path/to/dump", i))
      for i in range(0, n_samples*interval+1, interval)
    ]
    box_traj = [create(
      StaDumpBox("/path/to/dump", i))
      for i in range(0, n_samples*interval+1, interval)
    ]

    mols_traj = [create(StaMolecules(atoms)) for atoms in atoms_traj]

    mappings = [
      [0, 1, 2, 12, 13, 14, 15, 16, 17, 18],
      [3, 4, 5, 19, 20, 21, 22, 23, 24],
      [6, 7, 8, 25, 26, 27, 28, 29, 30],
      [9, 10, 11, 31, 32, 33, 34, 35, 36, 37]
    ]

    abst_beads = [
      {"type": 1, "indices-in-mol": mapping}
      for i, mapping in enumerate(mappings)
    ]

    abst_special_bonds = [[1,2], [0,2,3], [0,1,3], [1,2]]


    beads_traj = [
      create(StaBeads(mols, abst_beads))
        .append_updater(AddCoMPosition(atoms))
        .append_updater(AddInertiaMoment(atoms))
        .append_updater(AddWrappedPosition(box))
      for atoms, box, mols in zip(atoms_traj, box_traj, mols_traj)
    ]


    for beads, mols in zip(beads_traj, mols_traj):

      mols.append_updater(AddChildIDs(beads, "bead", "mol"))
      mols.append_updater(AddRename("bead-ids", "atom-ids").overwrite())

      beads.append_updater(AddSpecialBonds(mols, abst_special_bonds))

    pro = ProRDFWD(list(zip(beads_traj, box_traj)))

    pro.set_bin(0.1, 200)
    pro.set_margin(2.0)

    InvOMP(pro).execute()

    print(pro.get_rdf())
    </code></pre>
    @endhtmlonly
  */
  void py_pro_radial_distribution_function_with_deformation(py::module &m);
}

#endif
