/*!
  @file src/pybind/filters/py_fil_set.h
  @brief This file is for binding FilSet class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/01
*/

#ifndef PYBIND_FIL_SET_H
#define PYBIND_FIL_SET_H

#include <filters/fil_set.h>
#include <pybind/filters/py_filter.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind FilSet class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of FilSet
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          FilSet::FilSet
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief FilSet::FilSet
          @copydetails FilSet::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails FilSet::FilSet
        </td>
      </tr>
    </table>

    Usage example of the constructor for a filter removing atoms
    whose `type` property is not 1, 2, or 3.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    atoms.append_updater(FilSet({"type": {1, 2, 3}}))
    </code></pre>
    @endhtmlonly

    Usage example of the constructor for a filter removing atoms
    except for those of which `type` property is 1, 2, or 3,
    and `id` property is a multiple of 3 less than 1000.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    atoms.append_updater(FilSet({
      "type": {1, 2, 3},
      "id": set(range(3, 1000, 3))
    }))
    </code></pre>
    @endhtmlonly
  */
  void py_fil_set(py::module &m);
}

#endif