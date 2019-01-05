/*!
  @file src/pybind/filters/py_fil_comparison.h
  @brief This file is for binding FilComparison class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/02
*/

#ifndef PYBIND_FIL_COMPARISON_H
#define PYBIND_FIL_COMPARISON_H

#include <filters/fil_comparison.h>
#include <pybind/filters/py_filter.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind FilComparison class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side constructor of FilComparison
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">C++</th>
        <th class="py_constructor" colspan="2">Description</th>
        <th class="py_constructor" colspan="2">Parameters</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          FilComparison::FilComparison
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief FilComparison::FilComparison(
            const std::tuple<Str,Str,Json> &)
          @copydetails FilComparison::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails FilComparison::FilComparison(
            const std::tuple<Str,Str,Json> &)
        </td>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">
          FilComparison::FilComparison
        </td>
        <td class="py_constructor" colspan="2">
          @copybrief FilComparison::FilComparison(
            const Vec<std::tuple<Str,Str,Json>> &)
          @copydetails FilComparison::compute_impl
        </td>
        <td class="py_constructor" colspan="2">
          @copydetails FilComparison::FilComparison(
            const Vec<std::tuple<Str,Str,Json>> &)
        </td>
      </tr>
    </table>

    Usage example of the constructor for a filter removing atoms
    whose `xu` property is less than 10.0.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    atoms.append_updater(FilComparison(("xu", ">=", 10.0)))
    </code></pre>
    @endhtmlonly

    Usage example of the constructor for a filter removing atoms
    except for those of which `xu` property is greater than 10.0
    and less than 20.0, and `charge` property is equal to -1.0.

    @htmlonly
    <pre class="prettyprint"><code class="lang-py"># python

    atoms = create(StaDumpAtoms("path/to/dump", 0))
    atoms.append_updater(FilComparison([
      ("xu", ">", 10.0),
      ("xu", "<", 20.0),
      ("charge", "==", -1.0)
    ]))
    </code></pre>
    @endhtmlonly
  */
  void py_fil_comparison(py::module &m);
}

#endif