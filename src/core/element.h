/* ---------------------------------------------------------------------
Element: stands for Generator containing data 'element'.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ELEMENT_H
#define ELEMENT_H

#include <omp.h>

#include <generators/generator.h>

class Element : public Generator, public EnShThis<Element> {
  static int instance_count;
  int ID;
  int n_remain = 0;
  Json data = nullptr;
  Set<Str> datakeys;
  omp_lock_t omp_lock;
 public:
  Element();
  virtual ~Element() = default;
  virtual ShPtr<Element> get_element(
    Json name = nullptr) override;
  virtual ShPtr<Generator> get_generator(
    Json name = nullptr) override;
  void increment_remain();
  void decrement_remain();
  void update_data(
    ShPtr<Updater> upd);
  ShPtr<Element> append_updater(
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

#endif
