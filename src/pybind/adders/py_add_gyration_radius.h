/*!
  @file src/pybind/adders/py_add_gyration_radius.h
  @brief This file is for binding AddGyrationRadius class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/15
*/

#ifndef PYBIND_ADD_GYRATION_RADIUS_H
#define PYBIND_ADD_GYRATION_RADIUS_H

#include <adders/add_gyration_radius.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddGyrationRadius class to Python.
    @param m : A mutable reference to Python module.
    @return None.
    @details
    <table class="py_table">
      <caption>
        Python-side constructor of AddGyrationRadius
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %AddGyrationRadius</td>
        <td class="py_td">AddGyrationRadius::Updater</td>
        <td class="py_td">
          Constructor of AddGyrationRadius class.
        </td>
        <td class="py_td">
          None.
        </td>
        <td class="py_td">
          Constructed AddGyrationRadius object, which is appended to
          an Element object (such as one containing data for molecules).
        </td>
      </tr>
    </table>

    Usage example of the constructor to add square of gyration radius
    to an Element object for molecules.

    @code{.python}
      atoms = create(...)
      molecules = create(StaMolecules(atoms))

      molecules.append_updater(AddCoMPosition(atoms))
      molecules.append_updater(AddInertiaMoment(atoms))
      molecules.append_updater(AddGyrationRadius())
    @endcode

    <table class="py_table">
      <caption>
        Python-side methods of AddGyrationRadius
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c with_sqrted</td>
        <td class="py_td">AddGyrationRadius::with_sqrted</td>
        <td class="py_td">
          @copybrief AddGyrationRadius::with_sqrted
          Note that an average gyration radius should be computed
          by square rooting an average of squared gyration radius,
          not averaging the gyration radius itself.
        </td>
        <td class="py_td">
          - \c add_sqrted_ : A boolean, whether gyration radius is
          computed or not (default is \c True).
        </td>
        <td class="py_td">
          This AddGyrationRadius object.
        </td>
      </tr>
    </table>
  */
  void py_add_gyration_radius(py::module &m);
}

#endif