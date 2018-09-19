/*!
  @file src/adders/add_gyration_radius.h
  @brief This file has a definition of AddGyrationRadius class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/15
*/

#ifndef ADD_GYRATION_RADIUS_H
#define ADD_GYRATION_RADIUS_H

#include <adders/adder.h>

/*!
  @brief AddGyrationRadius adds gyration radius of an Element object.
  @details This class inherits Adder class and
  ::EnShThis<#AddGyrationRadius>, and overrides Adder::compute_impl.

  This class computes radius of gyration of an Element object (such as
  one containing data for molecules) from its inertia moment.

  About usage in Python, please see
  src/pybind/py_adders/add_gyration_radius.h.

  Key of property to be added (default):
    - \c Rg (float)
    - \c Rg(y+z) (float)
    - \c Rg(z+x) (float)
    - \c Rg(x+y) (float)
    - \c Rg(x) (float)
    - \c Rg(y) (float)
    - \c Rg(z) (float)

  Key of property to be added (optional):
    - \c Rg^2 (float)
    - \c Rg^2(y+z) (float)
    - \c Rg^2(z+x) (float)
    - \c Rg^2(x+y) (float)
    - \c Rg^2(x) (float)
    - \c Rg^2(y) (float)
    - \c Rg^2(z) (float)

  Required key of property:
    - \c mass (float)
    - \c I_xx (float)
    - \c I_yy (float)
    - \c I_zz (float)
*/
class AddGyrationRadius : public Adder, public EnShThis<AddGyrationRadius> {
  /*!
    @brief Whether square of the gyration radius is computed (default
    is false).
    @details Note that an average gyration radius should be computed by
    square rooting an averaged square of the gyration radius, not
    averaging the gyration radius itself.
  */
  bool add_squared = false;
  /*!
    @brief Whether gyration radius (not squared) is computed (default
    is true).
    @details Note that an average gyration radius should be computed by
    square rooting an averaged square of the gyration radius, not
    averaging the gyration radius itself.
  */
  bool add_sqrted = true;
 protected:
  /*!
    @copydoc AddMap::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  //! Constructor of AddGyrationRadius class (inherited).
  using Adder::Adder;
  virtual ~AddGyrationRadius() = default;
  /*!
    @brief Switch #add_squared (to true by default).
    @param add_squared_ : A boolean to be assigned to #add_squared.
    @return Shared pointer to this object.
  */
  ShPtr<AddGyrationRadius> with_squared(
    bool add_squared_ = true);
  /*!
    @brief Switch #add_sqrted (to false by default).
    @param without_sqrted_ : A boolean whose negation is assigned to
    #add_sqrted.
    @return Shared pointer to this object.
  */
  ShPtr<AddGyrationRadius> without_sqrted(
    bool without_sqrted_ = true);
};

#endif