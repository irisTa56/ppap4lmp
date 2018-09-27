/*!
  @file src/adders/add_molecular_orientation.h
  @brief This file has a definition of AddMolecularOrientation class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/16
*/

#ifndef ADD_MOLECULAR_ORIENTATION_H
#define ADD_MOLECULAR_ORIENTATION_H

#include <adders/adder.h>

/*!
  @brief AddMolecularOrientation adds molecular orientation (order
  parameter) to an Element object.

  This class computes orientation (a.k.a. order parameter) of
  an Element object (such as one containing data for molecules) from
  its inertia moment. To compute the orientation, a direction of
  eigenvector corresponding the minimum eigenvalue of
  the inertia moment (that is, long axis of the molecule) is used for
  each molecule.

  About usage in Python,
  please see pybind::py_add_molecular_orientation.
*/
class AddMolecularOrientation : public Adder {
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - \c I_values : array of floats
        (eigenvalues of inertia moment)
        - \c I_vectors : array of arrays of floats
        (eigenvectors of inertia moment)
        - \c S_x : float
        - \c S_y : float
        - \c S_z : float
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - \c I_xx : float
        - \c I_yy : float
        - \c I_zz : float
        - \c I_xy : float
        - \c I_xz : float
        - \c I_yz : float
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  using Adder::Adder;
  virtual ~AddMolecularOrientation() = default;
};

#endif