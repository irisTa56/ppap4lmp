/*!
  @file src/starters/sta_molecules.h
  @brief This file has a definition of StaMolecules class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/07/07
*/

#ifndef STA_MOLECULES_H
#define STA_MOLECULES_H

#include <starters/starter.h>

/*!
  @brief StaMolecules sets properties for molecules
  using atoms forming the molecules.
  @details This class inherits Starter class and overrides
  Starter::compute_impl.

  An object of this class owns an Element object for atoms
  forming molecules to be computed.
  Note that if molecular types are required elsewhere,
  one needs to add \c type property using an Adder object,
  such as an AddMap object.

  About usage in Python,
  please see src/pybind/starters/py_sta_molecules.h.

  Key of property to be added:
    - \c id (integer)
    - \c atom-ids (array of integers)

  Key of required property in #ext_generator:
    - \c id (integer)
    - \c mol (integer)
*/
class StaMolecules : public Starter {
 protected:
  /*!
    @copydoc StaCopy::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of StaMolecules class.
    @param el_atoms : Shared pointer to an Element object for atoms
    forming molecules to be computed.
    This argument is assigned to #ext_generator.
  */
  StaMolecules(
    const ElPtr &el_atoms);
  virtual ~StaMolecules() = default;
};

#endif