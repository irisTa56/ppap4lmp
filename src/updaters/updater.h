/* ---------------------------------------------------------------------
Updater: is an abstract class to update data held by Generator.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef UPDATER_H
#define UPDATER_H

#include <generators/generator.h>
#include <key_checker.h>

class Updater : public KeyChecker {
  Set<int> dataid_blacklist;
  omp_lock_t omp_lock;
 protected:
  ShPtr<Generator> ext_generator;
  virtual void compute_impl(Json &, Set<Str> &) = 0;
  const bool check_blacklist(
    int dataid);
 public:
  Updater() { omp_init_lock(&omp_lock); }
  virtual ~Updater() = default;
  virtual void compute(Json &, Set<Str> &, int) = 0;
  void remove_from_blacklist(
    int dataid);
  ShPtr<Generator> get_ext_generator();
};

#endif