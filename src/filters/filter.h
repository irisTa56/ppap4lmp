/*!
  @file src/filters/filter.h
  @brief This file has a definition of the Filter class, which is a
  subclass of the Updater class.
  @author Takayuki Kobayashi
  @date 2018/06/30
*/

#ifndef FILTER_H
#define FILTER_H

#include <core/updater.h>

/*!
  @brief \e Filter removes items in array Element::data if the items
  fail user-defined criteria.
  @details This class inherits Updater class and overrides
  Updater::compute. This class is an abstract class and has a pure
  virtual function, Filter::compute_impl (defined in Updater class).
  Names of subclass of this class should be prefixed by \e Fil. Note
  that there are two types of Filter: one constructed with an Element
  object can be used for creating a new Element object like a Starter
  object, and the other can be used for modifying an existing Element
  object.
*/
class Filter : public Updater {
 public:
  /*!
    @brief Constructor of Filter class (inherited). Constructed object
    is used for modifying an existing Element object.
    @details Element::data of an Element object where an object
    constructed by this constructor is appended to contains only items
    passing user-defined criteria.
  */
  using Updater::Updater;
  virtual ~Filter() = default;
  /*!
    @brief Filter items in array Element::data given as a reference or
    copied from #ext_generator if the reference is empty.
    @param data : Mutable reference to Element::data to be filtered.
    @param datakeys : Mutable reference to Element::datakeys.
    @param dataid : Constant integer copied from Element::dataid.
    @return None.
    @details This method checks if \c dataid is in #dataid_blacklist.
    If it is not in the blacklist, this method then checks if \c data
    is empty or not. If the \c data is empty, copies of Element::data
    and Element::datakeys of upcasted #ext_generator are assigned to
    the \c data and \c datakeys. This method then passes \c data and
    \c datakeys to Filter::compute_impl. Note that actual computation
    for filtering is conducted in Filter::compute_impl orveridden in
    subclasses of this class.
  */
  virtual void compute(
    Json &data,
    DataKeys &datakeys,
    const int dataid) override;
};

#endif