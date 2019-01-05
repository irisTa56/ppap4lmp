/*!
  @file src/pybind/adders/py_add_rename.h
  @brief This file is for binding AddRename class to Python.
  @author Takayuki Kobayashi
  @date 2018/08/17
*/

#ifndef PYBIND_ADD_RENAME_H
#define PYBIND_ADD_RENAME_H

#include <adders/add_rename.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddRename class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddRename
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddRename::AddRename
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief AddRename::AddRename
          @copydetails AddRename::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails AddRename::AddRename
        </td>
      </tr>
    </table>

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of AddRename
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">`overwrite`</td>
        <td class="py_method">AddRename::overwrite</td>
        <td class="py_method">
          @copybrief AddRename::overwrite
        </td>
        <td class="py_method">
          @copydetails AddRename::overwrite
        </td>
        <td class="py_method">
          This AddRename object.
        </td>
      </tr>
    </table>
  */
  void py_add_rename(py::module &m);
}

#endif