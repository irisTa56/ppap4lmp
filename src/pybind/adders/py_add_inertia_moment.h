/*!
  @file src/pybind/adders/py_add_inertia_moment.h
  @brief This file is for binding AddInertiaMoment class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/15
*/

#ifndef PYBIND_ADD_INERTIA_MOMENT_H
#define PYBIND_ADD_INERTIA_MOMENT_H

#include <adders/add_inertia_moment.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddInertiaMoment class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddInertiaMoment
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddInertiaMoment::AddInertiaMoment
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief AddInertiaMoment::AddInertiaMoment
          @copydetails AddInertiaMoment::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails AddInertiaMoment::AddInertiaMoment
        </td>
      </tr>
    </table>

    Usage example of the constructor to add elements of inertia moment
    to an Element object for molecules.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    molecules = create(StaMolecules(atoms))

    molecules.append_updater(AddCoMPosition(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
    </code></pre>
    @endhtmlonly
  */
  void py_add_inertia_moment(py::module &m);
}

#endif