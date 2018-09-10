#ifndef PYBIND_ELEMENT_H
#define PYBIND_ELEMENT_H

#include <alias/pybind.h>
#include <core/element.h>

// trampoline class to bind Python
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

static void pybind_element(py::module &m)
{
  py::class_<
    Element,PyElement,ElPtr>(m, "Element")
    .def(py::init<>())
    .def("append_updater", &Element::append_updater)
    .def("get_data", &Element::get_data_py)
    .def("get_keys", &Element::get_keys_py)
    .def("get_1d_int", &Element::get_1d_int_py)
    .def("get_1d_float", &Element::get_1d_float_py)
    .def("get_2d_int", &Element::get_2d_int_py)
    .def("get_2d_float", &Element::get_2d_float_py);

  /* NOTE:
    this fucntion is necessary because shared_from_this() cannot be
    called in the constructor
  */
  m.def(
    "create",
    [](ShPtr<Updater> upd)
    {
      return ElPtr(new Element())->append_updater(upd);
    });
}

#endif