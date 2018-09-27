/*!
  @file src/processors/pro_value_array.h
  @brief This file has a definition of ProValueArray class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/07/16
*/

#ifndef PRO_VALUE_ARRAY_H
#define PRO_VALUE_ARRAY_H

#include <processors/processor.h>

/*!
  @brief ProValueArray makes one or more arrays consisting of values
  for property in a sequence of Element objects.

  An object of this class makes one or more two-dimensional arrays
  consisting of values for property of Element objects stored
  in #generators. These arrays are useful for calculating statistics
  of property added by Adder's subclass.

  About usage in Python,
  please see pybind::py_pro_value_array.
*/
class ProValueArray : public Processor {
  /*!
    List of string keys for properties to be targeted.
  */
  Vec<Str> selected_keys;
  /*!
    Dictionary from keys for property to two-dimensional arrays of
    values for the property.
    The keys are same as elements of #selected_keys.
    Each column of the array corresponds to a sequence of the value
    for each element in array Element objects stored in #generators
    (for example, each atom in Element objects for atoms),
    and each row of the array corresponds to each Element object
    of #generators.
  */
  Map<Str,ArrayXXd> results;
  /*!
    List in which dictionaries from key for property to ::RowArrayXd
    of values for the property are stored.
    Indices in this list corresponds those in #generators.
  */
  Vec<Map<Str,RowArrayXd>> results_trajs;
 protected:
  /*!
    @copydoc Processor::run_impl

    I am sorry to say that the best documentation for this method
    is its source code...
  */
  virtual void run_impl(
    const int index) override;
 public:
  /*!
    @brief Constructor of ProValueArray class for one Element object.

    @param elem
      An Element object.
      <span class="remove_in_table">
        The parameter is put into #generators by #register_generator.
      </span>
  */
  ProValueArray(
    const ElPtr &elem);
  /*!
    @brief Constructor of ProValueArray class for a sequence
    of Element objects.

    @param elems
      List of Element objects.
      If each Element object is an array, all the array should have
      the same length.
      <span class="remove_in_table">
        Elements of this parameter is put into #generators
        by #register_generators.
      </span>
  */
  ProValueArray(
    const Vec<ElPtr> &elems);
  virtual ~ProValueArray() = default;
  /*!
    @brief Resize #results_trajs.
    @return None.
  */
  virtual void prepare() override;
  /*!
    @brief Make #results from #results_trajs.

    @return None.

    Each row of a value of #results corresponds to a value
    for the corresponding key in each element of #results_trajs.
  */
  virtual void finish() override;
  /*!
    @brief Specify string keys for properties. To use this object,
    at least one key must be specified. Note that new keys overwrite
    old keys.

    @param *args
      An ordered list of string keys for properties
      (Python's variable number arguments).
      Be sure that all Element objects stored in this object
      has the keys.
      <span class="remove_in_table">
        This parameter is converted to be stored as #selected_keys.
      </span>

    @return None.
  */
  void select(
    const py::args &args);
  /*!
    @brief Get dictionary from keys for property to
    two-dimensional arrays of values for the property.
    Each row of the array corresponds to each snapshot of a simulation,
    and each column of the array corresponds to each element
    in array Element objects (for example,
    each atom in Element objects for atoms).

    @return #results.
  */
  const Map<Str,ArrayXXd> &get_results();
};

#endif
