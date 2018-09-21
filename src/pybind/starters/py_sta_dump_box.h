/*!
  @file src/pybind/starters/py_sta_dump_box.h
  @brief This file is for binding StaDumpBox class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/29
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
        <ul class="py_ul">
          <li>
            \c filepath_ : A string for path to a Lammps' dump file.
          </li>
          <li>
            \c timestep_ : An integer specifying
            a timestep of simulation to be parsed.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed StaDumpBox object.
      </td>
    </tr>
  </table>

  Example of the constructor for a trajectory.

  \code{.python}
    atoms_traj = [
      create(StaDumpBox("path/to/dump", i))
      for i in range(0, 1000000, 1000)]
  \endcode
*/

#ifndef PYBIND_STA_DUMP_BOX_H
#define PYBIND_STA_DUMP_BOX_H

#include <starters/sta_dump_box.h>
#include <pybind/starters/py_starter.h>

//! Function to bind StaDumpBox class to Python.
static void pybind_sta_dump_box(py::module &m)
{
  py::class_<StaDumpBox,PyUpdater<StaDumpBox>,StaDump,Starter,Updater,ShPtr<StaDumpBox>>(m, "StaDumpBox")
    .def(py::init<const Str &, int>());
}

#endif