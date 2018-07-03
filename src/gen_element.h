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
  virtual const nlohmann::json &get_data() override;
  virtual const bool check_key(
    const std::string &) override;
  virtual const std::vector<bool> check_keys(
    const std::vector<std::string> &) override;
  virtual const Eigen::VectorXi get_int_vector(
    const std::string &) override;
  virtual const Eigen::VectorXd get_double_vector(
    const std::string &) override;
  virtual const Eigen::ArrayXXi get_int_array(
    const std::vector<std::string> &) override;
  virtual const Eigen::ArrayXXd get_double_array(
    const std::vector<std::string> &) override;
  std::shared_ptr<Generator> set_initial_updater(
    std::shared_ptr<Updater>);
  std::shared_ptr<Generator> append_updater(
    std::shared_ptr<Updater>);
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_gen_element(py::module &m)
{
  py::class_<GenElement,PyGenerator<GenElement>,Generator,std::shared_ptr<GenElement>>(m, "GenElement")
    .def(py::init<>())
    .def("get_data", &GenElement::get_data,
      py::return_value_policy::reference_internal)
    .def("append_updater", &GenElement::append_updater)
    .def("check_key", &GenElement::check_key)
    .def("check_keys", &GenElement::check_keys)
    .def("get_int_vector", &GenElement::get_int_vector)
    .def("get_double_vector", &GenElement::get_double_vector)
    .def("get_int_array", &GenElement::get_int_array)
    .def("get_double_array", &GenElement::get_double_array);

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
