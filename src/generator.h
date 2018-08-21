/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <omp.h>

#include "aliases.h"

class GenElement;
class Updater;

using UpdatePair = std::pair<ShPtr<GenElement>,ShPtr<Updater>>;

class Generator {
 protected:
  List<UpdatePair> update_chain;
  void merge_update_chain(
    const List<UpdatePair> &new_chain);
 public:
  Generator() = default;
  virtual ~Generator() = default;
  virtual ShPtr<GenElement> get_element(
    Json name = nullptr) = 0;
  virtual ShPtr<Generator> get_generator(
    Json name = nullptr) = 0;
  void appoint();
  void hello();
  void goodbye();
  const List<UpdatePair> &get_update_chain();
};

#include "gen_element.h"
#include "gen_dict.h"
#include "gen_list.h"
#include "updater.h"

#endif
