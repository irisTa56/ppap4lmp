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
  @details An object of this class owns mapping(s) representing
  coarse-graining scheme(s). Each mapping describes
  how atoms in a molecule are allocated to beads.
  Different mapping schemes are acceptable
  for different molecular types. For each bead, its type
  and weighting factors of atoms belonging to the bead can be set.

  About usage in Python,
  please see src/pybind/starters/py_sta_beads.h.
*/
class StaBeads : public Starter {
  /*!
    @brief Coarse-grain mapping schemes for each molecular type.
    @details Description of coarse-graining is stored as a map
    (dictionary) from molecular type to vector (list) of ::Json objects.
    Each ::Json object corresponds to each bead in a molecule
    of that type, and contains three items: \c indices-in-mol is
    an array of zero-based index of atoms in the molecule,
    \c type is type of the bead, and \c weights is an array of floats
    for weighting factors of atoms. The last two items are optional.
    Length of the two arrays, \c indices-in-mol and \c weights,
    should be the same with the number of atoms belonging to the bead.
  */
  Map<int,Vec<Json>> mol_type_to_abst_beads;
  /*!
    @brief Check if #mol_type_to_abst_beads correctly describes
    coarse-grain mapping schemes.
    @return A pair of booleans: the first is whether \c type exists
    or not, the second is whether \c weights exists or not. Note that
    if at least one of ::Json objects in #mol_type_to_abst_beads has
    \c type (or \c weights) property, all the other objects must have
    that property.
  */
  std::pair<bool,bool> check_mol_type_to_abst_beads();
 protected:
  /*!
    @copydoc Updater::compute_impl
    @details
    <table class="py_table2">
      <caption>
        StaBeads related properties
      </caption>
      <tr class="py_tr">
        <th class="py_th2">Key for property to be set</th>
        <th class="py_th2">Key for required property</th>
        <th class="py_th2">Key for externally required property</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">
          - \c id : integer
          - \c mol : integer
          - \c atom-ids : array of integers

          [optional]
          - \c type : integer
          - \c atom-weights : array of floats
        </td>
        <td class="py_td">
          None.
        </td>
        <td class="py_td">
          - \c atom-ids : array of integers
        </td>
      </tr>
    </table>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of StaBeads class for one molecular type.
    @param el_mols : Shared pointer to a molecular Element object
    consisting of a bead Element object where the constructed object is
    appended to.
    This argument is assigned to #ext_generator.
    @param scheme : ::Vec of ::Json objects. For more details about
    contents of each ::Json object, please see the explanation of
    #mol_type_to_abst_beads.
    This argument is stored in #mol_type_to_abst_beads as
    a coarse-graining scheme for molecular type 1.
  */
  StaBeads(
    const ElPtr &el_mols,
    const Vec<Json> &scheme);
  /*!
    @brief Constructor of StaBeads class for multiple molecular types.
    @param el_mols : Shared pointer to a molecular Element object
    consisting of a bead Element object where the constructed object is
    appended to.
    This argument is assigned to #ext_generator.
    @param schemes : ::Map from molecular type to ::Vec of ::Json
    objects. For more details about contents of each ::Json object,
    please see the explanation of #mol_type_to_abst_beads.
    This argument is assigned to #mol_type_to_abst_beads.
  */
  StaBeads(
    const ElPtr &el_mols,
    const Map<int,Vec<Json>> &schemes);
  virtual ~StaBeads() = default;
};

#endif