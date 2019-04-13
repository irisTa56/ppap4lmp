/*!
  @file src/filters/filter.h
  @brief This file has a definition of Filter class,
  which is a subclass of Updater class.
  @author Takayuki Kobayashi
  @date 2018/06/30
*/

#ifndef FILTER_H
#define FILTER_H

#include <core/updater.h>

/*!
  @brief Filter removes elements from array Element::data
  if the elements fail user-defined criteria.

  This class inherits Updater class and overrides Updater::compute_boby.
  This class is an abstract class and has a pure virtual function,
  Filter::compute_impl.

  Name of subclass of this class should be prefixed by *Fil*.
  Note that Filter do nothing for non-array Element::data.
*/
class Filter : public Updater {
 protected:
  /*!
    @brief Filter elements from array Element::data given
    as a mutable reference.

    @param elem
      Shared pointer to an Element object to be filtered.

    @param data
      Mutable reference to Element::data to be filtered.

    @return None.

    Each element in the array `data` remains unchanged.
  */
  virtual void compute_body(
    const ElPtr &elem,
    Json &data) override;
 public:
  using Updater::Updater;
  virtual ~Filter() = default;
};

#endif