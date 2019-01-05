/*!
  @file src/pybind/adders/py_add_bond_length.h
  @brief This file is for binding AddBondLength class to Python.
  @author Yang Juntao & Kawai Kento
  @date 2018/12/06
*/

#ifndef PYBIND_ADD_BOND_LENGTH_H
#define PYBIND_ADD_BOND_LENGTH_H

#include <adders/add_bond_length.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddBondLength class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddBondLength
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddBondLength::AddBondLength
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief AddBondLength::AddBondLength
          @copydetails AddBondLength::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails AddBondLength::AddBondLength
        </td>
      </tr>
    </table>

    Usage example of the constructor to add `length` property to an
    Element object for bonds.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    bonds = create(StaCustom([...]))

    bonds.append_updater(AddBondLength(atoms))
    </code></pre>
    @endhtmlonly
  */
  void py_add_bond_length(py::module &m);
}

#endif