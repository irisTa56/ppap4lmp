/* ---------------------------------------------------------------------
Filter: is an abstract class to filter data.

create: 2018/06/30 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef FILTER_H
#define FILTER_H

#include <updaters/updater.h>

class Filter : public Updater {
 public:
  Filter(
    ShPtr<Element> elem);
  using Updater::Updater;
  virtual ~Filter() = default;
  virtual void compute(
    Json &data,
    Set<Str> &datakeys,
    int dataid) override;
};

#endif