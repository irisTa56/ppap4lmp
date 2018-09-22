/*!
  @file src/starters/sta_copy.h
  @brief This file has a definition of StaCopy class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/09/20
*/

#ifndef STA_COPY_H
#define STA_COPY_H

#include <starters/starter.h>

/*!
  @brief StaCopy copies Element::data of an existing Element object
  and sets it to a new Element object.
  @details An object of this class owns an existing Element object as
  #ext_generator and copies Element::data and Element::datakeys
  of the existing object, and then sets the copies to a new Element
  object.

  About usage in Python,
  please see src/pybind/starters/py_sta_copy.h.
*/
class StaCopy : public Starter {
 protected:
  /*!
    @copydoc Updater::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of StaCopy class.
    @param elem : Shared pointer to an Element object to be copied.
    This argument is assigned to #ext_generator.
  */
  StaCopy(
    const ElPtr &elem);
  virtual ~StaCopy() = default;
  /*!
    @copybrief Starter::compute
    @param data : Mutable reference to Element::data where computed
    properties are set to.
    @param datakeys : Mutable reference to Element::datakeys where keys
    of computed properties are set to.
    @param dataid : Constant integer copied from Element::dataid.
    @return None.
    @details Unlike other subclasses of Stater class, StaCopy overrides
    this method to skip sorting by \c id property.
  */
  virtual void compute(
    Json &data,
    DataKeys &datakeys,
    const int dataid) override;
};

#endif