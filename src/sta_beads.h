/* ---------------------------------------------------------------------
StaBeads: stands for Starter to generate Beads from molecules.

create: 2018/08/18 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_BEADS_H
#define STA_BEADS_H

#include "starter.h"

class StaBeads : public Starter {
  bool with_type;
  bool with_weights;
  Dict<int,List<Json>> mol_type_to_abst_beads;
  void check_mol_type_to_abst_beads();
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

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_sta_beads(py::module &m)
{
  py::class_<StaBeads,PyUpdater<StaBeads>,Starter,Updater,ShPtr<StaBeads>>(m, "StaBeads")
    .def(py::init<ShPtr<GenElement>,const List<Json> &>())
    .def(py::init<ShPtr<GenElement>,const Dict<int,List<Json>> &>());
}

#endif