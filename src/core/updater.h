/* ---------------------------------------------------------------------
Updater: is an abstract class to update data held by Generator.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef UPDATER_H
#define UPDATER_H

#include <omp.h>

#include <core/generators.h>

class Updater {
  Set<int> dataid_blacklist;
  omp_lock_t omp_lock;
 protected:
  ShPtr<Generator> ext_generator;
  virtual void compute_impl(Json &, DataKeys &) = 0;
  bool check_blacklist(
    const int dataid);
 public:
  Updater();
  virtual ~Updater() = default;
  virtual void compute(Json &, DataKeys &, const int) = 0;
  void remove_from_blacklist(
    const int dataid);
  const ShPtr<Generator> &get_ext_generator();
};

#endif