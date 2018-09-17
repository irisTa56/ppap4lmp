/*!
  @file src/pybind/element.h
  @brief This file is for binding Element class to Python.
  @author Takayuki Kobayashi
  @date 2018/07/01
  @details

  <b>Python-side methods of Element class</b>:
  <table class="py_table">
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c append_updater</td>
      <td class="py_td">Element::append_updater</td>
      <td class="py_td">
        Append an object of Adder's or Filter's subclass to this
        Element object.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            An object of Adder's or Filter's subclass.
          </li>
        </ul>
      </td>
      <td class="py_td">
        This Element object.
      </td>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c get_data</td>
      <td class="py_td">Element::get_data_py</td>
      <td class="py_td">
        Get Element::data of this object as a complex of \e dict and
        \e list.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            None.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Json-like object consisting of \e dict and \e list.
      </td>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c get_keys</td>
      <td class="py_td">Element::get_keys_py</td>
      <td class="py_td">
        Get Element::datakeys of this object as a set of strings.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            None.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Set of strings.
      </td>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c get_1d_int</td>
      <td class="py_td">Element::get_1d_int_py</td>
      <td class="py_td">
        Get values of an integer property contained in Element::data of
        this object as an one-dimensional Numpy-Array.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            String key specifying a property to be extracted.
          </li>
        </ul>
      </td>
      <td class="py_td">
        One-dimensional Numpy-Array whose elements are integers.
      </td>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c get_1d_float</td>
      <td class="py_td">Element::get_1d_float_py</td>
      <td class="py_td">
        Get values of a float property contained in Element::data of
        this object as an one-dimensional Numpy-Array.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            String key specifying a property to be extracted.
          </li>
        </ul>
      </td>
      <td class="py_td">
        One-dimensional Numpy-Array whose elements are floats.
      </td>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c get_2d_int</td>
      <td class="py_td">Element::get_2d_int_py</td>
      <td class="py_td">
        Get values of multiple integer properties contained in
        Element::data of this object as a two-dimensional Numpy-Array.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            A variable number of string keys specifying properties to
            be extracted.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Two-dimensional Numpy-Array whose elements are integers.
      </td>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c get_2d_float</td>
      <td class="py_td">Element::get_2d_float_py</td>
      <td class="py_td">
        Get values of multiple float properties contained in
        Element::data of this object as a two-dimensional Numpy-Array.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            A variable number of string keys specifying properties to
            be extracted.
          </li>
        </ul>
      </td>
      <td class="py_td">
        Two-dimensional Numpy-Array whose elements are floats.
      </td>
    </tr>
  </table>

  <b>Python-side functions</b>:
  <table class="py_table">
    <tr class="py_tr">
      <th class="py_th">Name</th>
      <th class="py_th">C++-side</th>
      <th class="py_th">Description</th>
      <th class="py_th">Argument</th>
      <th class="py_th">Return</th>
    </tr>
    <tr class="py_tr">
      <td class="py_td">\c create</td>
      <td class="py_td">Lambda.</td>
      <td class="py_td">
        Factory function for Element class. This function takes one
        argument, an object of Starter's subclass (such class is
        prefixed by \c Sta) which adds some properties to empty data
        of the created Element object.
      </td>
      <td class="py_td">
        <ul class="py_ul">
          <li>
            An object of Starter's subclass.
          </li>
        </ul>
      </td>
      <td class="py_td">
        An object of Element class.
      </td>
    </tr>
  </table>
*/

#ifndef PYBIND_ELEMENT_H
#define PYBIND_ELEMENT_H

#include <alias/pybind.h>
#include <core/element.h>

/*!
  @brief Trampoline class to bind Element class to Python.
  @details For more details, please see pybind11 documentation:
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
      ShPtr<Generator> , Element, get_generator, name);
  }
};

/*!
  @brief Function to bind Element class to Python.
  @details Constructor of Element class is hidden from Python. A
  Python-side function \b create provides functionality to create an
  object of Element class with an object of Starter's subclass. Such a
  function is required to make ::UpdatePair from shared pointers to the
  created Element object and Starter object taken as the argument;
  because constructor cannot call \c shared_from_this() and therefore
  cannot make ::UpdatePair.
*/
static void pybind_element(py::module &m)
{
  m.def(
    "create",
    [](ShPtr<Updater> starter)
    {
      return ElPtr(new Element())->append_updater(starter);
    },
    R"EOF(
      Factory function for Element class. This function takes one
      argument, an object of Starter's subclass (such class is
      prefixed by 'Sta') which adds some properties to empty data
      of the created Element object.

      # argument
        - An object of Starter's subclass.
      # return
        An object of Element class.
    )EOF"
  );

  py::class_<
    Element,PyElement,ElPtr>(m, "Element")
    .def(py::init<>())
    .def(
      "append_updater",
      &Element::append_updater,
      R"EOF(
        Append an object of Adder's or Filter's subclass to this
        Element object.

        # argument
          - An object of Adder's or Filter's subclass.
        # return
          This Element object.
      )EOF"
    )
    .def(
      "get_data",
      &Element::get_data_py,
      R"EOF(
        Get data of this Element object as a complex of dict and list.

        # argument
          - None.
        # return
          Json-like object consisting of dict and list.
      )EOF"
    )
    .def(
      "get_keys",
      &Element::get_keys_py,
      R"EOF(
        Get datakeys of this Element object as a set of strings.

        # argument
          - None.
        # return
          Set of strings.
      )EOF"
    )
    .def(
      "get_1d_int",
      &Element::get_1d_int_py,
      R"EOF(
        Get values of an integer property contained in data of this
        Element object as an one-dimensional Numpy-Array.

        # argument
          - String key specifying a property to be extracted.
        # return
          One-dimensional Numpy-Array whose elements are integers.
      )EOF"
    )
    .def(
      "get_1d_float",
      &Element::get_1d_float_py,
      R"EOF(
        Get values of a float property contained in data of this
        Element object as an one-dimensional Numpy-Array.

        # argument
          - String key specifying a property to be extracted.
        # return
          One-dimensional Numpy-Array whose elements are floats.
      )EOF"
    )
    .def(
      "get_2d_int",
      &Element::get_2d_int_py,
      R"EOF(
        Get values of multiple integer properties contained  in data
        of this Element object as a two-dimensional Numpy-Array.

        # argument
          - A variable number of string keys specifying properties
            to be extracted.
        # return
          Two-dimensional Numpy-Array whose elements are integers.
      )EOF"
    )
    .def(
      "get_2d_float",
      &Element::get_2d_float_py,
      R"EOF(
        Get values of multiple float properties contained  in data
        of this Element object as a two-dimensional Numpy-Array.

        # argument
          - A variable number of string keys specifying properties
            to be extracted.
        # return
          Two-dimensional Numpy-Array whose elements are floats.
      )EOF"
    );
}

#endif
