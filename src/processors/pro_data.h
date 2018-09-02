/* ---------------------------------------------------------------------
ProData: stands for Processor which returns Data itself.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_DATA_H
#define PRO_DATA_H

#include <processors/processor.h>

class ProData : public Processor {
  List<Str> selected_keys;
  List<Json> results;
 protected:
  virtual void run_impl(
    int index) override;
 public:
  ProData(
    ShPtr<Element> elem);
  ProData(
    List<ShPtr<Element>> elems);
  virtual ~ProData() = default;
  virtual void prepare() override;
  void select(
    py::args);
  const List<Json> &get_results();
};

#endif
