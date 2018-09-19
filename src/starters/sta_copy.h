#ifndef STA_COPY_H
#define STA_COPY_H

#include <starters/starter.h>

class StaCopy : public Starter {
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  StaCopy(
    const ElPtr &elem);
  virtual ~StaCopy() = default;
  virtual void compute(
    Json &data,
    DataKeys &datakeys,
    const int dataid) override;
};

#endif