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

/*!
  @brief \e CompareFunc is an alias for a function
  taking a ::Json object and returning a boolean.
*/
using CompareFunc = std::function<bool(const Json &)>;

/*!
  @brief FilComparison applies a filter
  defined by comparison operators.

  An object of this class has a filter defined by #comparisons,
  which is a list consisting of tuples where the first element is
  a string key, the second element is a comparison operator and
  the third element is a right side value of an inequality
  (or equation). Currently supported operators are
  \c <, \c >, \c <=, \c >=, \c ==, and \c !=.

  An element of array Element::data can pass this filter
  only if every value for every key in #comparisons satisfies
  an inequality consisting of the corresponding comparison operator
  and right side value (the second and third elements of #comparisons).
  Note that value(s) of the item is taken as left side value of
  the inequality.

  About usage in Python,
  please see pybind::py_fil_comparison.
*/
class FilComparison : public Filter {
  /*!
    Criteria of this filter stored in a ::Vec (list) object.
    Elements of the list are 3-elements tuples. The first element
    of each tuple is a key; and the key must be contained in
    Element::datakeys of an Element object where this object is
    appended to. Note that the reason not using ::Map is to allow
    duplicate keys.
  */
  Vec<std::tuple<Str,Str,Json>> comparisons;
  /*!
    Make a ::CompareFunc object from a comparison operator
    and a right side value.

    @param oper : A string representing a comparison operator.
    One of \c <, \c >, \c <=, \c >=, \c ==, and \c !=.

    @param rval : A right side value. Since it is ::Json,
    it can be either an integer or a float.

    @return ::CompareFunc, a function evaluating an inequality
    (or equation).
  */
  const CompareFunc make_lambda(
    const Str &oper,
    const Json &rval);
  /*!
    Convert tuples in #comparisons to pairs of a string key
    and ::CompareFunc.

    @param comps : #comparisons.

    @return Constant ::Vec<std::pair<#Str,#CompareFunc>>,
    which describes criteria of this filter.

    Returned value of this method is used for evaluating inequalities
    consisting of the second and third elements of tuples contained
    in #comparisons. Note that this method should not be called
    from constructor because of possibility of throwing
    (and raising) a runtime error.
  */
  const Vec<std::pair<Str,CompareFunc>> convert_to_funcs(
    const Vec<std::tuple<Str,Str,Json>> &comps);
 protected:
  //! This method overrides Updater::compute_impl.
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of FilComparison class with one criterion.

    @param comparison_
      A 3-elements tuple consisting of a string key,
      comparison operator and right side value of an inequality
      (or equation). Note that an Element object, where the constructed
      object is appended to, must has a property corresponding to
      the first element of this parameter (string key).
      <span class="remove_in_table">
        A single-element ::Vec object consisting of this parameter
        is assigned to #comparisons.
      </span>
  */
  FilComparison(
    const std::tuple<Str,Str,Json> &comparison_);
  /*!
    @brief Constructor of FilComparison class with multiple criteria.

    @param comparisons_
      List of 3-elements tuples consisting of a string key,
      comparison operator and right side value of an inequality
      (or equation). Note that an Element object, where the constructed
      object is appended to, must has properties corresponding to
      the first elements of this parameter (string key).
      <span class="remove_in_table">
        This parameter is assigned to #comparisons.
      </span>
  */
  FilComparison(
    const Vec<std::tuple<Str,Str,Json>> &comparisons_);
  virtual ~FilComparison() = default;
};

#endif