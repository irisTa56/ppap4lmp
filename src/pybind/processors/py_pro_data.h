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
    @details
    <table class="py_table">
      <caption>
        Python-side constructor of ProData
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %ProData</td>
        <td class="py_td">ProData::ProData</td>
        <td class="py_td">
          Constructor of ProData class for one Element object.
        </td>
        <td class="py_td">
          - \c elem : An Element object to be copied.
          @note this is a note
        </td>
        <td class="py_td">
          Constructed ProData object.
        </td>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c %ProData</td>
        <td class="py_td">ProData::ProData</td>
        <td class="py_td">
          Constructor of ProData class for a sequence
          of Element objects.
        </td>
        <td class="py_td">
          - \c elems : List of Element objects to be copied.
        </td>
        <td class="py_td">
          Constructed ProData object.
        </td>
      </tr>
    </table>

    <table class="py_table">
      <caption>
        Python-side methods of ProData
      </caption>
      <tr class="py_tr">
        <th class="py_th">Name</th>
        <th class="py_th">C++-side</th>
        <th class="py_th">Description</th>
        <th class="py_th">Argument</th>
        <th class="py_th">Return</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c select</td>
        <td class="py_td">ProData::select</td>
        <td class="py_td">
          @copybrief ProData::select
        </td>
        <td class="py_td">
          - \c *args : A variable number of string keys specifying
            properties to be copied.
        </td>
        <td class="py_td">
          None.
        </td>
      </tr>
      <tr class="py_tr">
        <td class="py_td">\c get_results</td>
        <td class="py_td">ProData::get_results</td>
        <td class="py_td">
          @copybrief ProData::get_results
        </td>
        <td class="py_td">
          None.
        </td>
        <td class="py_td">
          List of JSON-like object consisting of copied properties.
        </td>
      </tr>
    </table>
  */
  void py_pro_data(py::module &m);
}

#endif
