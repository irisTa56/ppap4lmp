/*!
  @file src/pybind/adders/py_add_child_positions.h
  @brief This file is for binding AddChildPositions class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef PYBIND_ADD_CHILD_POSITIONS_H
#define PYBIND_ADD_CHILD_POSITIONS_H

#include <adders/add_child_positions.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddChildPositions class to Python.
    @param m : A mutable reference to Python module.
    @return None.
    @details
    <table class="py_table">
      <caption>
        Python-side constructor of AddChildPositions
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %AddChildPositions</td>
        <td class="py_td">AddChildPositions::AddChildPositions</td>
        <td class="py_td">
          Constructor of AddChildPositions class.
        </td>
        <td class="py_td">
          - \c elem : \e A child object (such as an Element object
            containing data for atoms).
          - \c child_name_ : A string for naming the above child object.
        </td>
        <td class="py_td">
          Constructed AddChildPositions object, which is appended to
          a \e parent object (such as an Element object containing data
          for molecules).
        </td>
      </tr>
    </table>
  */
  void py_add_child_positions(py::module &m);
}

#endif