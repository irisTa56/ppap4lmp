/*!
  @file src/pybind/py_adders/add_com_position.h
  @brief This file is for binding AddCoMPosition class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/13
  @details

  <table class="py_table">
    <caption>
      Python-side constructor of AddCoMPosition
    </caption>
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %AddCoMPosition</td>
      <td class="py_td">AddCoMPosition::AddCoMPosition</td>
      <td class="py_td">
        Constructor of AddCoMPosition class.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c elem : \e Child object (such as an Element object
            containing data for atoms).
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed AddCoMPosition object, which is appended to
        a \e parent object (such as an Element object containing data
        for molecules).
      </td>
    </tr>
  </table>

  Usage example of the constructor to add \c xu, \c yu and \c zu
  property to an Element object for molecules.

  \code{.python}
    atoms = create(...)
    molecules = create(StaMolecules(atoms))

    molecules.append_updater(AddCoMPosition(atoms))
  \endcode
*/

#ifndef PYBIND_ADD_COM_POSITION_H
#define PYBIND_ADD_COM_POSITION_H

#include <adders/add_com_position.h>
#include <pybind/adders/py_adder.h>

//! Function to bind AddCoMPosition class to Python.
static void pybind_add_com_position(py::module &m)
{
  py::class_<AddCoMPosition,PyUpdater<AddCoMPosition>,Adder,Updater,ShPtr<AddCoMPosition>>(m, "AddCoMPosition")
    .def(py::init<const ElPtr &>());
}

#endif