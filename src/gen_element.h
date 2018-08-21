/* ---------------------------------------------------------------------
GenElement: stands for Generator containing data 'element'.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_ELEMENT_H
#define GEN_ELEMENT_H

#include "generator.h"

class GenElement : public Generator, public EnableShThis<GenElement> {
  static int instance_count;
  int ID;
  int n_remain = 0;
  Json data = nullptr;
  Set<Str> datakeys;
  omp_lock_t omp_lock;
 public:
  GenElement();
  virtual ~GenElement() = default;
  virtual ShPtr<GenElement> get_element(
    Json name = nullptr) override;
  virtual ShPtr<Generator> get_generator(
    Json name = nullptr) override;
  void increment_remain();
  void decrement_remain();
  void update_data(
    ShPtr<Updater> upd);
  ShPtr<GenElement> append_updater(
    ShPtr<Updater> upd);
  const Json &get_data();
  const Set<Str> &get_keys();
  ArrayXi get_1d_int(
    const Str &key);
  ArrayXd get_1d_double(
    const Str &key);
  ArrayXXi get_2d_int(
    const List<Str> &keys);
  ArrayXXd get_2d_double(
    const List<Str> &keys);
  const Json &get_data_py();
  const Set<Str> &get_keys_py();
  const ArrayXi get_1d_int_py(
    const Str &key);
  const ArrayXd get_1d_double_py(
    const Str &key);
  const ArrayXXi get_2d_int_py(
    const List<Str> &keys);
  const ArrayXXd get_2d_double_py(
    const List<Str> &keys);
};

/* ------------------------------------------------------------------ */
// for pybind11

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
