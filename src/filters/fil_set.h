/*!
  @file src/filters/fil_set.h
  @brief This file has a definition of the FilSet class, which is
  a subclass of the Filter class.
  @author Takayuki Kobayashi
  @date 2018/07/01
*/

#ifndef FIL_SET_H
#define FIL_SET_H

#include <filters/filter.h>

/*!
  @brief \e FilSet applies filtering using sets of acceptable values.
  @details This class inherits Filter class and overrides
  Filter::compute_impl. An object of this class has #value_sets, which
  is a dictionary consisting of pairs of a string key and a set of
  acceptable values. An item of Element::data can pass this filter only
  if every value for every key of #value_sets is included in the
  corresponding set (value of #value_sets).
*/
class FilSet : public Filter {
  /*!
    @brief ::Map (dictionary) representing an user-defined criterion of
    this filter.
    @details Keys of the dictionary are a part of Element::datakeys of
    an Element object where this object appended to.
  */
  Map<Str,Set<Json>> value_sets;
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  FilSet(
    const Map<Str,Set<Json>> &value_sets_);
  virtual ~FilSet() = default;
};

#endif