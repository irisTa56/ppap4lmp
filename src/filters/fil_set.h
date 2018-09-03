/* ---------------------------------------------------------------------
FilSet: stands for Filter using Set of values.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef FIL_SET_H
#define FIL_SET_H

#include <filters/filter.h>

class FilSet : public Filter {
  Map<Str,Set<Json>> value_sets;
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  FilSet(
    const Map<Str,Set<Json>> &value_sets_);
  FilSet(
    const ElPtr &elem,
    const Map<Str,Set<Json>> &value_sets_);
  virtual ~FilSet() = default;
};

#endif