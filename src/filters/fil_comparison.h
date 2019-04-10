/*!
  @file src/filters/fil_comparison.h
  @brief This file has a definition of FilComparison class,
  which is a subclass of Filter class.
  @author Takayuki Kobayashi
  @date 2018/07/02
*/

#ifndef FIL_COMPARISON_H
#define FIL_COMPARISON_H

#include <filters/filter.h>

//! Alias for a function taking a ::Json object and returning a boolean.
using CompareFunc = std::function<bool(const Json &)>;

/*!
  @brief FilComparison applies a filter
  defined by comparison operators.

  An object of this class has a filter defined
  by #compare_expr_list, which is a list consisting of tuples
  where the first element is a string key, the second element is
  a comparison operator and the third element is a right hand value of
  an inequality (or equation). Currently supported operators are
  `<`, `>`, `<=`, `>=`, `==`, and `!=`.
  An element of array Element::data can pass this filter only if
  satisfying all the inequalities. The element can pass a inequality
  when its value for the string key satisfies the condition defined by
  the comparison operator and right hand value.

  About usage in Python,
  please see pybind::py_fil_comparison.
*/
class FilComparison : public Filter {
  /*!
    Criteria of this filter stored in a ::Vec (list) object.
    Elements of the list are three-elements tuples.
    The first element of each tuple is a key; and the key must be
    contained in an Element object where this object is appended to.
    Note that the reason not using ::Map is to allow
    duplicate keys.
  */
  Vec<std::tuple<Str,Str,Json>> compare_expr_list;
  /*!
    @brief Make a ::CompareFunc object from a comparison operator
    and a right side value.

    @param oper
      A string representing a comparison operator.
      One of `<`, `>`, `<=`, `>=`, `==`, and `!=`.

    @param rval
      A right side value. Since it is ::Json,
      it can be either an integer or a float.

    @return A function evaluating an inequality (or equation).
  */
  const CompareFunc make_compare_func(
    const Str &oper,
    const Json &rval);
  /*!
    @brief Convert tuples in #compare_expr_list to pairs of a string key
    and ::CompareFunc.

    @return A constant ::Vec<std::pair<#Str,#CompareFunc>> object,
    which describes criteria of this filter.

    Returned value of this method is used for evaluating inequalities
    consisting of the second and third elements of tuples contained
    in #compare_expr_list. Note that this conversion from tuples
    to pairs should not be conducted in constructor because of
    possibility of throwing (and raising) a runtime error.
  */
  const Vec<std::pair<Str,CompareFunc>> make_compare_func_list();
  /*!
    @brief Check if an element in data array can pass this filter.

    @param elem_in_data
      An element in data array.

    @param compare_func_list
      Comparison functions made by #make_compare_func_list.

    @return
      If `elem_in_data` can pass this filter.
  */
  const bool check_if_pass_data_elem(
    const Json &elem_in_data,
    const Vec<std::pair<Str,CompareFunc>> &compare_func_list);
 protected:
  //! This method overrides Updater::compute_impl.
  virtual void compute_impl(
    Json &data) override;
 public:
  /*!
    @brief Constructor of FilComparison class with one criterion.

    @param compare_expr_
      A three-elements tuple consisting of a string key,
      comparison operator and right side value of an inequality
      (or equation). Note that an Element object, where the constructed
      object is appended to, must has a property corresponding to
      the first element of this parameter (string key).
      <span class="remove_in_table">
        A single-element ::Vec object consisting of this parameter
        is assigned to #compare_expr_list.
      </span>
  */
  FilComparison(
    const std::tuple<Str,Str,Json> &compare_expr_);
  /*!
    @brief Constructor of FilComparison class with multiple criteria.

    @param compare_expr_list_
      List of three-elements tuples consisting of a string key,
      comparison operator and right side value of an inequality
      (or equation). Note that an Element object, where the constructed
      object is appended to, must has properties corresponding to
      the first elements of this parameter (string key).
      <span class="remove_in_table">
        This parameter is assigned to #compare_expr_list.
      </span>
  */
  FilComparison(
    const Vec<std::tuple<Str,Str,Json>> &compare_expr_list_);
  virtual ~FilComparison() = default;
};

#endif