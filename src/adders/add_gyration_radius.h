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
  @details This class computes radius of gyration of an Element object
  (such as one containing data for molecules) from its inertia moment.

  About usage in Python, please see
  src/pybind/adders/py_add_gyration_radius.h.
*/
class AddGyrationRadius : public Adder, public EnShThis<AddGyrationRadius> {
  /*!
    @brief Whether gyration radius (not squared) is computed (default
    is \c false).
    @details Note that an average gyration radius should be computed by
    square rooting an averaged square of the gyration radius, not
    averaging the gyration radius itself.
  */
  bool add_sqrted = false;
 protected:
  /*!
    @copydoc Updater::compute_impl
    @details
    <table class="py_table2">
      <caption>
        AddGyrationRadius related properties
      </caption>
      <tr class="py_tr">
        <th class="py_th2">Key for property to be added</th>
        <th class="py_th2">Key for required property</th>
        <th class="py_th2">Key for externally required property</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">
          - \c Rg^2 : float
          - \c Rg^2(y+z) : float
          - \c Rg^2(z+x) : float
          - \c Rg^2(x+y) : float
          - \c Rg^2(x) : float
          - \c Rg^2(y) : float
          - \c Rg^2(z) : float

          [option]
          - \c Rg : float
          - \c Rg(y+z) : float
          - \c Rg(z+x) : float
          - \c Rg(x+y) : float
          - \c Rg(x) : float
          - \c Rg(y) : float
          - \c Rg(z) : float
        </td>
        <td class="py_td">
          - \c mass : float
          - \c I_xx : float
          - \c I_yy : float
          - \c I_zz : float
        </td>
        <td class="py_td">
          None.
        </td>
      </tr>
    </table>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  //! Constructor of AddGyrationRadius class (inherited).
  using Adder::Adder;
  virtual ~AddGyrationRadius() = default;
  /*!
    @brief Enable to compute gyration radius (by default, only square
    of gyration radius is computed).
    @param add_sqrted_ : A boolean, whether gyration radius is computed
    or not (default is \c true).
    @return Shared pointer to this object.
    @details Please be careful not to call this method in
    a multithreading context because it is thread-unsafe.
  */
  ShPtr<AddGyrationRadius> with_sqrted(
    bool add_sqrted_ = true);
};

#endif