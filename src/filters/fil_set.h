/*!
  @file src/filters/fil_set.h
  @brief This file has a definition of FilSet class,
  which is a subclass of Filter class.
  @author Takayuki Kobayashi
  @date 2018/07/01
*/

#ifndef FIL_SET_H
#define FIL_SET_H

#include <filters/filter.h>

/*!
  @brief FilSet applies a filter defined by sets of acceptable values.
  @details An object of this class has a filter defined by #value_sets,
  which is a dictionary consisting of pairs of a string key
  and a set of acceptable values. An element of Element::data can pass
  this filter only if every value for every key for #value_sets is
  included in the corresponding set (a value of #value_sets).

  About usage in Python,
  please see src/pybind/filters/py_fil_set.h.
*/
class FilSet : public Filter {
  /*!
    @brief ::Map (dictionary) describing criteria of this filter.
    @details Note that keys of this dictionary must be
    a partial set of Element::datakeys of an Element object
    where this object appended to.
  */
  Map<Str,Set<Json>> value_sets;
 protected:
  /*!
    @copydoc Updater::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of FilSet class.
    @param value_sets_ : ::Map from a string key for property to
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