/*!
  @file src/pybind/processors/py_pro_thickness_profile.h
  @brief This file is for binding ProThicknessProfile class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/08
*/

#ifndef PYBIND_PRO_THICKNESS_PROFILE_H
#define PYBIND_PRO_THICKNESS_PROFILE_H

#include <processors/pro_thickness_profile.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind ProThicknessProfile class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of ProThicknessProfile
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProThicknessProfile::ProThicknessProfile
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief ProThicknessProfile::ProThicknessProfile(
            const ElPtr &,
            const ElPtr &)
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProThicknessProfile::ProThicknessProfile(
            const ElPtr &,
            const ElPtr &)
        </td>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProThicknessProfile::ProThicknessProfile
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief ProThicknessProfile::ProThicknessProfile(
            const Vec<std::pair<ElPtr,ElPtr>> &)
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProThicknessProfile::ProThicknessProfile(
            const Vec<std::pair<ElPtr,ElPtr>> &)
        </td>
      </tr>
    </table>

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of ProThicknessProfile
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c set_grid</td>
        <td class="py_method">ProThicknessProfile::set_grid</td>
        <td class="py_method">
          @copybrief ProThicknessProfile::set_grid
        </td>
        <td class="py_method">
          @copydetails ProThicknessProfile::set_grid
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c set_offset</td>
        <td class="py_method">ProThicknessProfile::set_offset</td>
        <td class="py_method">
          @copybrief ProThicknessProfile::set_offset
        </td>
        <td class="py_method">
          @copydetails ProThicknessProfile::set_offset
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c shift_half_delta</td>
        <td class="py_method">ProThicknessProfile::shift_half_delta</td>
        <td class="py_method">
          @copybrief ProThicknessProfile::shift_half_delta
        </td>
        <td class="py_method">
          @copydetails ProThicknessProfile::shift_half_delta
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_conditions</td>
        <td class="py_method">ProThicknessProfile::get_conditions</td>
        <td class="py_method">
          @copybrief ProThicknessProfile::get_conditions
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          List of dictionary.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_profiles</td>
        <td class="py_method">ProThicknessProfile::get_profiles</td>
        <td class="py_method">
          @copybrief ProThicknessProfile::get_profiles
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          List of two-dimensional Numpy-Array.
        </td>
      </tr>
    </table>

    Usage example of ProThicknessProfile class for computing
    a time series of thickness profile of a film consisting of atoms
    of which radius is 2.16 and \c type property is 1.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms_traj = [
      create(StaDumpAtoms("path/to/dump", i))
        .append_updater(AddMap("type", "radius", {1: 2.16}))
      for i in range(0, 1000000, 1000))
    ]

    box_traj = [
      create(StaDumpBox("path/to/dump", i))
      for i in range(0, 1000000, 1000))
    ]

    for atoms, box in zip(atoms_traj, box_traj):
      atoms.append_updater(AddWrappedPosition(box))

    pro = ProThicknessProfile(list(zip(atoms_traj, box_traj)))
    pro.set_grid(100, 100)

    execute_omp(pro)

    profiles = pro.get_profiles()
    </code></pre>
    @endhtmlonly
  */
  void py_pro_thickness_profile(py::module &m);
}

#endif
