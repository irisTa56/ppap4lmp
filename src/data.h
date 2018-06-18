/* ---------------------------------------------------------------------
This file is for Data class.

create: 2018/06/12 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef DATA_H
#define DATA_H

#include <map>
#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

#include <Eigen/LU>

class Data {
 public:
  Data() = default;
  virtual ~Data() = default;
  int get_i(const std::string &);
  double get_d(const std::string &);
  const Eigen::VectorXi &get_iv(const std::string &);
  const Eigen::VectorXd &get_dv(const std::string &);
  const Eigen::ArrayXXi &get_ia(const std::string &);
  const Eigen::ArrayXXd &get_da(const std::string &);
 protected:
  void set_i(const std::string &, int);
  void set_d(const std::string &, double);
  void set_iv(const std::string &, const Eigen::VectorXi &);
  void set_dv(const std::string &, const Eigen::VectorXd &);
  void set_ia(const std::string &, const Eigen::ArrayXXi &);
  void set_da(const std::string &, const Eigen::ArrayXXd &);
  std::map<std::string,int> prop_i;               // property name -> value (integer)
  std::map<std::string,double> prop_d;            // property name -> value (double)
  std::map<std::string,Eigen::VectorXi> prop_iv;  // property name -> value (integer vector)
  std::map<std::string,Eigen::VectorXd> prop_dv;  // property name -> value (double vector)
  std::map<std::string,Eigen::ArrayXXi> prop_ia;  // property name -> value (2D integer array)
  std::map<std::string,Eigen::ArrayXXd> prop_da;  // property name -> value (2D double array)
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_data(py::module &m) {

  py::class_<Data>(m, "Data")
    .def(py::init<>())
    .def(
      "get_i", &Data::get_i,
      py::return_value_policy::reference_internal)
    .def(
      "get_d", &Data::get_d,
      py::return_value_policy::reference_internal)
    .def(
      "get_iv", &Data::get_iv,
      py::return_value_policy::reference_internal)
    .def(
      "get_dv", &Data::get_dv,
      py::return_value_policy::reference_internal)
    .def(
      "get_ia", &Data::get_ia,
      py::return_value_policy::reference_internal)
    .def(
      "get_da", &Data::get_da,
      py::return_value_policy::reference_internal);

}

#endif
