/*!
  @file src/pybind/adders/py_add_gyration_radius.h
  @brief This file is for binding AddGyrationRadius class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/15
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
        <ul class="py_ul">
          <li>
            None.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed AddGyrationRadius object, which is appended to
        an Element object (such as one containing data for molecules).
      </td>
    </tr>
  </table>
  <br/>
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
      <td class="py_td">\c with_squared</td>
      <td class="py_td">AddGyrationRadius::with_squared</td>
      <td class="py_td">
        Enable to compute square of gyration radius. Note that an
        average gyration radius should be computed by square rooting an
        average of squared gyration radius, not averaging the gyration
        radius itself.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c add_squared_ : A boolean, whether squared gyration
            radius is computed or not. No argument leads to enabling
            the computation.
          </li>
        </ul>
      </td>
      <td class="py_td">
        This AddGyrationRadius object.
      </td>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c without_sqrted</td>
      <td class="py_td">AddGyrationRadius::without_sqrted</td>
      <td class="py_td">
        Disable to compute gyration radius (skipping root-squaring).
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c without_sqrted_ : A boolean, whether computing gyration
            radius is skipped or not. No argument leads to skipping
            the computation.
          </li>
        </ul>
      </td>
      <td class="py_td">
        This AddGyrationRadius object.
      </td>
    </tr>
  </table>

  Usage example of the constructor and method to add square of
  gyration radius to an Element object for molecules.

  \code{.python}
    atoms = create(...)
    molecules = create(StaMolecules(atoms))

    molecules.append_updater(AddCoMPosition(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
    molecules.append_updater(AddGyrationRadius().with_squared())
  \endcode
*/

#ifndef PYBIND_ADD_GYRATION_RADIUS_H
#define PYBIND_ADD_GYRATION_RADIUS_H

#include <adders/add_gyration_radius.h>
#include <pybind/adders/py_adder.h>

//! Function to bind AddGyrationRadius class to Python.
static void pybind_add_gyration_radius(py::module &m)
{
  py::class_<AddGyrationRadius,PyUpdater<AddGyrationRadius>,Adder,Updater,ShPtr<AddGyrationRadius>>(m, "AddGyrationRadius")
    .def(py::init<>())
    .def(
      "with_squared", &AddGyrationRadius::with_squared,
      py::arg("add_squared_") = true)
    .def(
      "without_sqrted", &AddGyrationRadius::without_sqrted,
      py::arg("without_sqrted_") = true);
}

#endif