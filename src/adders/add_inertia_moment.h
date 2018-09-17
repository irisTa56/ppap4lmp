/*!
  @file src/adders/add_inertia_moment.h
  @brief This file has a definition of the AddInertiaMoment class,
  which is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/15
*/

#ifndef ADD_INERTIA_MOMENT_H
#define ADD_INERTIA_MOMENT_H

#include <adders/adder.h>

/*!
  @brief \e AddInertiaMoment stands for Adder for Inertia Moment.
  @details This class inherits Adder class and overrides
  Adder::compute_impl. This class computes elements of 3x3 matrix of
  inertia moment (a.k.a. inertia matrix, inertia tensor) of molecules
  (or something else, such as beads). About usage in Python, please see
  src/pybind/py_adders/add_inertia_moment.h.
  <p>
    Name (key) of property to be added:
      - \c I_xx (float)
      - \c I_yy (float)
      - \c I_zz (float)
      - \c I_xy (float)
      - \c I_xz (float)
      - \c I_yz (float)
  </p>
  <p>
    Name (key) of property to be required:
      - <c>atom-ids</c> (array of integer)
      - \c xu (float)
      - \c yu (float)
      - \c zu (float)
  </p>
  <p>
    Name (key) of property in #ext_generator to be required:
      - \c id (int)
      - \c mass (float)
      - \c xu (float)
      - \c yu (float)
      - \c zu (float)
  </p>
*/
class AddInertiaMoment : public Adder {
  /*!
    @brief Compute the inertia moment with weighed atoms.
    @param data : Mutable reference to Element::data where computed
    properties are added to.
    @param el_atoms : Shared pointer of up-casted #ext_generator.
    @return None.
    @details Note that the weight is different from mass of the atom.
    It is an artificial value defined with some reason.
  */
  void compute_with_weights(
    Json &data,
    const ElPtr &el_atoms);
  /*!
    @brief Compute the inertia moment.
    @param data : Mutable reference to Element::data where computed
    properties are added to.
    @param el_atoms : Shared pointer of up-casted #ext_generator.
    @return None.
  */
  void compute_without_weights(
    Json &data,
    const ElPtr &el_atoms);
 protected:
  /*!
    @copydoc AddMap::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddInertiaMoment class.
    @param elem : Shared pointer to an Element object, which is used
    for creating another Element object where the constructed object
    is appended to.
    @details The \c elem is assigned to the #ext_generator.
  */
  AddInertiaMoment(
    const ElPtr &elem);
  virtual ~AddInertiaMoment() = default;
};

#endif