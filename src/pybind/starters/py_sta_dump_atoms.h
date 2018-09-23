/*!
  @file src/pybind/starters/py_sta_dump_atoms.h
  @brief This file is for binding StaDumpAtoms class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef PYBIND_STA_DUMP_ATOMS_H
#define PYBIND_STA_DUMP_ATOMS_H

#include <starters/sta_dump_atoms.h>
#include <pybind/starters/py_starter.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind StaDumpAtoms class to Python.
    @param m : A mutable reference to Python module.
    @return None.
    @details
    <table class="py_table">
      <caption>
        Python-side constructor of StaDumpAtoms
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %StaDumpAtoms</td>
        <td class="py_td">StaDumpAtoms::StaDump</td>
        <td class="py_td">
          Constructor of StaDumpAtoms class.
        </td>
        <td class="py_td">
          - \c filepath_ : A string for path to a Lammps' dump file.
          - \c timestep_ : An integer specifying
            a timestep of simulation to be parsed.
        </td>
        <td class="py_td">
          Constructed StaDumpAtoms object.
        </td>
      </tr>
    </table>

    Example of the constructor for a sequence of Lammps' dump files.

    @code{.python}
      atoms_traj = [
        create(StaDumpAtoms("path/to/dump", i))
        for i in range(0, 1000000, 1000)]
    @endcode
  */
  void py_sta_dump_atoms(py::module &m);
}

#endif