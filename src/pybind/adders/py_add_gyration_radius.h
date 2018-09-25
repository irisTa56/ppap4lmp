/*!
  @file src/pybind/adders/py_add_gyration_radius.h
  @brief This file is for binding AddGyrationRadius class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/15
*/

#ifndef PYBIND_ADD_GYRATION_RADIUS_H
#define PYBIND_ADD_GYRATION_RADIUS_H

#include <adders/add_gyration_radius.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddGyrationRadius class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddGyrationRadius
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddGyrationRadius::Updater
        </td>
        <td class="py_constructor" colspan="2">
          Constructor of AddGyrationRadius class.
          @copydetails AddGyrationRadius::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          None.
        </td>
      </tr>
    </table>

    Usage example of the constructor to add square of gyration radius
    to an Element object for molecules.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    molecules = create(StaMolecules(atoms))

    molecules.append_updater(AddCoMPosition(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
    molecules.append_updater(AddGyrationRadius())
    </code></pre>
    @endhtmlonly

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of AddGyrationRadius
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c with_sqrted</td>
        <td class="py_method">AddGyrationRadius::with_sqrted</td>
        <td class="py_method">
          @copybrief AddGyrationRadius::with_sqrted
        </td>
        <td class="py_method">
          @copydetails AddGyrationRadius::with_sqrted
        </td>
        <td class="py_method">
          This AddGyrationRadius object.
        </td>
      </tr>
    </table>
  */
  void py_add_gyration_radius(py::module &m);
}

#endif