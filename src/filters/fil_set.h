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

  An object of this class has a filter defined by #acceptable_value_sets,
  which is a dictionary consisting of pairs of a string key
  and a set of values which can pass the filter.

  An element of array Element::data can pass this filter
  only if its value for every key in #acceptable_value_sets is
  included in the corresponding set (a value of #acceptable_value_sets).

  About usage in Python,
  please see pybind::py_fil_set.
*/
class FilSet : public Filter {
  /*!
    Criteria of this filter stored in a ::Map (dictionary) object.
    Note that keys of this dictionary must be contained
    in an Element object where this object appended to.
  */
  Map<Str,Set<Json>> acceptable_value_sets;
  /*!
    @brief Check if an element in data array can pass this filter.

    @param elem_in_data
      An element in data array.

    @return
      If `elem_in_data` can pass this filter.
  */
  const bool check_if_pass_data_elem(
    const Json &elem_in_data);
 protected:
  //! This method overrides Updater::compute_impl.
  virtual void compute_impl(
    Json &data) override;
 public:
  /*!
    @brief Constructor of FilSet class.

    @param acceptable_value_sets_
      Dictionary from a string key for property to acceptable values
      of that property. Note that an Element object,
      where the constructed object is appended to, must has properties
      corresponding to keys in this parameter.
      <span class="remove_in_table">
        This parameter is assigned to #acceptable_value_sets.
      </span>
  */
  FilSet(
    const Map<Str,Set<Json>> &acceptable_value_sets_);
  virtual ~FilSet() = default;
};

#endif