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
  @brief Adder adds new properties to a non-empty Element object.

  This class inherits Updater class and overrides Updater::compute_boby.
  This class is an abstract class and has a pure virtual function,
  Adder::compute_impl.

  Name of subclass of this class should be prefixed by *Add*.
  Unlike Starter, Adder accepts only non-empty Element::data.
*/
class Adder : public Updater {
 protected:
  /*!
    @brief Compute properties and add them to Element::data given
    as a mutable reference.

    @param elem
      Shared pointer to an Element object
      where computed properties are added to.

    @param data
      Mutable reference to Element::data
      where computed properties are added to.

    @return None.

    This method ensures that a new property whose name is *id*
    is not added; `id` property must be set at initialization
    (done by Starter) only.
  */
  virtual void compute_body(
    const ElPtr &elem,
    Json &data) override;
 public:
  using Updater::Updater;
  virtual ~Adder() = default;
};

#endif