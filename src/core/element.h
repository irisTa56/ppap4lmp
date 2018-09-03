/* ---------------------------------------------------------------------
Element: stands for Generator containing data 'element'.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ELEMENT_H
#define ELEMENT_H

#include <omp.h>

#include <alias/eigen.h>
#include <alias/pybind.h>
#include <generators/generator.h>
#include <class/data_keys.h>

class Element : public Generator, public EnShThis<Element> {
  static int instance_count;
  int n_remain = 0;
  int dataid;
  Json data;
  DataKeys datakeys;
  omp_lock_t omp_lock;
  void increment_remain();
  void decrement_remain();
  void update_data(
    const ShPtr<Updater> &upd);
  /* NOTE:
    To use methods (increment_remain, decrement_remain, update_data),
    Generator needs to be a friend class.
  */
  friend class Generator;
 public:
  Element();
  virtual ~Element() = default;
  virtual ShPtr<Element> get_element(
    const Json &name = nullptr) override;
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  ShPtr<Element> append_updater(
    const ShPtr<Updater> &upd);
  const Json &get_data();
  /* NOTE:
    If get_data() takes an argument, it does not return a reference.
  */
  Json get_data(
    const Json &key_);
  const DataKeys &get_keys();
  template <typename T>
  void array1d(
    T &array,
    const Str &key);
  template <typename T>
  void array2d(
    T &array,
    const Vec<Str> &keys);
// wrappers for DataKeys' methods
  void required(
    const Json &key_);
  bool optional(
    const Json &key_);
// functions for Python
  const Json &get_data_py();
  const Set<Str> &get_keys_py();
  ArrayXi get_1d_int_py(
    const Str &key);
  ArrayXd get_1d_float_py(  // float in Python, double in C++
    const Str &key);
  ArrayXXi get_2d_int_py(
    const py::args &args);
  ArrayXXd get_2d_float_py(  // float in Python, double in C++
    const py::args &args);
 private:
  void init_for_python();
};

using ElPtr = ShPtr<Element>;

#endif
