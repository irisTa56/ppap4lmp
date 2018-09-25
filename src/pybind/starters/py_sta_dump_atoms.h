/*!
  @file src/pybind/starters/py_sta_dump_atoms.h
  @brief This file is for binding StaDumpAtoms class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef PYBIND_STA_DUMP_ATOMS_H
#define PYBIND_STA_DUMP_ATOMS_H

#include <starters/sta_dump_atoms.h>
#include <pybind/starters/py_starter.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind StaDumpAtoms class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of StaDumpAtoms
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          StaDumpAtoms::StaDump
        </td>
        <td class="py_constructor" colspan="2">
          Constructor of StaDumpAtoms class.
          @copydetails StaDumpAtoms::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails StaDumpAtoms::StaDump
        </td>
      </tr>
    </table>

    Example of the constructor for a sequence of Lammps' dump files.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms_traj = [
      create(StaDumpAtoms("path/to/dump", i))
      for i in range(0, 1000000, 1000)]
    </code></pre>
    @endhtmlonly
  */
  void py_sta_dump_atoms(py::module &m);
}

#endif