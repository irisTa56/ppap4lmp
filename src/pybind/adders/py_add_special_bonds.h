/*!
  @file src/pybind/adders/py_add_special_bonds.h
  @brief This file is for binding AddSpecialBonds class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#ifndef PYBIND_ADD_SPECIAL_BONDS_H
#define PYBIND_ADD_SPECIAL_BONDS_H

#include <adders/add_special_bonds.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddSpecialBonds class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddSpecialBonds
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddSpecialBonds::AddSpecialBonds
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief AddSpecialBonds::AddSpecialBonds(
            const ElPtr &,
            const Vec<Vec<int>> &)
          @copydetails AddSpecialBonds::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails AddSpecialBonds::AddSpecialBonds(
            const ElPtr &,
            const Vec<Vec<int>> &)
        </td>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddSpecialBonds::AddSpecialBonds
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief AddSpecialBonds::AddSpecialBonds(
            const ElPtr &,
            const Map<int,Vec<Vec<int>>> &)
          @copydetails AddSpecialBonds::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails AddSpecialBonds::AddSpecialBonds(
            const ElPtr &,
            const Map<int,Vec<Vec<int>>> &)
        </td>
      </tr>
    </table>

    Example of the constructor for molecules consisting of linearly
    connected four atoms. Bond-length and bond-angle potentials are
    considered.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    molecules = create(StaMolecules(atoms))

    my_sbonds = AddSpecialBonds(
      molecules,
      [
        [1, 2],
        [0, 2, 3],
        [0, 1, 3],
        [1, 2]
      ]
    )

    atoms.append_updater(my_sbonds)
    </code></pre>
    @endhtmlonly

    Example of the constructor for two types of molecule: the first one
    consists of linearly connected four atoms, and the second one
    consists of linearly connected five atoms. Bond-length and
    bond-angle potentials are considered.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    molecules = create(StaMolecules(atoms))

    my_sbonds = AddSpecialBonds(
      molecules,
      {
        1: [
          [1, 2],
          [0, 2, 3],
          [0, 1, 3],
          [1, 2]
        ],
        2: [
          [1, 2],
          [0, 2, 3],
          [0, 1, 3, 4],
          [1, 2, 4],
          [2, 3]
        ]
      }
    )

    atoms.append_updater(my_sbonds)
    </code></pre>
    @endhtmlonly
  */
  void py_add_special_bonds(py::module &m);
}

#endif