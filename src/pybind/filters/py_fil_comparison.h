/*!
  @file src/pybind/filters/py_fil_comparison.h
  @brief This file is for binding FilComparison class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/02
  @details

  <table class="py_table">
    <caption>
      Python-side constructor of FilComparison
    </caption>
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %FilComparison</td>
      <td class="py_td">FilComparison::FilComparison</td>
      <td class="py_td">
        Constructor of FilComparison class for one criterion.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c comparison_ : A 3-elements tuple consisting of
            a string key, and comparison operator and right side value
            of an inequality (or equation) used as a criterion.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed FilComparison object.
      </td>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c %FilComparison</td>
      <td class="py_td">FilComparison::FilComparison</td>
      <td class="py_td">
        Constructor of FilComparison class for multiple criteria.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            \c comparisons_ : List of 3-elements tuples. Contents of
            each tuple is the same as for the case of one criterion.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Constructed FilComparison object.
      </td>
    </tr>
  </table>

  Usage example of the constructor for a filter removing atoms
  whose \c xu property is less than 10.0.

  \code{.python}
    atoms = create(...)
    atoms.append_updater(FilComparison(("xu", ">=", 10.0)))
  \endcode

  Usage example of the constructor for a filter removing atoms
  whose \c xu property is less than 10.0 or greater than 20.0,
  and whose \c charge property is not equal to -1.0.

  \code{.python}
    atoms = create(...)
    atoms.append_updater(FilComparison([
      ("xu", ">=", 10.0),
      ("xu", "<=", 20.0),
      ("charge", "==", -1.0)
    ]))
  \endcode
*/

#ifndef PYBIND_FIL_COMPARISON_H
#define PYBIND_FIL_COMPARISON_H

#include <filters/fil_comparison.h>
#include <pybind/filters/py_filter.h>

//! Function to bind FilComparison class to Python.
static void pybind_fil_comparison(py::module &m)
{
  py::class_<FilComparison,PyUpdater<FilComparison>,Filter,Updater,ShPtr<FilComparison>>(m, "FilComparison")
    .def(py::init<const std::tuple<Str,Str,Json> &>())
    .def(py::init<const Vec<std::tuple<Str,Str,Json>> &>());
}

#endif