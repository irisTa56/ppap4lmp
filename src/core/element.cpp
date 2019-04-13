/*!
  @file src/core/element.cpp
  @brief This file has an implementation of Element class,
  which is one of the cores of this program.
  @author Takayuki Kobayashi
  @date 2018/07/01
*/

#include "element.h"
#include "updater.h"
#include "../utils/join.h"
#include "../utils/message.h"
#include "../utils/pyargs_to_vec.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

int Element::n_element_instances = 0;

/* ------------------------------------------------------------------ */

Element::Element()
{
  n_element_instances++;
  elementid = n_element_instances;
  omp_init_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

void Element::increment_bookings()
{
  #pragma omp atomic
  n_bookings++;
}

/* ------------------------------------------------------------------ */

void Element::decrement_bookings()
{
  omp_set_lock(&omp_lock);

  n_bookings--;

  if (n_bookings == 0)
  {
    if (data.is_array())
    {
      data.get_ref<Json::array_t&>().clear();
      data.get_ref<Json::array_t&>().shrink_to_fit();
      data = nullptr;
    }
    else
    {
      data.clear();
      data = nullptr;
    }

    update_keys();

    auto shared_this = shared_from_this();

    for (const auto &pair : update_chain)
    {
      if (pair.first == shared_this)
      {
        pair.second->remove_from_skippable_elementids(elementid);
      }
    }

    ut::log("Data-" + std::to_string(elementid) + " has been deleted");
  }
  else if (n_bookings < 0)
  {
    ut::runtime_error(
      "Data-" + std::to_string(elementid) + " was used illegally");
  }

  omp_unset_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

void Element::update_data(
  const ShPtr<Updater> &upd)
{
  omp_set_lock(&omp_lock);

  upd->compute(shared_from_this(), elementid, data);

  omp_unset_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

Vec<std::pair<Str,int>> Element::get_distances_between_keys(
  const Json &key_)
{
  const Vec<Str> keys = key_.is_array() ? key_ : Json::array({key_});

  Vec<std::pair<Str,int>> distances;
  int distance_from_begin_ex = 0;

  for (auto it = datakeys.begin(); it != datakeys.end(); ++it)
  {
    if (std::find(keys.begin(), keys.end(), *it) != keys.end())
    {
      int distance_from_begin = std::distance(datakeys.begin(), it);
      distances.push_back(std::make_pair(
        *it, distance_from_begin - distance_from_begin_ex));
      distance_from_begin_ex = distance_from_begin;
    }
  }

  return distances;
}

/* ------------------------------------------------------------------ */

ElPtr Element::get_element(
  const Json &name)
{
  if (name != nullptr)
  {
    ut::runtime_error("Rejection of non-null Json");
  }

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

ShPtr<Generator> Element::get_generator(
  const Json &name)
{
  if (name != nullptr)
  {
    ut::runtime_error("Rejection of non-null Json");
  }

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

void Element::accessed_by_instance_of(
  const Str &classname)
{
  accessing_classname = classname;
}

/* ------------------------------------------------------------------ */

ElPtr Element::append_updater(
  const ShPtr<Updater> &upd)
{
  auto gen = upd->get_ext_generator();

  if (gen)
  {
    merge_update_chain(gen->get_update_chain());
  }

  update_chain.push_back(UpdatePair(shared_from_this(), upd));

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

const Json &Element::get_data()
{
  return data;
}

/* ------------------------------------------------------------------ */

Set<Str> Element::get_keys()
{
  return Set<Str>(datakeys.begin(), datakeys.end());
}

/* ------------------------------------------------------------------ */

Json Element::make_reduced_data(const Json &key_)
{
  const auto pairs_key_and_distance = get_distances_between_keys(key_);

  auto reduced_data = Json::array();

  if (data.is_array())
  {
    reduced_data.get_ref<Json::array_t&>().reserve(data.size());
  }

  for (const auto &d : data.is_array() ? data : Json::array({data}))
  {
    reduced_data.push_back({});
    auto &back = reduced_data.back();
    auto it_item = d.begin();

    for (const auto &pair : pairs_key_and_distance)
    {
      std::advance(it_item, pair.second);
      back[pair.first] = *it_item;
    }
  }

  return data.is_array() ? reduced_data : reduced_data.front();
}

/* ------------------------------------------------------------------ */

template <typename T>
void Element::make_1darray_from_data(
  T &array,
  const Str &key)
{
  array.resize(data.is_array() ? data.size() : 1);

  const auto key_position = std::distance(
    datakeys.begin(), std::find(datakeys.begin(), datakeys.end(), key));

  int index = 0;

  for (const auto &d : data.is_array() ? data : Json::array({data}))
  {
    array(index++) = *std::next(d.begin(), key_position);
  }
}

/* ------------------------------------------------------------------ */

template <typename T>
void Element::make_2darray_from_data(
  T &array,
  const Vec<Str> &keys)
{
  array.resize(data.is_array() ? data.size() : 1, keys.size());

  Vec<std::pair<int,int>> pairs_distance_and_icol;
  for (const auto &pair : get_distances_between_keys(keys))
  {
    pairs_distance_and_icol.push_back(std::make_pair(
      pair.second,
      std::distance(
        keys.begin(), std::find(keys.begin(), keys.end(), pair.first))
    ));
  }

  int irow = 0;

  for (const auto &d : data.is_array() ? data : Json::array({data}))
  {
    auto it_item = d.begin();

    for (const auto &pair : pairs_distance_and_icol)
    {
      std::advance(it_item, pair.first);
      array(irow, pair.second) = *it_item;
    }

    irow++;
  }
}

/* ------------------------------------------------------------------ */

void Element::update_keys()
{
  datakeys.clear();

  for (const auto &el : (data.is_array() ? data.front() : data).items())
  {
    datakeys.push_back(el.key());
  }
}

/* ------------------------------------------------------------------ */

void Element::check_required_keys(
  const Json &key_)
{
  const Vec<Str> keys = key_.is_array() ? key_ : Json::array({key_});
  Vec<Str> missing_keys;

  for (const auto &key : keys)
  {
    if (std::find(datakeys.begin(), datakeys.end(), key) == datakeys.end())
    {
      missing_keys.push_back(key);
    }
  }

  if (!missing_keys.empty())
  {
    std::sort(missing_keys.begin(), missing_keys.end());

    Str msg = "Missing key(s) '" + ut::join(missing_keys, "', '") + "'";

    if (!accessing_classname.empty())
    {
      msg += " in " + accessing_classname;
    }

    ut::runtime_error(msg);
  }
}

/* ------------------------------------------------------------------ */

bool Element::check_optional_keys(
  const Json &key_)
{
  const Vec<Str> keys = key_.is_array() ? key_ : Json::array({key_});

  for (const auto &key : keys)
  {
    if (std::find(datakeys.begin(), datakeys.end(), key) == datakeys.end())
    {
      return false;
    }
  }

  return true;
}

/* functions for Python --------------------------------------------- */

const Json &Element::get_data_py()
{
  init_for_python();

  return data;
}

/* ------------------------------------------------------------------ */

Set<Str> Element::get_keys_py()
{
  init_for_python();

  return get_keys();
}

/* ------------------------------------------------------------------ */

ArrayXi Element::get_1d_int_py(
  const Str &key)
{
  init_for_python();

  check_required_keys(key);

  ArrayXi array;
  make_1darray_from_data(array, key);

  return array;
}

/* ------------------------------------------------------------------ */

ArrayXd Element::get_1d_float_py(
  const Str &key)
{
  init_for_python();

  check_required_keys(key);

  ArrayXd array;
  make_1darray_from_data(array, key);

  return array;
}

/* ------------------------------------------------------------------ */

ArrayXXi Element::get_2d_int_py(
  const py::args &args)
{
  init_for_python();

  Vec<Str> keys;
  ut::pyargs_to_vec(args, keys);

  check_required_keys(keys);

  ArrayXXi array;
  make_2darray_from_data(array, keys);

  return array;
}

/* ------------------------------------------------------------------ */

ArrayXXd Element::get_2d_float_py(
  const py::args &args)
{
  init_for_python();

  Vec<Str> keys;
  ut::pyargs_to_vec(args, keys);

  check_required_keys(keys);

  ArrayXXd array;
  make_2darray_from_data(array, keys);

  return array;
}

/* ------------------------------------------------------------------ */

void Element::init_for_python()
{
  try
  {
    generate_data();
  }
  catch (std::runtime_error &e)
  {
    // NOTE: Error message can also be seen as Python's exception.
    ut::log("ERROR - " + Str(e.what()));
  }
}
