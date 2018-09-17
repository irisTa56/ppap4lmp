/*!
  @file src/adders/add_molecular_orientation.h
  @brief This file has a definition of the AddMolecularOrientation
  class, which is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/16
*/

#ifndef ADD_MOLECULAR_ORIENTATION_H
#define ADD_MOLECULAR_ORIENTATION_H

#include <adders/adder.h>

/*!
  @brief \e AddMolecularOrientation stands for Adder for Molecular
  Orientation.
  @details This class inherits Adder class and overrides
  Adder::compute_impl. This class computes orientation (a.k.a. order
  parameter) of molecules from their inertia moments. To compute the
  orientation, a direction of eigenvector corresponding the minimum
  eigenvalue of the inertia moment (that is, long axis of the molecule)
  is used for each molecule. About usage in Python, please see
  src/pybind/py_adders/add_molecular_orientation.h.
  <p>
    Name (key) of property to be added:
      - \c I_values (array of float; eigenvalues of inertia moment)
      - \c I_vectors (array of array of float; eigenvectors of inertia
      moment)
      - \c S_x (float)
      - \c S_y (float)
      - \c S_z (float)
  </p>
  <p>
    Name (key) of property to be required:
      - \c I_xx (float)
      - \c I_yy (float)
      - \c I_zz (float)
      - \c I_xy (float)
      - \c I_xz (float)
      - \c I_yz (float)
  </p>
*/
class AddMolecularOrientation : public Adder {
 protected:
  /*!
    @copydoc AddMap::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddMolecularOrientation class (default).
  */
  using Adder::Adder;
  virtual ~AddMolecularOrientation() = default;
};

#endif