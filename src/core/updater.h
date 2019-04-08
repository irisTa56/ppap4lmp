/*!
  @file src/core/updater.h
  @brief This file has a definition of Updater class,
  which is one of the cores of this program.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef UPDATER_H
#define UPDATER_H

#include <omp.h>

#include <core/generators.h>

/*!
  @brief Updater is an abstract class to update data held by
  an Element object.

  This class is a superclass of the Starter, Adder and Filter
  class.

  An object of this class is append to an Element object by
  Element::append_updater and stored as ::UpdatePair (where the first
  item is the Element object and the second item is the object of
  this class).
*/
class Updater : public std::enable_shared_from_this<Updater> {
  /*!
    Blacklist of Element::elementid updated by this Updater object.
    If this Updater object is called from an Element object
    for the first time, this object stores Element::elementid
    in #skippable_elementids and updates Element::data.
    From the second time on, this object can skip
    the updating computation.
  */
  Set<int> skippable_elementids;
  /*!
    A variable used for OpenMP. In this program,
    #skippable_elementids is modified in a multithreading context.
    To prevent #skippable_elementids from being modified from
    multiple threads at the same time, this member must be locked
    in #check_update_requirest_for and #remove_from_skippable_elementids.
  */
  omp_lock_t omp_lock;
 protected:
  /*!
    Shared pointer to a Generator object used in updating process.
    To compute some properties for an Element object where
    this object is appended to, an external Generator object (can be
    Element/GenDict/GenList) might be required. For example, to compute
    the center of mass of molecules for a molecular Element object,
    an atomic Element object containing positions of the atoms is
    required.
  */
  ShPtr<Generator> ext_generator;
  /*!
    Wrapper function for Element::check_required_keys of
    an Element object where this instance is appended to.
  */
  std::function<void(const Json &)> check_required_keys;
  /*!
    Wrapper function for Element::check_optional_keys of
    an Element object where this instance is appended to.
  */
  std::function<bool(const Json &)> check_optional_keys;
  /*!
    @brief Implementation of computation for updating Element::data.

    @param data
      Mutable reference to Element::data
      where computed properties are added to.

    @return None.
  */
  virtual void compute_impl(Json &data) = 0;
  //! Make #check_required_keys
  void make_check_required_keys(
    const ElPtr &elem);
  //! Make #check_optional_keys
  void make_check_optional_keys(
    const ElPtr &elem);
  /*!
    Look for Element::elementid in #skippable_elementids.

    @param elementid
      An Element::elementid to be checked.

    @return A boolean. If `elementid` is found in #skippable_elementids,
    this method returns false, that is, rejects the Element object
    of the `elementid`.
  */
  bool check_update_requirest_for(
    const int elementid);
 public:
  /*!
    @brief Constructor of Updater class.

    This constructor is thread-unsafe because it accesses
    its members thread-globally. Ensure this constructor is
    not called in a multithreading context. Please be careful
    that constructors of subclasses of this class are
    also thread-unsafe.
  */
  Updater();
  virtual ~Updater() = default;
  /*!
    @brief Managing computation to update Element::data.

    @param elem
      Shared pointer to an Element object
      where computed properties are added to.

    @param elementid
      A constant integer copied from Element::elementid.

    @param data
      Mutable reference to Element::data
      where computed properties are added to.

    @return None.
  */
  virtual void compute(
    const ElPtr &elem, const int elementid, Json &data) = 0;
  /*!
    @brief Remove Element::elementid from #skippable_elementids.

    @param elementid
      An Element::elementid to be removed.

    @return None.

    Removing `elementid` from #skippable_elementids is necessary
    so that this object can update the Element object of the `elementid`
    again after its Element::data being cleared.
  */
  void remove_from_skippable_elementids(
    const int elementid);
  /*!
    @brief Get #ext_generator of this object.

    @return Constance reference to ::ShPtr<#Generator>.

    This method is mainly used in Element::update_chain.
  */
  const ShPtr<Generator> &get_ext_generator();
};

#endif