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

  An object of this class owns a mapping. Domain of the mapping
  consists of values for an existing property of an Element object
  where the object of this class is appended to. Codomain of
  the mapping consists of values for a new property. Note that
  the domain must cover all values for the existing property.

  About usage in Python,
  please see pybind::py_add_map.
*/
class AddMap : public Adder {
  /*!
    Whether overwriting an existing property whose name is
    the same as a new property to be added (default is `false`).
  */
  bool do_overwrite = false;
  /*!
    Key for an existing property (domain of the mapping).
  */
  Str key_ref;
  /*!
    Key for a new property to be added (codomain of the mapping)
  */
  Str key_new;
  /*!
    Mapping from values for an existing property specified by #key_ref
    to values for a new property specified by #key_new. Domain of
    the mapping consists of values for the existing property
    in Element::data of an Element object where this object is
    appended to. Codomain of the mapping consists of user-defined
    values for the new property to be added to the Element::data.
  */
  Map<Json,Json> mapping;
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - `[key_new]` : any type
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - `[key_ref]` : any type
        (but, in most cases, integer or strings)
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    JsonToVoidFunc check_required_keys,
    JsonToBoolFunc check_optional_keys) override;
 public:
  /*!
    @brief Constructor of AddMap class.

    @param key_ref_
    @parblock
      A string key for a reference property: an existing property
      to be used as domain of mapping.
      <span class="remove_in_table">
        This parameter is assigned to #key_ref.
      </span>

    @param key_new_
      A string key for a new property to be added.
      Values for the new property are determined by mapping.
      <span class="remove_in_table">
        This parameter is assigned to #key_new.
      </span>

    @param mapping_
      Dictionary defining a mapping from values for
      the reference property to values for the new property.
      Keys of the dictionary corresponds to domain of the mapping,
      and values of the dictionary corresponds to codomain
      of the mapping. Note that the keys must cover all values
      of the reference property in an Element object
      where the constructed object is appended to.
      <span class="remove_in_table">
        This parameter is assigned to #mapping.
      </span>
    @endparblock
  */
  AddMap(
    const Str &key_ref_,
    const Str &key_new_,
    const Map<Json,Json> &mapping_);
  virtual ~AddMap() = default;
  /*!
    @brief Allow overwriting an existing property by a new property
    with the same name.

    @param do_overwrite_
      A boolean, whether an existing property can be overwritten
      by a new property (default is `true`).
      <span class="remove_in_table">
        This parameter is assigned to #do_overwrite.
      </span>

    @return Shared pointer to this object.

    <span class="remove_in_table">
      Please be careful not to call this method
      in a multithreading context because it is thread-unsafe.
    </span>
  */
  ShPtr<AddMap> overwrite(
    bool do_overwrite_ = true);
};

#endif