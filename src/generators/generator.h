/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <alias/std.h>
#include <alias/json.h>

class Element;
class Updater;

using UpdatePair = std::pair<ShPtr<Element>,ShPtr<Updater>>;

class Generator {
 protected:
  Vec<UpdatePair> update_chain;
  void merge_update_chain(
    const Vec<UpdatePair> &new_chain);
 public:
  Generator() = default;
  virtual ~Generator() = default;
  virtual ShPtr<Element> get_element(
    const Json &name = nullptr) = 0;
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) = 0;
  void appoint();
  void hello();
  void goodbye();
  const Vec<UpdatePair> &get_update_chain();
};

#endif
