/*!
  @file src/processors/pro_data.h
  @brief This file has a definition of ProData class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/06/22
*/

#ifndef PRO_DATA_H
#define PRO_DATA_H

#include <processors/processor.h>

/*!
  @brief ProData copies Element::data from Element objects.

  An object of this class makes a list of ::Json objects by copying all
  or some properties of Element objects stored in #generators.

  About usage in Python,
  please see pybind::py_pro_data.
*/
class ProData : public Processor {
  /*!
    List of string keys for properties to be copied. If this member is
    empty, all properties of Element objects are copied.
  */
  Vec<Str> selected_keys;
  /*!
    List in which ::Json objects consisting of copied properties
    are stored.
    Indices in this member corresponds to those in #generators.
  */
  Vec<Json> results;
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
    @brief Constructor of ProData class for one Element object.

    @param elem
      An Element object to be copied.
      <span class="remove_in_table">
        The parameter is put into #generators by #register_generator.
      </span>
  */
  ProData(
    const ElPtr &elem);
  /*!
    @brief Constructor of ProData class for a sequence
    of Element objects.

    @param elems
      List of Element objects to be copied.
      <span class="remove_in_table">
        Elements of the parameter is put into #generators
        by #register_generators.
      </span>
  */
  ProData(
    const Vec<ElPtr> &elems);
  virtual ~ProData() = default;
  /*!
    @brief Clear and resize #results.
    @return None.
  */
  virtual void prepare() override;
  /*!
    @brief Specify string keys for properties to be copied.

    @param *args
      An ordered list of string keys for properties to be copied.
      (Python's variable number arguments).
      <span class="remove_in_table">
        This parameter is converted to be stored as #selected_keys.
      </span>

    @return None.
  */
  void select(
    const py::args &args);
  /*!
    @brief Get list of ::Json objects consisting of all
    or some properties of Element objects stored in this object.

    @return #results.
  */
  const Vec<Json> &get_results();
};

#endif
