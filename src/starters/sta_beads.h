/* ---------------------------------------------------------------------
StaBeads: stands for Starter to generate Beads from molecules.

create: 2018/08/18 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_BEADS_H
#define STA_BEADS_H

#include <starters/starter.h>

class StaBeads : public Starter {
  Dict<int,List<Json>> mol_type_to_abst_beads;
  std::pair<bool,bool> check_mol_type_to_abst_beads();
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  StaBeads(
    ShPtr<GenElement> gen_mols,
    const List<Json> &scheme);
  StaBeads(
    ShPtr<GenElement> gen_mols,
    const Dict<int,List<Json>> &schemes);
  virtual ~StaBeads() = default;
};

#endif