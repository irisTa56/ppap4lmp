/* ---------------------------------------------------------------------
Generator: is an abstract class to generate data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <aliases.h>

class Element;
class Updater;

using UpdatePair = std::pair<ShPtr<Element>,ShPtr<Updater>>;

class Generator {
 protected:
  List<UpdatePair> update_chain;
  void merge_update_chain(
    const List<UpdatePair> &new_chain);
 public:
  Generator() = default;
  virtual ~Generator() = default;
  virtual ShPtr<Element> get_element(
    Json name = nullptr) = 0;
  virtual ShPtr<Generator> get_generator(
    Json name = nullptr) = 0;
  void appoint();
  void hello();
  void goodbye();
  const List<UpdatePair> &get_update_chain();
};

#endif
