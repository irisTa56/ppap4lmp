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
  @brief \e CompareFunc is an alias for a function taking a ::Json
  and returning a boolean.
*/
using CompareFunc = std::function<bool(const Json &)>;

/*!
  @brief FilComparison applies a filter defined by comparison operators.
  @details An object of this class has a filter defined by #comparisons,
  which is a list consisting of tuples where the first element is
  a string key, the second element is a comparison operator and
  the third element is a right side value of an inequality
  (or equation). An item of Element::data can pass this filter
  only if every value for every key for #comparisons satisfies
  an inequality consisting of the corresponding comparison operator
  and right side value (the second and third elements of #comparisons).
  Note that value(s) of the item is taken as left side value of
  the inequality.

  About usage in Python,
  please see src/pybind/filters/py_fil_comparison.h.
*/
class FilComparison : public Filter {
  /*!
    @brief ::Vec (list) describing criteria of this filter.
    @details Elements of the list are 3-elements tuples.
    Note that the first element of each tuple is a key;
    and the key must be contained in Element::datakeys of
    an Element object where this object appended to.
    Note that the reason not using ::Map is to allow duplicate keys.
  */
  Vec<std::tuple<Str,Str,Json>> comparisons;
  /*!
    @brief Make a ::CompareFunc object from a comparison operator
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
    @brief Convert tuples in #comparisons to pairs of a string key
    and ::CompareFunc.
    @param comps : #comparisons.
    @return Constant ::Vec<std::pair<#Str,#CompareFunc>>,
    which describes criteria of this filter.
    @details Returned value of this method is used for evaluating
    inequalities consisting of the second and third elements of tuples
    contained in #comparisons. Note that this method should not be
    called from constructor because of possibility of throwing
    (and raising) a runtime error.
  */
  const Vec<std::pair<Str,CompareFunc>> convert_to_funcs(
    const Vec<std::tuple<Str,Str,Json>> &comps);
 protected:
  /*!
    @copydoc Updater::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of FilComparison class.
    @param comparison_ : A 3-elements tuple consisting of a string key,
    comparison operator and right side value of an inequality
    (or equation).
    This argument is appended to #comparisons.
    @details Note that the first element of \c comparison_ (string key)
    must be included in Element::datakeys of an Element object
    where this object appended to.
  */
  FilComparison(
    const std::tuple<Str,Str,Json> &comparison_);
  /*!
    @brief Constructor of FilComparison class.
    @param comparisons_ : ::Vec of 3-elements tuples consisting of
    a string key, comparison operator
    and right side value of an inequality (or equation).
    This argument is assigned to #comparisons.
    @details Note that the first element of each tuple
    in \c comparisons_ must be included in Element::datakeys
    of an Element object where this object appended to.
  */
  FilComparison(
    const Vec<std::tuple<Str,Str,Json>> &comparisons_);
  virtual ~FilComparison() = default;
};

#endif