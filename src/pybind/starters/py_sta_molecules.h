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

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of StaMolecules
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          StaMolecules::StaMolecules
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief StaMolecules::StaMolecules
          @copydetails StaMolecules::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails StaMolecules::StaMolecules
        </td>
      </tr>
    </table>

    Usage example of the constructor for a trajectory of typed molecules.
    The number of molecules is 100; molecules with odd `id` are type 1
    and the others are type 2.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms_traj = [
      create(StaDumpAtoms("path/to/dump", i))
      for i in range(0, 1000000, 1000))
    ]

    map_from_id_to_type = {
      i + 1 : i%2 + 1 for i in range(100)
    }

    molecules_traj = [
      create(StaMolecules(atoms))
        .append_updater(AddMap("id", "type", map_from_id_to_type))
      for atoms in atoms_traj
    ]
    </code></pre>
    @endhtmlonly
  */
  void py_sta_molecules(py::module &m);
}

#endif