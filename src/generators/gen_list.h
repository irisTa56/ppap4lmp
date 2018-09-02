/* ---------------------------------------------------------------------
GenList: stands for Generator List containing elements.

create: 2018/07/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_LIST_H
#define GEN_LIST_H

#include <core/element.h>

class GenList : public Generator {
  List<ShPtr<Generator>> generator_list;
 public:
  GenList(
    const List<ShPtr<Generator>> &generator_list_);
  virtual ~GenList() = default;
  virtual ShPtr<Element> get_element(
    Json name = nullptr) override;
  virtual ShPtr<Generator> get_generator(
    Json name = nullptr) override;
  const int get_length();
};

#endif
