/*!
  @file src/pybind/processors/py_pro_data.h
  @brief This file is for binding ProData class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/22
*/

#ifndef PYBIND_PRO_DATA_H
#define PYBIND_PRO_DATA_H

#include <processors/pro_data.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind ProData class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of ProData
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProData::ProData
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief ProData::ProData(const ElPtr &)
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProData::ProData(const ElPtr &)
        </td>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          ProData::ProData
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief ProData::ProData(const Vec<ElPtr> &)
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails ProData::ProData(const Vec<ElPtr> &)
        </td>
      </tr>
    </table>

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of ProData
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c select</td>
        <td class="py_method">ProData::select</td>
        <td class="py_method">
          @copybrief ProData::select
        </td>
        <td class="py_method">
          @copydetails ProData::select
        </td>
        <td class="py_method">
          None.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c get_results</td>
        <td class="py_method">ProData::get_results</td>
        <td class="py_method">
          @copybrief ProData::get_results
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          List of ::Json objects (complex of dictionary and list).
        </td>
      </tr>
    </table>
  */
  void py_pro_data(py::module &m);
}

#endif
