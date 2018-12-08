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

  An object of this class owns an Element object for atoms
  forming molecules to be computed.
  Note that if molecular types are required elsewhere,
  you need to add \c type property using an Adder's subclass object,
  such as an AddMap object.

  About usage in Python,
  please see pybind::py_sta_molecules.
*/
class StaMolecules : public Starter {
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - \c id : integer
        - <c>atom-ids</c> : array of integers
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of StaMolecules class.

    @param el_atoms
    @parblock
      An Element object for atoms forming molecules to be created.
      <span class="remove_in_table">
        This parameter is assigned to #ext_generator.
      </span>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - \c id : integer
          - \c mol : integer
        </dd>
      </dl>
    @endparblock
  */
  StaMolecules(
    const ElPtr &el_atoms);
  virtual ~StaMolecules() = default;
};

#endif