/*!
  @file src/adders/add_dihedral_angle.h
  @brief This file has a definition of AddDihedralAngle class,
  which is a subclass of Adder class.
  @author Yang Juntao
  @date 2018/12/24
*/

#ifndef ADD_DIHEDRAL_ANGLE_H
#define ADD_DIHEDRAL_ANGLE_H

#include <adders/adder.h>

/*!
  @brief AddDihedralAngle adds `dihedral-angle` property to dehedrals,
  each of them is defined by four consecutive atoms.

  An object of this class computes dihedral angles defined by four
  consecutive atoms, (angles between two planes defined the first three
  atoms and the last three atoms), and then adds these dihedral angles
  (in degree) to the dihedrals as their `dihedral-angle` property.
  The object of this class takes an Element object for atoms as
  #ext_generator, and is appended to an Element object for dihedrals
  using its Element::append_updater.

  About usage in Python,
  please see pybind::py_add_dihedral_angle.
*/
class AddDihedralAngle : public Adder {

 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - `dihedral-angle` : float
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - `atom1-id` : integer
        - `atom2-id` : integer
        - `atom3-id` : integer
        - `atom4-id` : integer
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data) override;
 public:
  /*!
    @brief Constructor of AddDihedralAngle class.

    @param elem
    @parblock
      An Element object for dihedrals.
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
  AddDihedralAngle(
    const ElPtr &elem);
  virtual ~AddDihedralAngle() = default;
};

#endif