/*!
  @file src/starters/sta_custom.h
  @brief This file has a definition of StaCustom class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/08/16
*/

#ifndef STA_CUSTOM_H
#define STA_CUSTOM_H

#include <starters/starter.h>

/*!
  @brief StaCustom sets an user-defined ::Json object to
  a new Element object as its Element::data.

  An object of this class takes an user-defined ::Json object
  to be set as Element::data.

  About usage in Python,
  please see pybind::py_sta_custom.
*/
class StaCustom : public Starter {
  /*!
    A ::Json (complex of dictionary and list) object
    to be set as Element::data.
  */
  Json json;
 protected:
  //! This method overrides Updater::compute_impl.
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of StaCustom class.

    @param json_
      A ::Json (complex of dictionary and list) object
      to be set as Element::data.
      <span class="remove_in_table">
        This parameter is assigned to #json.
      </span>
  */
  StaCustom(
    const Json &json_);
  virtual ~StaCustom() = default;
};

#endif