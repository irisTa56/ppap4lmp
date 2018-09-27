/*!
  @file src/pybind/processors/py_pro_value_array.h
  @brief This file is for binding ProValueArray class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/16
*/

#ifndef PYBIND_PRO_VALUE_ARRAY_H
#define PYBIND_PRO_VALUE_ARRAY_H

#include <processors/pro_value_array.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind ProValueArray class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of ProValueArray
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProValueArray::ProValueArray
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief ProValueArray::ProValueArray(const ElPtr &)
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProValueArray::ProValueArray(const ElPtr &)
        </td>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProValueArray::ProValueArray
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief ProValueArray::ProValueArray(const Vec<ElPtr> &)
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProValueArray::ProValueArray(const Vec<ElPtr> &)
        </td>
      </tr>
    </table>

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of ProValueArray
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c select</td>
        <td class="py_method">ProValueArray::select</td>
        <td class="py_method">
          @copybrief ProValueArray::select
        </td>
        <td class="py_method">
          @copydetails ProValueArray::select
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_results</td>
        <td class="py_method">ProValueArray::get_results</td>
        <td class="py_method">
          @copybrief ProValueArray::get_results
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          Dictionary from string key to two-dimensional Numpy-Array.
        </td>
      </tr>
    </table>

    Usage example of ProValueArray class
    for computing an averaged radius of gyration of molecules.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms_traj = [
      create(StaDumpAtoms("path/to/dump", i))
      for i in range(0, 1000000, 1000))
    ]

    molecules_traj = [
      create(StaMolecules(atoms))
        .append_updater(AddCoMPosition(atoms))
        .append_updater(AddInertiaMoment(atoms))
        .append_updater(AddGyrationRadius())
       for atoms in atoms_traj
    ]

    pro = ProValueArray(molecules_traj)
    pro.select("Rg^2")

    InvOMP(pro).execute()

    Rg = sqrt(pro.get_results()["Rg^2"].mean())
    </code></pre>
    @endhtmlonly
  */
  void py_pro_value_array(py::module &m);
}

#endif
