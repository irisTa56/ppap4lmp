/*!
  @file src/adders/add_map.h
  @brief This file has a definition of the AddMap class, which is a
  subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/06/26
*/

#ifndef ADD_MAP_H
#define ADD_MAP_H

#include <adders/adder.h>

/*!
  @brief \e AddMap stands for Adder for Mapping from existing property
  to new property.
  @details This class inherits Adder class and ::EnShThis<#AddMap>,
  and overrides Adder::compute_impl. This class adds a new property by
  mapping from an existing property. Domain of the mapping must cover
  all values of the existing property. About usage in Python, please
  see src/pybind/adders_py/add_map.h.
  <p>
    Name (key) of property to be added:
      - \c <c>[key_new]</c> (any type)
  </p>
  <p>
    Name (key) of property to be required:
      - <c>[key_ref]</c> (any type; but, in most cases, integer or
      strings)
  </p>
*/
class AddMap : public Adder, public EnShThis<AddMap> {
  /*!
    @brief Whether overwriting an existing property whose name is the
    same as new property to be added (default is false).
  */
  bool do_overwrite = false;
  /*!
    @brief Name (key) of an existing property (domain of the mapping).
    @details Name of this member stands for key referenced from the
    mapping.
  */
  Str key_ref;
  /*!
    @brief Name (key) of a new property to be added (codomain of the
    mapping).
  */
  Str key_new;
  /*!
    @brief Mapping (or function) to be used for determining values of
    new property.
  */
  Map<Json,Json> mapping;
 protected:
  /*!
    @brief Compute properties and add them to Element::data given as a
    reference.
    @param data : Mutable reference to Element::data where computed
    properties are added to.
    @param datakeys : Mutable reference to Element::datakeys where keys
    of computed properties are added to.
    @return None.
    @details I'm sorry to say that source code is the best
    documentation for this method...
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddMap class.
    @param key_ref_ : A string key for an existing property to be used
    as domain of mapping.
    @param key_new_ : A string key for a new property to be added.
    @param mapping_ : ::Map from ::Json to ::Json. Constructed object
    conducts mapping process defined by this argument.
    @details The \c key_ref_, \c key_new_ and \c mapping_ are assigned
    to the #key_ref, #key_new and #mapping, respectively. Note that
    domain of the \c mapping_ must cover all values of property
    specified by \c key_ref_; the property is stored in an Element
    object where the constructed object is appended to.
  */
  AddMap(
    const Str &key_ref_,
    const Str &key_new_,
    const Map<Json,Json> &mapping_);
  virtual ~AddMap() = default;
  /*!
    @brief Switch #do_overwrite (to true by default).
    @param do_overwrite_ : A boolean to be assigned to #do_overwrite.
    @return Shared pointer to this object.
  */
  ShPtr<AddMap> overwrite(
    bool do_overwrite_ = true);
};

#endif