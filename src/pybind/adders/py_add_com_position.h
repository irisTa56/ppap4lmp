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
          - \c elem : \e A child object (such as an Element object
            containing data for atoms).
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

    @code{.python}
      atoms = create(...)
      molecules = create(StaMolecules(atoms))

      molecules.append_updater(AddCoMPosition(atoms))
    @endcode
  */
  void py_add_com_position(py::module &m);
}

#endif