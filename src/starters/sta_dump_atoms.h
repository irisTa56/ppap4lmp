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
  @details This class inherits StaDump class and overrides
  StaDump::compute_impl.

  An object of this class reads properties of atoms
  from a Lammps' dump file specified by #filepath.
  Note that only properties at a time specified by #timestep are read.

  About usage in Python,
  please see src/pybind/starters/py_sta_dump_atoms.h.

  Keys to be set are names of dumped Lammps' atom property.
  In a Lammps' dump file, the names are printed in a line
  beginning with <c>ITEM: ATOMS</c>.
*/
class StaDumpAtoms : public StaDump {
  /*!
    @brief Make a list whether each value printed in a line of
    a Lammps' dump file is an integer or not.
    @param line : The first line in a body of a Lammps' dump file:
    a line below the line beginning with <c>ITEM: ATOMS</c>.
    @return ::Vec of booleans whether each value in the \c line is
    an integer or not.
  */
  const Vec<bool> make_is_int_vector(
    const Str &line);
 protected:
  /*!
    @copydoc StaCopy::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  //! Constructor of StaDumpAtoms class (inherited).
  using StaDump::StaDump;
  virtual ~StaDumpAtoms() = default;
};

#endif