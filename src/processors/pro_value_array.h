/* ---------------------------------------------------------------------
ProValueArray: stands for Processor returning selected (double) Values
contained in Arrays.

create: 2018/07/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_VALUE_ARRAY_H
#define PRO_VALUE_ARRAY_H

#include <processors/processor.h>

class ProValueArray : public Processor {
  Vec<Str> selected_keys;
  Map<Str,ArrayXXd> results;
  Map<Str,Vec<RowArrayXd>> results_trajs;
 protected:
  virtual void run_impl(
    const int index) override;
 public:
  ProValueArray(
    const ShPtr<Element> &elem);
  ProValueArray(
    const Vec<ShPtr<Element>> &elems);
  virtual ~ProValueArray() = default;
  virtual void prepare() override;
  virtual void finish() override;
  void select(
    const py::args &args);
  const Map<Str,ArrayXXd> &get_results();
};

#endif
