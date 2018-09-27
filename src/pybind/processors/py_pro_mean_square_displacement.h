/*!
  @file src/pybind/processors/py_pro_distance_in_molecule.h
  @brief This file is for binding ProMeanSquareDisplacement class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/26
*/

#ifndef PYBIND_PRO_MEAN_SQUARE_DISPLACEMENT_H
#define PYBIND_PRO_MEAN_SQUARE_DISPLACEMENT_H

#include <processors/pro_mean_square_displacement.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind ProMeanSquareDisplacement class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of ProMeanSquareDisplacement
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProMeanSquareDisplacement::ProMeanSquareDisplacement
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief ProMeanSquareDisplacement::ProMeanSquareDisplacement
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProMeanSquareDisplacement::ProMeanSquareDisplacement
        </td>
      </tr>
    </table>

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of ProMeanSquareDisplacement
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c set_dimension</td>
        <td class="py_method">ProMeanSquareDisplacement::set_dimension</td>
        <td class="py_method">
          @copybrief ProMeanSquareDisplacement::set_dimension
        </td>
        <td class="py_method">
          @copydetails ProMeanSquareDisplacement::set_dimension
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c without_drift_correction</td>
        <td class="py_method">ProMeanSquareDisplacement::without_drift_correction</td>
        <td class="py_method">
          @copybrief ProMeanSquareDisplacement::without_drift_correction
        </td>
        <td class="py_method">
          @copydetails ProMeanSquareDisplacement::without_drift_correction
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_displacement2_array</td>
        <td class="py_method">ProMeanSquareDisplacement::get_displacement2_array</td>
        <td class="py_method">
          @copybrief ProMeanSquareDisplacement::get_displacement2_array
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          Two-dimensional Numpy-Array.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_mean_square_displacement</td>
        <td class="py_method">ProMeanSquareDisplacement::get_mean_square_displacement</td>
        <td class="py_method">
          @copybrief ProMeanSquareDisplacement::get_mean_square_displacement
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          One-dimensional Numpy-Array.
        </td>
      </tr>
    </table>

    Usage example of ProMeanSquareDisplacement class for
    three-dimensional mean square displacement.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms_traj = [
      create(StaDumpAtoms("path/to/dump", i))
      for i in range(0, 1000000, 1000))
    ]

    molecules_traj = [
      create(StaMolecules(atoms))
        .append_updater(AddCoMPosition(atoms))
      for atoms in atoms_traj
    ]

    pro = ProMeanSquareDisplacement(molecules_traj)

    InvOMP(pro).execute()

    msd = pro.get_distance2_array().mean()
    </code></pre>
    @endhtmlonly
  */
  void py_pro_mean_square_displacement(py::module &m);
}

#endif
