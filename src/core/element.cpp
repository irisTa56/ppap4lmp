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

int Element::instance_count = 0;

/* ------------------------------------------------------------------ */

Element::Element()
{
  instance_count++;
  dataid = instance_count;
  omp_init_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

void Element::increment_remain()
{
  #pragma omp atomic
  n_remain++;
}

/* ------------------------------------------------------------------ */

void Element::decrement_remain()
{
  omp_set_lock(&omp_lock);

  n_remain--;

  if (n_remain == 0)
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

    for (const auto &item : update_chain)
    {
      if (item.first == shared_this)
      {
        item.second->remove_from_blacklist(dataid);
      }
    }

    ut::log("Data-" + std::to_string(dataid) + " has been deleted");
  }
  else if (n_remain < 0)
  {
    ut::runtime_error(
      "Data-" + std::to_string(dataid) + " was used illegally");
  }

  omp_unset_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

void Element::update_data(
  const ShPtr<Updater> &upd)
{
  omp_set_lock(&omp_lock);

  upd->compute(shared_from_this(), data, dataid);

  omp_unset_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

Vec<std::pair<Str,int>> Element::get_key_advances(
  const Json &key_)
{
  const Vec<Str> keys = key_.is_array() ? key_ : Json::array({key_});
  const auto &front = data.is_array() ? data.front() : data;

  Vec<std::pair<Str,int>> advances;
  int from_begin_ex = 0;

  for (auto it = front.begin(); it != front.end(); ++it)
  {
    if (std::find(keys.begin(), keys.end(), it.key()) != keys.end())
    {
      int from_begin = std::distance(front.begin(), it);
      advances.push_back(
        std::make_pair(it.key(), from_begin - from_begin_ex));
      from_begin_ex = from_begin;
    }
  }

  return advances;
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

void Element::set_checking_classname(
  const Str &classname)
{
  checking_classname = classname;
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

Json Element::get_json(const Json &key_)
{
  const auto advances = get_key_advances(key_);

  Json tmp;

  if (data.is_array())
  {
    tmp = Json::array();
    tmp.get_ref<Json::array_t&>().reserve(data.size());

    for (const auto &d : data)
    {
      tmp.push_back({});
      auto &back = tmp.back();
      auto it = d.begin();

      for (const auto &pair : advances)
      {
        std::advance(it, pair.second);
        back[pair.first] = *it; //*(begin+item.second);
      }
    }
  }
  else
  {
    auto it = data.begin();

    for (const auto &pair : advances)
    {
      std::advance(it, pair.second);
      tmp[pair.first] = *it; //*(begin+item.second);
    }
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

Set<Str> Element::get_keys()
{
  return Set<Str>(datakeys.begin(), datakeys.end());
}

/* ------------------------------------------------------------------ */

template <typename T>
void Element::array1d(
  T &array,
  const Str &key)
{
  array.resize(data.is_array() ? data.size() : 1);

  if (data.is_array())
  {
    const auto key_position = get_key_advances(key).front().second;

    int index = 0;

    for (const auto &d : data)
    {
      array(index++) = *std::next(d.begin(), key_position);
    }
  }
  else
  {
    array(0) = data[key];
  }
}

/* ------------------------------------------------------------------ */

template <typename T>
void Element::array2d(
  T &array,
  const Vec<Str> &keys)
{
  array.resize(data.is_array() ? data.size() : 1, keys.size());

  if (data.is_array())
  {
    Vec<std::pair<int,int>> advances;
    for (const auto &pair : get_key_advances(keys))
    {
      advances.push_back(std::make_pair(
        pair.second,
        std::distance(
          keys.begin(), std::find(keys.begin(), keys.end(), pair.first))
      ));
    }

    int irow = 0;

    for (const auto &d : data)
    {
      auto it = d.begin();

      for (const auto &pair : advances)
      {
        std::advance(it, pair.first);
        array(irow, pair.second) = *it;
      }

      irow++;
    }
  }
  else
  {
    int icol = 0;

    for (const auto &key : keys)
    {
      array(0, icol++) = data[key];
    }
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

void Element::required_keys(
  const Json &key_)
{
  Vec<Str> missings;

  for (const Str &key : key_.is_array() ? key_ : Json::array({key_}))
  {
    if (std::find(datakeys.begin(), datakeys.end(), key) == datakeys.end())
    {
      missings.push_back(key);
    }
  }

  if (!missings.empty())
  {
    std::sort(missings.begin(), missings.end());

    Str msg = "Missing key(s) '" + ut::join(missings, "', '") + "'";

    if (!checking_classname.empty())
    {
      msg += " in " + checking_classname;
    }

    ut::runtime_error(msg);
  }
}

/* ------------------------------------------------------------------ */

bool Element::optional_keys(
  const Json &key_)
{
  for (const Str &key : key_.is_array() ? key_ : Json::array({key_}))
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

  required_keys(key);

  ArrayXi array;
  array1d(array, key);

  return array;
}

/* ------------------------------------------------------------------ */

ArrayXd Element::get_1d_float_py(
  const Str &key)
{
  init_for_python();

  required_keys(key);

  ArrayXd array;
  array1d(array, key);

  return array;
}

/* ------------------------------------------------------------------ */

ArrayXXi Element::get_2d_int_py(
  const py::args &args)
{
  init_for_python();

  Vec<Str> keys;
  ut::pyargs_to_vec(args, keys);

  required_keys(keys);

  ArrayXXi array;
  array2d(array, keys);

  return array;
}

/* ------------------------------------------------------------------ */

ArrayXXd Element::get_2d_float_py(
  const py::args &args)
{
  init_for_python();

  Vec<Str> keys;
  ut::pyargs_to_vec(args, keys);

  required_keys(keys);

  ArrayXXd array;
  array2d(array, keys);

  return array;
}

/* ------------------------------------------------------------------ */

void Element::init_for_python()
{
  try
  {
    hello();
  }
  catch (std::runtime_error &e)
  {
    ut::log("ERROR - " + Str(e.what()));
  }
}

/* ------------------------------------------------------------------ */