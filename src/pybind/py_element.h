/*!
  @file src/pybind/py_element.h
  @brief This file is for binding Element class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/01
*/

#ifndef PYBIND_ELEMENT_H
#define PYBIND_ELEMENT_H

#include <alias/pybind.h>
#include <core/element.h>

/*!
  @brief Trampoline class to bind Element class to Python.

  For more details, please see pybind11 documentation:
  https://pybind11.readthedocs.io/en/stable/advanced/classes.html.
*/
class PyElement : public Element {
 public:
  using Element::Element;
  ElPtr get_element(
    const Json &name) override
  {
    PYBIND11_OVERLOAD(
      ElPtr, Element, get_element, name);
  }
  ShPtr<Generator> get_generator(
    const Json &name) override
  {
    PYBIND11_OVERLOAD(
      ShPtr<Generator>, Element, get_generator, name);
  }
  void accessed_by_instance_of(
    const Str &classname) override
  {
    PYBIND11_OVERLOAD(
      void, Element, accessed_by_instance_of, classname);
  }
};

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  /*!
    @brief Bind Element class to Python.
    @param m : A mutable reference to Python module.
    @return None.

    Constructor of Element class is hidden from Python.
    A Python-side function \b create provides functionality
    to create an Element object taking a Starter's subclass object
    as its parameter.

    <table class="py_constructor">
      <caption class="py_constructor">
        Python-side functions
      </caption>
      <tr class="py_constructor">
        <th class="py_constructor">Name</th>
        <th class="py_constructor">C++</th>
        <th class="py_constructor">Description</th>
        <th class="py_constructor">Parameters</th>
        <th class="py_constructor">Return</th>
      </tr>
      <tr class="py_constructor">
        <td class="py_constructor">`create`</td>
        <td class="py_constructor">
          Lambda function defined in pybind::py_element
        </td>
        <td class="py_constructor">
          Factory function for Element class.
        </td>
        <td class="py_constructor">
          @param upd
            An object of Starter's subclass, which sets some properties
            to empty Element::data of the created Element object.
            Note that `upd` can be an Element or ::Json object:
            StaCopy and StaCustom are implicitly used for Element
            and ::Json, respectively.
        </td>
        <td class="py_constructor">
          An object of Element class.
        </td>
      </tr>
    </table>

    <table class="py_method">
      <caption class="py_method">
        Python-side methods of Element
      </caption>
      <tr class="py_method">
        <th class="py_method">Name</th>
        <th class="py_method">C++</th>
        <th class="py_method">Description</th>
        <th class="py_method">Parameters</th>
        <th class="py_method">Return</th>
      </tr>
      <tr class="py_method">
        <td class="py_method">`append_updater`</td>
        <td class="py_method">Element::append_updater</td>
        <td class="py_method">
          @copybrief Element::append_updater
        </td>
        <td class="py_method">
          @copydetails Element::append_updater
        </td>
        <td class="py_method">
          This Element object.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">`get_data`</td>
        <td class="py_method">Element::get_data_py</td>
        <td class="py_method">
          @copybrief Element::get_data_py
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          A ::Json object (complex of dictionary and list).
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">`get_keys`</td>
        <td class="py_method">Element::get_keys_py</td>
        <td class="py_method">
          @copybrief Element::get_keys_py
        </td>
        <td class="py_method">
          None.
        </td>
        <td class="py_method">
          Set of strings.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">`get_1d_int`</td>
        <td class="py_method">Element::get_1d_int_py</td>
        <td class="py_method">
          @copybrief Element::get_1d_int_py
        </td>
        <td class="py_method">
          @copydetails Element::get_1d_int_py
        </td>
        <td class="py_method">
          One-dimensional Numpy-Array of which elements are integers.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">`get_1d_float`</td>
        <td class="py_method">Element::get_1d_float_py</td>
        <td class="py_method">
          @copybrief Element::get_1d_float_py
        </td>
        <td class="py_method">
          @copydetails Element::get_1d_float_py
        </td>
        <td class="py_method">
          One-dimensional Numpy-Array of which elements are floats.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">`get_2d_int`</td>
        <td class="py_method">Element::get_2d_int_py</td>
        <td class="py_method">
          @copybrief Element::get_2d_int_py
        </td>
        <td class="py_method">
          @copydetails Element::get_2d_int_py
        </td>
        <td class="py_method">
          Two-dimensional Numpy-Array of which elements are integers.
        </td>
      </tr>
      <tr class="py_method">
        <td class="py_method">`get_2d_float`</td>
        <td class="py_method">Element::get_2d_float_py</td>
        <td class="py_method">
          @copybrief Element::get_2d_float_py
        </td>
        <td class="py_method">
          @copydetails Element::get_2d_float_py
        </td>
        <td class="py_method">
          Tow-dimensional Numpy-Array of which elements are floats.
        </td>
      </tr>
    </table>
  */
  void py_element(py::module &m);
}

#endif
