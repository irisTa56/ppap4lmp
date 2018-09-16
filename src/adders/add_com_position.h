/*!
  @file src/adders/add_com_position.h
  @brief This file has a definition of the AddCoMPosition class, which
  is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/13
*/

#ifndef ADD_COM_POSITION_H
#define ADD_COM_POSITION_H

#include <adders/adder.h>

/*!
  @brief \e AddCoMPosition stands for Adder for Center of Mass added as
  Position, \c xu, \c yu and \c zu.
  @details This class inherits Adder class and overrides
  Adder::compute_impl. An Element instance, which an instance of this
  class is appended to, consists of (that is, is started from) an
  Element instance stored as the #ext_generator. About usage in Python,
  please see src/pybind/adders/add_com_position.h.
  <p>
  Name (key) of property to be added:
    - \c mass (float)
    - \c xu (float)
    - \c yu (float)
    - \c zu (float)
  </p>
  <p>
  Name (key) of property to be required:
    - <c>atom-ids</c> (array of integer)
  </p>
  <p>
  Name (key) of property in #ext_generator to be required:
    - \c id (integer)
    - \c mass (float)
    - \c xu (float)
    - \c yu (float)
    - \c zu (float)
  </p>
*/
class AddCoMPosition : public Adder {
  /*!
    @brief Compute the center of mass with weighed atoms.
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
    @brief Compute the center of mass.
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
    @brief Constructor of AddCoMPosition class.
    @param elem : Shared pointer to an Element instance, which is used
    for creating another Element instance where the constructed instance
    is appended to.
    @details The \c elem is assigned to the #ext_generator.
  */
  AddCoMPosition(
    const ElPtr &elem);
  virtual ~AddCoMPosition() = default;
};

#endif