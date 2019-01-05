/*!
  @file src/pybind/adders/py_add_child_ids.h
  @brief This file is for binding AddChildIDs class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#ifndef PYBIND_ADD_CHILD_IDS_H
#define PYBIND_ADD_CHILD_IDS_H

#include <adders/add_child_ids.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddChildIDs class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddChildIDs
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddChildIDs::AddChildIDs
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief AddChildIDs::AddChildIDs
          @copydetails AddChildIDs::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails AddChildIDs::AddChildIDs
        </td>
      </tr>
    </table>

    Usage example of the constructor to add `bead-ids` property to
    an Element object for molecules.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    molecules = create(StaMolecules(atoms))
    beads = create(StaBeads(molecules, mapping))

    molecules.append_updater(AddChildIDs(beads, "bead", "mol"))
    </code></pre>
    @endhtmlonly
  */
  void py_add_child_ids(py::module &m);
}

#endif