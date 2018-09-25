/*!
  @file src/adders/adder.h
  @brief This file has a definition of Adder class,
  which is a subclass of Updater class.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef ADDER_H
#define ADDER_H

#include <core/updater.h>

/*!
  @brief Adder adds new properties (keys and values) to
  a non-empty Element object.

  This class inherits Updater class and overrides Updater::compute.
  This class is an abstract class and has a pure virtual function,
  Adder::compute_impl.

  Name of subclass of this class should be prefixed by \e Add.
  Unlike Starter, Adder accepts only non-empty Element::data.
*/
class Adder : public Updater {
 public:
  using Updater::Updater;
  virtual ~Adder() = default;
  /*!
    @brief Compute properties and add them to Element::data given
    as a mutable reference.

    @param data
      Mutable reference to Element::data where computed
      properties are added to.

    @param datakeys
      Mutable reference to Element::datakeys where keys
      for computed properties are added to.

    @param dataid
      Constant integer copied from Element::dataid.

    @return None.

    This method checks if \c dataid is in #dataid_blacklist. If it is
    not in the blacklist, this method passes \c data and \c datakeys
    to Adder::compute_impl. Note that actual computation and addition
    of properties is conducted by Adder::compute_impl orveridden
    in subclasses of this class. In addition, this method ensures that
    a new property whose name is \e id is not added; \c id property
    must be set at initialization (done by Starter) only.
  */
  virtual void compute(
    Json &data,
    DataKeys &datakeys,
    const int dataid) override;
};

#endif