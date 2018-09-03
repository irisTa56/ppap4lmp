/* ---------------------------------------------------------------------
Filter: is an abstract class to filter data.

create: 2018/06/30 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef FILTER_H
#define FILTER_H

#include <core/updater.h>

class Filter : public Updater {
 public:
  Filter(
    const ElPtr &elem);
  using Updater::Updater;
  virtual ~Filter() = default;
  virtual void compute(
    Json &data,
    DataKeys &datakeys,
    const int dataid) override;
};

#endif