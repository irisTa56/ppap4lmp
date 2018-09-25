/*!
  @file src/pybind/adders/py_add_molecular_orientation.h
  @brief This file is for binding AddMolecularOrientation class to
  Python.
  @author Takayuki Kobayashi
  @date 2018/07/16
*/

#ifndef PYBIND_ADD_MOLECULAR_ORIENTATION_H
#define PYBIND_ADD_MOLECULAR_ORIENTATION_H

#include <adders/add_molecular_orientation.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddMolecularOrientation class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddMolecularOrientation
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddMolecularOrientation::Updater
        </td>
        <td class="py_constructor" colspan="2">
          Constructor of AddMolecularOrientation class.
          @copydetails AddMolecularOrientation::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          None.
        </td>
      </tr>
    </table>

    Usage example of the constructor to add molecular orientation to
    an Element object for molecules.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    molecules = create(StaMolecules(atoms))

    molecules.append_updater(AddCoMPosition(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
    molecules.append_updater(AddMolecularOrientation())
    </code></pre>
    @endhtmlonly
  */
  void py_add_molecular_orientation(py::module &m);
}

#endif