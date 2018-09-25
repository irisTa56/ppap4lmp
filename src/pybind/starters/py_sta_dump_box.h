/*!
  @file src/pybind/starters/py_sta_dump_box.h
  @brief This file is for binding StaDumpBox class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef PYBIND_STA_DUMP_BOX_H
#define PYBIND_STA_DUMP_BOX_H

#include <starters/sta_dump_box.h>
#include <pybind/starters/py_starter.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind StaDumpBox class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of StaDumpBox
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          StaDumpBox::StaDump
        </td>
        <td class="py_constructor" colspan="2">
          Constructor of StaDumpBox class.
          @copydetails StaDumpBox::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails StaDumpBox::StaDump
        </td>
      </tr>
    </table>

    Example of the constructor for a sequence of Lammps' dump files.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms_traj = [
      create(StaDumpBox("path/to/dump", i))
      for i in range(0, 1000000, 1000)]
    </code></pre>
    @endhtmlonly
  */
  void py_sta_dump_box(py::module &m);
}

#endif