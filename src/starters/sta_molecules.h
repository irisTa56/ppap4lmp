/* ---------------------------------------------------------------------
StaMolecules: stands for Starter to generate Molecules from atoms.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_MOLECULES_H
#define STA_MOLECULES_H

#include <starters/starter.h>

class StaMolecules : public Starter {
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  StaMolecules(
    ShPtr<Element> gen_atoms);
  virtual ~StaMolecules() = default;
};

#endif