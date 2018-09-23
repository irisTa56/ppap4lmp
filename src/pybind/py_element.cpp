/*!
  @file src/pybind/py_element.cpp
  @brief This file is for binding Element class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_element.h"
#include "../core/updater.h"

void pybind::py_element(py::module &m)
{
  /* NOTE:
    The below function is required to make an UpdatePair object
    from shared pointers of the created Element object
    and the taken Starter's subclass object;
    because a constructor cannot call shared_from_this()
    and therefore cannot make an UpdatePair object.
  */
  m.def(
    "create",
    [](ShPtr<Updater> upd)
    {
      return ElPtr(new Element())->append_updater(upd);
    }
  );

  py::class_<
    Element,PyElement,ElPtr>(m, "Element")
    .def(py::init<>())
    .def(
      "append_updater",
      &Element::append_updater)
    .def(
      "get_data",
      &Element::get_data_py)
    .def(
      "get_keys",
      &Element::get_keys_py)
    .def(
      "get_1d_int",
      &Element::get_1d_int_py)
    .def(
      "get_1d_float",
      &Element::get_1d_float_py)
    .def(
      "get_2d_int",
      &Element::get_2d_int_py)
    .def(
      "get_2d_float",
      &Element::get_2d_float_py);
}
