/*!
  @file src/pybind/adders/py_add_map.h
  @brief This file is for binding AddMap class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/26
*/

#ifndef PYBIND_ADD_MAP_H
#define PYBIND_ADD_MAP_H

#include <adders/add_map.h>
#include <pybind/adders/py_adder.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind AddMap class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of AddMap
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          AddMap::AddMap
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief AddMap::AddMap
          @copydetails AddMap::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails AddMap::AddMap
        </td>
      </tr>
    </table>

    Usage example of the constructor for mapping
    from <c>atomic-number</c> to \c mass.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    my_mapping = AddMap(
      "atomic-number", "mass",
      {
        6: 12.011,
        8: 15.999,
        9: 18.998
      }
    )
    </code></pre>
    @endhtmlonly

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of AddMap
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">\c overwrite</td>
        <td class="py_method">AddMap::overwrite</td>
        <td class="py_method">
          @copybrief AddMap::overwrite
        </td>
        <td class="py_method">
          @copydetails AddMap::overwrite
        </td>
        <td class="py_method">
          This AddMap object.
        </td>
      </tr>
    </table>
  */
  void py_add_map(py::module &m);
}

#endif