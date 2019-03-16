/*!
  @file src/adders/add_bond_angle.h
  @brief This file has a definition of AddBondAngle class,
  which is a subclass of Adder class.
  @author Yang Juntao
  @date 2018/12/20
*/

#ifndef ADD_BOND_ANGLE_H
#define ADD_BOND_ANGLE_H

#include <adders/adder.h>

/*!
  @brief AddBondAngle adds `angle` property to bond-angles, each of
  them is defined by three consecutive atoms.

  An object of this class computes angles defined by three consecutive
  atoms, (in other words, angles between two adjacent bonds), and then
  adds these angles (in degree) to the bond-angles as their `angle`
  property. The object of this class takes an Element object for atoms
  as #ext_generator, and is appended to an Element object for bond-
  angles using its Element::append_updater.

  About usage in Python,
  please see pybind::py_add_bond_angle.
*/
class AddBondAngle : public Adder {

 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - `angle` : float
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - `atom1-id` : integer
        - `atom2-id` : integer
        - `atom3-id` : integer
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data) override;
 public:
  /*!
    @brief Constructor of AddBondAngle class.

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
  AddBondAngle(
    const ElPtr &elem);
  virtual ~AddBondAngle() = default;
};

#endif