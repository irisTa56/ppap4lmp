/*!
  @file src/starters/starter.h
  @brief This file has a definition of Starter class,
  which is a subclass of Updater class.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef STARTER_H
#define STARTER_H

#include <core/updater.h>

/*!
  @brief Starter sets some properties to an empty Element object.

  This class inherits Updater class and overrides Updater::compute.
  This class is an abstract class and has a pure virtual function,
  Starter::compute_impl.

  Name of subclass of this class should be prefixed by *Sta*.
  Unlike Adder, Starter accepts only empty Element::data.
*/
class Starter : public Updater {
  /*!
    Sort elements of a array ::Json object by its `id` property.

    @param data
      Mutable reference to a ::Json object.

    @return None.
  */
  void sort_by_id(
    Json &data);
 protected:
  /*!
    Whether to call #sort_by_id after setting data.
  */
  static const bool do_sorting_by_id = true;
  /*!
    @brief Compute or parse properties and set them to Element::data
    given as a mutable reference.

    @param elem
      Shared pointer to an Element object
      where computed properties are set to.

    @param data
      Mutable reference to Element::data
      where computed properties are set to.

    @return None.

    This method sorts elements of the `data` by `id` property,
    if the `data` is array and `id` property exists.
  */
  virtual void compute_body(
    const ElPtr &elem,
    Json &data) override;
 public:
  using Updater::Updater;
  virtual ~Starter() = default;
};

#endif