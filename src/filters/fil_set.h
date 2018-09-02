/* ---------------------------------------------------------------------
FilSet: stands for Filter using Set of values.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef FIL_SET_H
#define FIL_SET_H

#include <filters/filter.h>

class FilSet : public Filter {
  Dict<Str,Set<Json>> value_sets;
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  FilSet(
    const Dict<Str,Set<Json>> &value_sets_);
  FilSet(
    ShPtr<GenElement> elem,
    const Dict<Str,Set<Json>> &value_sets_);
  virtual ~FilSet() = default;
};

#endif