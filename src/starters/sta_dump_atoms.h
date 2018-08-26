/* ---------------------------------------------------------------------
StaDumpAtoms: stands for Starter reading lammps' Dump file and
extracting Atoms data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_DUMP_ATOMS_H
#define STA_DUMP_ATOMS_H

#include <starters/sta_dump.h>

class StaDumpAtoms : public StaDump {
  const Vec<bool> make_is_int_vector(
    const Str &line);
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  using StaDump::StaDump;
  virtual ~StaDumpAtoms() = default;
};

#endif