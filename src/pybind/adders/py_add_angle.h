/*!
  @file src/pybind/adders/py_add_angle.h
  @brief This file is for binding AddAngle class to Python.
  @author Yang Juntao
  @date 2018/12/20
*/

#ifndef PYBIND_ADD_ANGLE_H
#define PYBIND_ADD_ANGLE_H

#include <adders/add_angle.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddAngle class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddAngle
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddAngle::AddAngle
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief AddAngle::AddAngle
          @copydetails AddAngle::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails AddAngle::AddAngle
        </td>
      </tr>
    </table>

    ---modify
    Usage example of the constructor to add \c xu, \c yu and \c zu
    property to an Element object for molecules.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    molecules = create(StaMolecules(atoms))

    molecules.append_updater(AddAngle(atoms))
    </code></pre>
    @endhtmlonly
    ----
  */
  void py_add_angle(py::module &m);
}

#endif