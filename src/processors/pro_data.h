/* ---------------------------------------------------------------------
ProData: stands for Processor which returns Data itself.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_DATA_H
#define PRO_DATA_H

#include <processors/processor.h>

class ProData : public Processor {
  Vec<Str> selected_keys;
  Vec<Json> results;
 protected:
  virtual void run_impl(
    const int index) override;
 public:
  ProData(
    const ShPtr<Element> &elem);
  ProData(
    const Vec<ShPtr<Element>> &elems);
  virtual ~ProData() = default;
  virtual void prepare() override;
  void select(
    const py::args &args);
  const Vec<Json> &get_results();
};

#endif
