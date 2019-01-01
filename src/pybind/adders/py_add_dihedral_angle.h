/*!
  @file src/pybind/adders/py_add_dihedral_angle.h
  @brief This file is for binding AddDihedralAngle class to Python.
  @author Yang Juntao
  @date 2018/12/24
*/

#ifndef PYBIND_ADD_DIHEDRAL_ANGLE_H
#define PYBIND_ADD_DIHEDRAL_ANGLE_H

#include <adders/add_dihedral_angle.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddDihedralAngle class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddDihedralAngle
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddDihedralAngle::AddDihedralAngle
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief AddDihedralAngle::AddDihedralAngle
          @copydetails AddDihedralAngle::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails AddDihedralAngle::AddDihedralAngle
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

    molecules.append_updater(AddDihedralAngle(atoms))
    </code></pre>
    @endhtmlonly
    ----
  */
  void py_add_dihedral_angle(py::module &m);
}

#endif