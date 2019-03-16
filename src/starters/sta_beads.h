/*!
  @file src/starters/sta_beads.h
  @brief This file has a definition of StaBeads class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/08/18
*/

#ifndef STA_BEADS_H
#define STA_BEADS_H

#include <starters/starter.h>

/*!
  @brief StaBeads sets properties for beads using mapping
  (coarse-graining) scheme for each molecule.

  An object of this class owns mapping(s) representing coarse-graining
  scheme(s). Each mapping describes how atoms in a molecule are
  allocated to beads. Different mapping schemes are acceptable
  for different molecular types. For each bead, its type
  and weighting factors of atoms belonging to the bead can be set.

  About usage in Python,
  please see pybind/starters/py_sta_beads.
*/
class StaBeads : public Starter {
  /*!
    Coarse-grain mapping schemes for each molecular type.
    Description of coarse-graining is stored in a ::Map (dictionary)
    object from molecular type to a ::Vec (list) object of
    ::Json objects. Each ::Json object corresponds to each bead
    in a molecule of that type, and contains three items:
    `indices-in-mol` is an array of zero-based index of atoms
    in the molecule, `type` is type of the bead, and `weights` is
    an array of floats for weighting factors of atoms.
    The last two items are optional. Length of the two arrays,
    `indices-in-mol` and `weights`, should be the same with
    the number of atoms belonging to the bead.
  */
  Map<int,Vec<Json>> mol_type_to_abst_beads;
  /*!
    Check if #mol_type_to_abst_beads correctly describes
    coarse-grain mapping schemes.

    @return A pair of booleans: the first is whether `type` exists
    or not, the second is whether `weights` exists or not. Note that
    if at least one of ::Json objects in #mol_type_to_abst_beads has
    `type` (or `weights`) property, all the other objects must have
    that property too.
  */
  std::pair<bool,bool> check_mol_type_to_abst_beads();
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - `id` : integer
        - `mol` : integer
        - `atom-ids` : array of integers
        - `type` : integer (optional)
        - `atom-weights` : array of floats (optional)
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data) override;
 public:
  /*!
    @brief Constructor of StaBeads class for
    molecules all of whose `type` property are 1,
    or molecules all of which do not have the property.

    @param el_mols
    @parblock
      A molecular Element object consisting of beads for which
      an Element object is created with this constructed object.
      <span class="remove_in_table">
        This parameter is assigned to #ext_generator.
      </span>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `atom-ids` : array of integers
        </dd>
      </dl>

    @param scheme
      List of ::Json (complex of dictionary and list) objects.
      Each ::Json object corresponds to each bead in a molecule,
      and contains three items: `indices-in-mol` is an array
      of zero-based index of atoms in the molecule, `type` is type
      of the bead, and `weights` is an array of floats for
      weighting factors of atoms.
      <span class="remove_in_table">
        This parameter is stored in #mol_type_to_abst_beads
        as a coarse-graining scheme for molecular type 1.
      </span>
    @endparblock
  */
  StaBeads(
    const ElPtr &el_mols,
    const Vec<Json> &scheme);
  /*!
    @brief Constructor of StaBeads class for multiple molecular types.

    @param el_mols
    @parblock
      A molecular Element object consisting of beads for which
      an Element object is created with this constructed object.
      <span class="remove_in_table">
        This parameter is assigned to #ext_generator.
      </span>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `atom-ids` : array of integers
        </dd>
      </dl>

    @param schemes
      Dictionary from molecular type to list of ::Json
      (complex of dictionary and list) objects.
      Each ::Json object corresponds to each bead in a molecule
      of that type, and contains three items: `indices-in-mol` is
      an array of zero-based index of atoms in the molecule, `type` is
      type of the bead, and `weights` is an array of floats for
      weighting factors of atoms.
      <span class="remove_in_table">
        This parameter is assigned to #mol_type_to_abst_beads.
      </span>
    @endparblock
  */
  StaBeads(
    const ElPtr &el_mols,
    const Map<int,Vec<Json>> &schemes);
  virtual ~StaBeads() = default;
};

#endif