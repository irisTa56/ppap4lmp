#ifndef PYBIND_GEN_ELEMENT_H
#define PYBIND_GEN_ELEMENT_H

#include <generators/gen_element.h>

// trampoline class to bind Python
class PyGenElement : public GenElement {
 public:
  using GenElement::GenElement;
  ShPtr<GenElement> get_element(
    Json name) override
  {
    PYBIND11_OVERLOAD(
      ShPtr<GenElement>, GenElement, get_element, name);
  }
  ShPtr<Generator> get_generator(
    Json name) override
  {
    PYBIND11_OVERLOAD(
      ShPtr<Generator> , GenElement, get_generator, name);
  }
};

static void pybind_gen_element(py::module &m)
{
  py::class_<
    GenElement,PyGenElement,ShPtr<GenElement>>(m, "GenElement")
    .def(py::init<>())
    .def("append_updater", &GenElement::append_updater)
    .def("get_data", &GenElement::get_data_py)
    .def("get_keys", &GenElement::get_keys_py)
    .def("get_1d_int", &GenElement::get_1d_int_py)
    .def("get_1d_double", &GenElement::get_1d_double_py)
    .def("get_2d_int", &GenElement::get_2d_int_py)
    .def("get_2d_double", &GenElement::get_2d_double_py);

  /* NOTE:
    this fucntion is necessary because shared_from_this() cannot be
    called in the constructor
  */
  m.def(
    "Element",
    [](ShPtr<Updater> upd)
    {
      return ShPtr<GenElement>(
        new GenElement())->append_updater(upd);
    });
}

#endif
