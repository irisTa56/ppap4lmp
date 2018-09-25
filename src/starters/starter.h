/*!
  @file src/starters/starter.h
  @brief This file has a definition of Starter class,
  which is a subclass of Updater class.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef STARTER_H
#define STARTER_H

#include <core/updater.h>

/*!
  @brief Starter sets some properties (keys and values) to
  an empty Element object.

  This class inherits Updater class and overrides Updater::compute.
  This class is an abstract class and has a pure virtual function,
  Starter::compute_impl.

  Name of subclass of this class should be prefixed by \e Sta.
  Unlike Adder, Starter accepts only empty Element::data.
*/
class Starter : public Updater {
/*!
  Sort elements of a array ::Json object by its \c id property.

  @param data
    Mutable reference to a ::Json object.

  @return None.
*/
  void sort_by_id(
    Json &data);
 public:
  using Updater::Updater;
  virtual ~Starter() = default;
  /*!
    @brief Compute or parse properties and set them to Element::data
    given as a mutable reference.

    @param data
      Mutable reference to Element::data where computed
      properties are set to.

    @param datakeys
      Mutable reference to Element::datakeys where keys
      for computed properties are set to.

    @param dataid
      A constant integer copied from Element::dataid.

    @return None.

    This method checks if \c dataid is in #dataid_blacklist. If it is
    not in the blacklist, this method passes \c data and \c datakeys
    to Starter::compute_impl. Note that actual computation and setting
    of properties is conducted by Starter::compute_impl orveridden
    in subclasses of this class. In addition, this method sorts
    elements of the \c data by \c id property, if the \c data
    is an array and \c id property is set.
  */
  virtual void compute(
    Json &data,
    DataKeys &datakeys,
    const int dataid) override;
};

#endif