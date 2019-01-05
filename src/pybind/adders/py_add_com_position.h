/*!
  @file src/pybind/adders/py_add_com_position.h
  @brief This file is for binding AddCoMPosition class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/13
*/

#ifndef PYBIND_ADD_COM_POSITION_H
#define PYBIND_ADD_COM_POSITION_H

#include <adders/add_com_position.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddCoMPosition class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddCoMPosition
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddCoMPosition::AddCoMPosition
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief AddCoMPosition::AddCoMPosition
          @copydetails AddCoMPosition::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails AddCoMPosition::AddCoMPosition
        </td>
      </tr>
    </table>

    Usage example of the constructor to add `xu`, `yu` and `zu`
    property to an Element object for molecules.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    molecules = create(StaMolecules(atoms))

    molecules.append_updater(AddCoMPosition(atoms))
    </code></pre>
    @endhtmlonly
  */
  void py_add_com_position(py::module &m);
}

#endif