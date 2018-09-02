/* ---------------------------------------------------------------------
Processor: is an abstract class to process data.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PROESSOR_H
#define PROESSOR_H

#include <core/generators.h>
#include <key_checker.h>

class Processor : public KeyChecker {
  int i_generator = 0;
 protected:
  int n_generators;
  List<ShPtr<Generator>> generators;
  virtual void run_impl(int) = 0;
  template <class GEN>
  void register_generator(
    ShPtr<GEN> gen);
  template <class GEN>
  void register_generators(
    const List<ShPtr<GEN>> &gens);
 public:
  Processor() = default;
  virtual ~Processor() = default;
  virtual void prepare() {}
  virtual void finish() {}
  virtual bool run();
};

#endif
