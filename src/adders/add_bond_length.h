/*!
  @file src/adders/add_bond_length.h
  @brief This file has a definition of AddBondLength class,
  which is a subclass of Adder class.
  @author Yang Juntao & Kawai Kento
  @date 2018/12/06
*/

#ifndef ADD_BOND_LENGTH_H
#define ADD_BOND_LENGTH_H

#include <adders/adder.h>

/*!
  @brief AddBondLength adds `length` property to bonds, each of them
  connects two atoms.

  An object of this class computes distances between pairs of atoms
  connected with bonds, and then adds these distances to the bonds as
  their `length` property. The object of this class takes an Element
  object for atoms as #ext_generator, and is appended to an Element
  object for bonds using its Element::append_updater.

  About usage in Python,
  please see pybind::py_add_bond_length.
*/
class AddBondLength : public Adder {

 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - `length` : float
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - `atom1-id` : integer
        - `atom2-id` : integer
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddBondLength class.

    @param elem
    @parblock
      An Element object for atoms.
      <span class="remove_in_table">
        This parameter is assigned to #ext_generator.
      </span>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `id` : integer
          - `xu` : float
          - `yu` : float
          - `zu` : float
        </dd>
      </dl>
    @endparblock
  */
  AddBondLength(
    const ElPtr &elem);
  virtual ~AddBondLength() = default;
};

#endif