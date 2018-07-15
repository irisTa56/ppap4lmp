/* ---------------------------------------------------------------------
GenElement: stands for Generator containing data 'element'.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_ELEMENT_H
#define GEN_ELEMENT_H

#include "generator.h"

class GenElement : public Generator {
 public:
  GenElement();
  virtual ~GenElement() = default;
  virtual const json &get_data() override;
  const json &get_data_py();
  virtual ArrayXi get_1d_int(
    const std::string &) override;
  const ArrayXi get_1d_int_py(
    const std::string &);
  virtual ArrayXd get_1d_double(
    const std::string &) override;
  const ArrayXd get_1d_double_py(
    const std::string &);
  virtual ArrayXXi get_2d_int(
    const std::vector<std::string> &) override;
  const ArrayXXi get_2d_int_py(
    const std::vector<std::string> &);
  virtual ArrayXXd get_2d_double(
    const std::vector<std::string> &) override;
  const ArrayXXd get_2d_double_py(
    const std::vector<std::string> &);
  void append_updater(std::shared_ptr<Updater>);
  std::shared_ptr<Generator> set_initial_updater(
    std::shared_ptr<Updater>);
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_gen_element(py::module &m)
{
  py::class_<GenElement,PyGenerator<GenElement>,Generator,std::shared_ptr<GenElement>>(m, "GenElement")
    .def(py::init<>())
    .def("get_data", &GenElement::get_data_py)
    .def("append_updater", &GenElement::append_updater)
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
    [](std::shared_ptr<Updater> upd)
    {
      return std::shared_ptr<GenElement>(
        new GenElement())->set_initial_updater(upd);
    });
}

#endif
