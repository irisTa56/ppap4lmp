/*!
  @file src/starters/sta_dump_atoms.h
  @brief This file has a definition of StaDumpAtoms class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef STA_DUMP_ATOMS_H
#define STA_DUMP_ATOMS_H

#include <starters/sta_dump.h>

/*!
  @brief StaDumpAtoms reads a Lammps' dump file
  and sets properties for atoms.

  An object of this class reads properties of atoms
  from a Lammps' dump file specified by #filepath.
  Note that only properties at a time specified by #timestep are read.

  About usage in Python,
  please see pybind::py_sta_dump_atoms.
*/
class StaDumpAtoms : public StaDump {
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - Keys to be set are names of dumped Lammps' atom property.
          In a Lammps' dump file, the names are printed in a line
          beginning with `ITEM: ATOMS`.
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    JsonToVoidFunc check_required_keys,
    JsonToBoolFunc check_optional_keys) override;
 public:
  using StaDump::StaDump;
  virtual ~StaDumpAtoms() = default;
};

#endif