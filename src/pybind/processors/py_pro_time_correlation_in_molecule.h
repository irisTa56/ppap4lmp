/*!
  @file src/pybind/processors/py_pro_time_correlation_in_molecule.h
  @brief This file is for binding ProTimeCorrelationInMolecule class to Python.
  @author Takayuki Kobayashi
  @date 2018/10/24
*/

#ifndef PYBIND_PRO_TIME_CORRELATION_IN_MOLECULE_H
#define PYBIND_PRO_TIME_CORRELATION_IN_MOLECULE_H

#include <processors/pro_time_correlation_in_molecule.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind ProTimeCorrelationInMolecule class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of ProTimeCorrelationInMolecule
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProTimeCorrelationInMolecule::ProTimeCorrelationInMolecule
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief ProTimeCorrelationInMolecule::ProTimeCorrelationInMolecule(
            const Vec<std::pair<ElPtr,ElPtr>> &)
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProTimeCorrelationInMolecule::ProTimeCorrelationInMolecule(
            const Vec<std::pair<ElPtr,ElPtr>> &)
        </td>
      </tr>
    </table>

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of ProTimeCorrelationInMolecule
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">`set_indices`</td>
        <td class="py_method">ProTimeCorrelationInMolecule::set_indices</td>
        <td class="py_method">
          @copybrief ProTimeCorrelationInMolecule::set_indices
        </td>
        <td class="py_method">
          @copydetails ProTimeCorrelationInMolecule::set_indices
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">`set_moltype`</td>
        <td class="py_method">ProTimeCorrelationInMolecule::set_moltype</td>
        <td class="py_method">
          @copybrief ProTimeCorrelationInMolecule::set_moltype
        </td>
        <td class="py_method">
          @copydetails ProTimeCorrelationInMolecule::set_moltype
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">`get_coefficients_array`</td>
        <td class="py_method">ProTimeCorrelationInMolecule::get_coefficients_array</td>
        <td class="py_method">
          @copybrief ProTimeCorrelationInMolecule::get_coefficients_array
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          Two-dimensional Numpy-Array.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">`get_time_correlation`</td>
        <td class="py_method">ProTimeCorrelationInMolecule::get_time_correlation</td>
        <td class="py_method">
          @copybrief ProTimeCorrelationInMolecule::get_time_correlation
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          One-dimensional Numpy-Array.
        </td>
      </tr>
    </table>

    Usage example of ProTimeCorrelationInMolecule class for
    a trajectory of molecules without `type` property.
    Time correlation function for a vector between the *0* th atom
    and *100* th atom is computed.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms_traj = [
      create(StaDumpAtoms("path/to/dump", i))
      for i in range(0, 1000000, 1000))
    ]

    molecules_traj = [
      create(StaMolecules(atoms)) for atoms in atoms_traj
    ]

    pro = ProTimeCorrelationInMolecule(list(zip(atoms_traj, molecules_traj)))
    pro.set_indices(0, 100)

    execute_omp(pro)

    tcf = pro.get_time_correlation()
    </code></pre>
    @endhtmlonly
  */
  void py_pro_time_correlation_in_molecule(py::module &m);
}

#endif
