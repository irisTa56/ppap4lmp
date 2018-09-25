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
  @details An object of this class makes a list of ::Json objects
  by copying all or some properties of Element objects
  stored in #generators.

  About usage in Python,
  please see src/pybind/processors/py_pro_data.h.
*/
class ProData : public Processor {
  /*!
    @brief List of string keys for properties to be copied.
    @details If this member is empty, all properties of Element objects
    are copied.
  */
  Vec<Str> selected_keys;
  /*!
    @brief List in which ::Json objects consisting of copied properties
    are stored.
    @details Index in this member corresponds that in #generators.
  */
  Vec<Json> results;
 protected:
  //! @copydoc Processor::run_impl
  virtual void run_impl(
    const int index) override;
 public:
  /*!
    @brief Constructor of ProData class for one Element object.
    @param elem : An Element object to be copied.
    @details The \c elems is put into #generators
    by #register_generator.
  */
  ProData(
    const ElPtr &elem);
  /*!
    @brief Constructor of ProData class for a sequence
    of Element objects.
    @param elems : ::Vec of Element objects to be copied.
    @details Elements of the \c elems are put into #generators
    by #register_generators.
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
    @param args : An ordered list of string keys (\c *args in Python).
    This parameter is converted to be stored as #selected_keys.
    @return None.
  */
  void select(
    const py::args &args);
  /*!
    @brief Get copied data.
    @return #results.
  */
  const Vec<Json> &get_results();
};

#endif
