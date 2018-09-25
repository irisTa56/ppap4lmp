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
  @brief AddGyrationRadius adds gyration radius to an Element object.

  This class computes radius of gyration of an Element object
  (such as one containing data for molecules) from its inertia moment.

  About usage in Python,
  please see pybind::py_add_gyration_radius.
*/
class AddGyrationRadius : public Adder, public EnShThis<AddGyrationRadius> {
  /*!
    Whether gyration radius (not squared) is computed (default is
    \c false). Note that an average gyration radius should be computed
    by square rooting an averaged square of the gyration radius, not
    averaging the gyration radius itself.
  */
  bool add_sqrted = false;
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - \c Rg^2 : float
        - \c Rg^2(y+z) : float
        - \c Rg^2(z+x) : float
        - \c Rg^2(x+y) : float
        - \c Rg^2(x) : float
        - \c Rg^2(y) : float
        - \c Rg^2(z) : float
        - \c Rg : float (optional)
        - \c Rg(y+z) : float (optional)
        - \c Rg(z+x) : float (optional)
        - \c Rg(x+y) : float (optional)
        - \c Rg(x) : float (optional)
        - \c Rg(y) : float (optional)
        - \c Rg(z) : float (optional)
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - \c mass : float
        - \c I_xx : float
        - \c I_yy : float
        - \c I_zz : float
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  using Adder::Adder;
  virtual ~AddGyrationRadius() = default;
  /*!
    @brief Enable to compute gyration radius (by default, only square
    of gyration radius is computed).

    @param add_sqrted_
      A boolean, whether gyration radius is computed or not
      (default is \c true).

    @return Shared pointer to this object.

    <span class="remove_in_table">
      Please be careful not to call this method
      in a multithreading context because it is thread-unsafe.
    </span>
  */
  ShPtr<AddGyrationRadius> with_sqrted(
    bool add_sqrted_ = true);
};

#endif