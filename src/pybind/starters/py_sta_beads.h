/*!
  @file src/pybind/starters/py_sta_beads.h
  @brief This file is for binding StaBeads class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/18
*/

#ifndef PYBIND_STA_BEADS_H
#define PYBIND_STA_BEADS_H

#include <starters/sta_beads.h>
#include <pybind/starters/py_starter.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind StaBeads class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of StaBeads
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          StaBeads::StaBeads
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief StaBeads::StaBeads(
            const ElPtr &,
            const Vec<Json> &)
          @copydetails StaBeads::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails StaBeads::StaBeads(
            const ElPtr &,
            const Vec<Json> &)
        </td>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          StaBeads::StaBeads
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief StaBeads::StaBeads(
            const ElPtr &,
            const Map<int,Vec<Json>> &)
          @copydetails StaBeads::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails StaBeads::StaBeads(
            const ElPtr &,
            const Map<int,Vec<Json>> &)
        </td>
      </tr>
    </table>

    Usage example of the constructor for beads consisting of five atoms
    in a molecule; the molecule consists of four beads,
    and all the beads are type 1.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    molecules = create(StaMolecules(atoms))

    my_beads = StaBeads(
      molecules,
      [
        {"type": 1, "indices-in-mol": [0, 1, 2, 3, 4]},
        {"type": 1, "indices-in-mol": [5, 6, 7, 8, 9]},
        {"type": 1, "indices-in-mol": [10, 11, 12, 13, 14]},
        {"type": 1, "indices-in-mol": [15, 16, 17, 18, 19]}
      ]
    )

    beads = create(my_beads)
    </code></pre>
    @endhtmlonly

    Usage example of the constructor; some beads belong to molecules
    whose type is 1 and the others belong to molecules whose type is 2.
    The number of molecules is 100; molecules with odd `id` are type 1
    and the others are type 2. All the beads for molecular type 1
    consist of five atoms and their types are 1. All the beads
    for molecular type 2 consist of four atoms and their types are 2.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    molecules = create(StaMolecules(atoms))

    map_from_id_to_type = {
      i + 1 : i%2 + 1 for i in range(100)
    }

    molecules.append_updater(
      AddMap("id", "type", map_from_id_to_type))

    my_beads = StaBeads(
      molecules,
      {
        1: [
          {"type": 1, "indices-in-mol": [0, 1, 2, 3, 4]},
          {"type": 1, "indices-in-mol": [5, 6, 7, 8, 9]},
          {"type": 1, "indices-in-mol": [10, 11, 12, 13, 14]},
          {"type": 1, "indices-in-mol": [15, 16, 17, 18, 19]}
        ],
        2: [
          {"type": 2, "indices-in-mol": [0, 1, 2, 3]},
          {"type": 2, "indices-in-mol": [4, 5, 6, 7]},
          {"type": 2, "indices-in-mol": [8, 9, 10, 11]},
          {"type": 2, "indices-in-mol": [12, 13, 14, 15]}
        ]
      }
    )

    beads = create(my_beads)
    </code></pre>
    @endhtmlonly
  */
  void py_sta_beads(py::module &m);
}

#endif