/* ---------------------------------------------------------------------
GenElement: stands for Generator containing data 'element'.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "gen_element.h"
#include "utils.h"

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
GenElement::GenElement()
{
  instance_count++;
  dataname = "_" + std::to_string(instance_count);
}

/* ------------------------------------------------------------------ */

const json &GenElement::get_data()
{
  return data;
}

/* ------------------------------------------------------------------ */

const json &GenElement::get_data_py()
{
  hello();
  return get_data();
}

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
void GenElement::append_updater(
  std::shared_ptr<Updater> upd)
{
  if (!upd->is_callable(datatype))
  {
    runtime_error(dataname + " cannot call Updater");
  }

  auto gen = upd->get_generator();

  if (gen)
  {
    merge_update_chain(gen->get_update_chain());
  }

  update_chain.push_back(UpdatePair(shared_from_this(), upd));
}

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
std::shared_ptr<Generator> GenElement::set_initial_updater(
  std::shared_ptr<Updater> upd)
{
  upd->initialize_datatype(datatype);
  dataname = datatype + dataname;

  update_chain.insert(
    update_chain.begin(), UpdatePair(shared_from_this(), upd));

  auto gen = upd->get_generator();

  if (gen)
  {
    auto &forward_chain = gen->get_update_chain();

    update_chain.insert(
      update_chain.begin(), forward_chain.begin(), forward_chain.end());
  }

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

ArrayXi GenElement::get_1d_int(const std::string &key)
{
  ArrayXi v(data.is_array() ? data.size() : 1);

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i != length; ++i)
    {
      v(i) = data[i][key];
    }
  }
  else
  {
    v(0) = data[key];
    message(dataname + " might be non-array or null (not int_vector)");
  }

  return v;
}

/* ------------------------------------------------------------------ */

const ArrayXi GenElement::get_1d_int_py(const std::string &key)
{
  hello();
  return get_1d_int(key);
}

/* ------------------------------------------------------------------ */

ArrayXd GenElement::get_1d_double(const std::string &key)
{
  ArrayXd v(data.is_array() ? data.size() : 1);

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i != length; ++i)
    {
      v(i) = data[i][key];
    }
  }
  else
  {
    v(0) = data[key];
    message(dataname + " might be non-array or null (not double_vector)");
  }

  return v;
}

/* ------------------------------------------------------------------ */

const ArrayXd GenElement::get_1d_double_py(const std::string &key)
{
  hello();
  return get_1d_double(key);
}

/* ------------------------------------------------------------------ */

ArrayXXi GenElement::get_2d_int(const std::vector<std::string> &keys)
{
  int n_keys = keys.size();

  ArrayXXi a(data.is_array() ? data.size() : 1, n_keys);

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i != length; ++i)
    {
      auto &d = data[i];

      for (int j = 0; j != n_keys; ++j)
      {
        a(i, j) = d[keys[j]];
      }
    }
  }
  else
  {
    for (int j = 0; j != n_keys; ++j)
    {
      a(0, j) = data[keys[j]];
    }
    message(dataname + " might be non-array or null (not int_array)");
  }

  return a;
}

/* ------------------------------------------------------------------ */

const ArrayXXi GenElement::get_2d_int_py(
  const std::vector<std::string> &keys)
{
  hello();
  return get_2d_int(keys);
}

/* ------------------------------------------------------------------ */

ArrayXXd GenElement::get_2d_double(const std::vector<std::string> &keys)
{
  int n_keys = keys.size();

  ArrayXXd a(data.is_array() ? data.size() : 1, n_keys);

  if (data.is_array())
  {
    int length = data.size();

    for (int i = 0; i != length; ++i)
    {
      auto &d = data[i];

      for (int j = 0; j != n_keys; ++j)
      {
        a(i, j) = d[keys[j]];
      }
    }
  }
  else
  {
    for (int j = 0; j != n_keys; ++j)
    {
      a(0, j) = data[keys[j]];
    }
    message(dataname + " might be non-array or null (not double_array)");
  }

  return a;
}

/* ------------------------------------------------------------------ */

const ArrayXXd GenElement::get_2d_double_py(
  const std::vector<std::string> &keys)
{
  hello();
  return get_2d_double(keys);
}
