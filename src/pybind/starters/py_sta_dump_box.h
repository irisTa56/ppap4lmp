/*!
  @file src/pybind/starters/py_sta_dump_box.h
  @brief This file is for binding StaDumpBox class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef PYBIND_STA_DUMP_BOX_H
#define PYBIND_STA_DUMP_BOX_H

#include <starters/sta_dump_box.h>
#include <pybind/starters/py_starter.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind StaDumpBox class to Python.
    @param m : A mutable reference to Python module.
    @return None.
    @details
    <table class="py_table">
      <caption>
        Python-side constructor of StaDumpBox
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %StaDumpBox</td>
        <td class="py_td">StaDumpBox::StaDump</td>
        <td class="py_td">
          Constructor of StaDumpBox class.
        </td>
        <td class="py_td">
          - \c filepath_ : A string for path to a Lammps' dump file.
          - \c timestep_ : An integer specifying
            a timestep of simulation to be parsed.
        </td>
        <td class="py_td">
          Constructed StaDumpBox object.
        </td>
      </tr>
    </table>

    Example of the constructor for a sequence of Lammps' dump files.

    @code{.python}
      atoms_traj = [
        create(StaDumpBox("path/to/dump", i))
        for i in range(0, 1000000, 1000)]
    @endcode
  */
  void py_sta_dump_box(py::module &m);
}

#endif