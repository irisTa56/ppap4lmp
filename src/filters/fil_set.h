/*!
  @file src/filters/fil_set.h
  @brief This file has a definition of FilSet class,
  which is a subclass of the Filter class.
  @author Takayuki Kobayashi
  @date 2018/07/01
*/

#ifndef FIL_SET_H
#define FIL_SET_H

#include <filters/filter.h>

/*!
  @brief FilSet applies a filter defined by sets of acceptable values.
  @details This class inherits Filter class and overrides
  Filter::compute_impl.

  An object of this class has a filter defined by #value_sets,
  which is a dictionary consisting of pairs of a string key
  and a set of acceptable values. An item of Element::data can pass
  this filter only if every value for every key of #value_sets is
  included in the corresponding set (a value of #value_sets).

  About usage in Python,
  please see src/pybind/filters/py_fil_set.h.
*/
class FilSet : public Filter {
  /*!
    @brief ::Map (dictionary) representing criteria of this filter.
    @details Note that keys of this dictionary must be
    a partial set of Element::datakeys of an Element object
    where this object appended to.
  */
  Map<Str,Set<Json>> value_sets;
 protected:
  /*!
    @brief Filter items from array Element::data given
    as a mutable reference.
    @param data : Mutable reference to Element::data to be filtered.
    @param datakeys : Mutable reference to Element::datakeys.
    @return None.
    @details I'm sorry to say that source code is the best
    documentation for this method...
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of FilSet class.
    @param value_sets_ : ::Map from a string key of property to
    acceptable values of that property.
    This argument is assigned to #value_sets.
    @details Note that keys in the \c value_sets_ must be included
    in Element::datakeys of an Element object
    where this object appended to.
  */
  FilSet(
    const Map<Str,Set<Json>> &value_sets_);
  virtual ~FilSet() = default;
};

#endif