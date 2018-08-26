/* ---------------------------------------------------------------------
Starter: is an abstract class to parse data from a file or other data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STARTER_H
#define STARTER_H

#include <core/updater.h>

class Starter : public Updater {
  void sort_by_id(
    Json &data);
 public:
  using Updater::Updater;
  virtual ~Starter() = default;
  virtual void compute(
    Json &data,
    DataKeys &datakeys,
    const int dataid) override;
};

#endif