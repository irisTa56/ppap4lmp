/*!
  @file src/adders/add_map.h
  @brief This file has a definition of AddMap class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/06/26
*/

#ifndef ADD_MAP_H
#define ADD_MAP_H

#include <adders/adder.h>

/*!
  @brief AddMap adds a new property by mapping from
  an existing property.
  @details An object of this class owns a mapping.
  Domain of the mapping consists of values of an existing property of
  an Element object where the object of this class is appended to.
  Codomain of the mapping consists of values of a new property.
  Note that the domain must cover all values of the existing property.

  About usage in Python,
  please see src/pybind/adders/py_add_map.h.

  Key of property to be added:
    - <c>[key_new]</c> (any type)

  Key of required property:
    - <c>[key_ref]</c> (any type; but, in most cases, integer or
    strings)
*/
class AddMap : public Adder, public EnShThis<AddMap> {
  /*!
    @brief Whether overwriting an existing property whose name is the
    same as new property to be added (default is false).
  */
  bool do_overwrite = false;
  /*!
    @brief Key of an existing property (domain of the mapping).
    @details \c key_ref stands for key referenced from the mapping.
  */
  Str key_ref;
  /*!
    @brief Key of a new property to be added (codomain of the mapping).
  */
  Str key_new;
  /*!
    @brief Mapping used for determining values of new property.
    @details This member defines a mapping from values of an existing
    property specified by #key_ref to values of a new property
    specified by #key_new. Domain of the mapping consists of values of
    the existing property in Element::data of an Element object where
    this object is appended to. Codomain of the mapping consists of
    user-defined values for the new property to be added to
    the Element::data.
  */
  Map<Json,Json> mapping;
 protected:
  /*!
    @copydoc Updater::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddMap class.
    @param key_ref_ : A string key for an existing property to be used
    as domain of mapping.
    This argument is assigned to #key_ref.
    @param key_new_ : A string key for a new property to be added.
    This argument is assigned to #key_new.
    @param mapping_ : ::Map from ::Json to ::Json defining a mapping
    process conducted by the constructed object.
    This argument is assigned to #mapping.
    @details Note that domain of the \c mapping_ must cover all values
    of property specified by \c key_ref_: the property belonging to
    an Element object where the constructed object is appended to.
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
    @details Please be careful not to call this method in
    a multithreading context because it is thread-unsafe.
  */
  ShPtr<AddMap> overwrite(
    bool do_overwrite_ = true);
};

#endif