/* ---------------------------------------------------------------------
GenList: stands for Generator List containing elements.

create: 2018/07/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_LIST_H
#define GEN_LIST_H

#include "generator.h"

class GenList : public Generator {
  List<ShPtr<Generator>> generator_list;
 public:
  GenList(const List<ShPtr<Generator>> &);
  virtual ~GenList() = default;
  virtual ShPtr<GenElement> get_element(Json name = nullptr) override;
  virtual ShPtr<Generator> get_generator(Json name = nullptr) override;
  const int get_length();
};

#endif
