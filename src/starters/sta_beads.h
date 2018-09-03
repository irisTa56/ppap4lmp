/* ---------------------------------------------------------------------
StaBeads: stands for Starter to generate Beads from molecules.

create: 2018/08/18 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_BEADS_H
#define STA_BEADS_H

#include <starters/starter.h>

class StaBeads : public Starter {
  Map<int,Vec<Json>> mol_type_to_abst_beads;
  std::pair<bool,bool> check_mol_type_to_abst_beads();
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  StaBeads(
    const ElPtr &el_mols,
    const Vec<Json> &scheme);
  StaBeads(
    const ElPtr &el_mols,
    const Map<int,Vec<Json>> &schemes);
  virtual ~StaBeads() = default;
};

#endif