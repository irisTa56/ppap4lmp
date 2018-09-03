/* ---------------------------------------------------------------------
GenDict: stands for Generator Dictionary containing elements.

create: 2018/07/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_DICT_H
#define GEN_DICT_H

#include <core/element.h>

class GenDict : public Generator {
  Map<Str,ShPtr<Generator>> generator_dict;
 public:
  GenDict(
    const Map<Str,ShPtr<Generator>> &generator_dict_);
  virtual ~GenDict() = default;
  virtual ElPtr get_element(
    const Json &name = nullptr) override;
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  Set<Str> get_keys();
};

#endif
