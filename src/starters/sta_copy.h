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

  An object of this class owns an existing Element object as
  #ext_generator and copies Element::data of the existing object,
  and then sets the copies to a new Element object.

  About usage in Python,
  please see pybind::py_sta_copy.
*/
class StaCopy : public Starter {
 protected:
  //! @copydoc Starter::do_sorting_by_id
  static const bool do_sorting_by_id = false;
  //! This method overrides Updater::compute_impl.
  virtual void compute_impl(
    Json &data,
    JsonToVoidFunc check_required_keys,
    JsonToBoolFunc check_optional_keys) override;
 public:
  /*!
    @brief Constructor of StaCopy class.

    @param elem
      An Element object to be copied.
      <span class="remove_in_table">
        This parameter is assigned to #ext_generator.
      </span>
  */
  StaCopy(
    const ElPtr &elem);
  virtual ~StaCopy() = default;
};

#endif