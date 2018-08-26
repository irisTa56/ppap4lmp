/* ---------------------------------------------------------------------
AddCoMPositions: stands for Adder for Center of Mass added as Positions.

create: 2018/07/13 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_com_positions.h"
#include "../utils/map_to_index.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

AddCoMPositions::AddCoMPositions(
  const ShPtr<Element> &elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddCoMPositions::compute_with_weights(
  Json &data,
  const ShPtr<Element> &gen_atoms)
{
  auto id2index_atom = ut::map_to_index(gen_atoms->get_data(), "id");

  ArrayXd ms_atom;
  gen_atoms->array1d(ms_atom, "mass");

  ArrayXXd rs_atom;
  gen_atoms->array2d(rs_atom, {"xu", "yu", "zu"});

  for (auto &d : data)
  {
    double m_tmp = 0.0;
    RowArrayXd r_tmp = RowArrayXd::Zero(3);

    auto &atom_ids = d["atom-ids"];
    auto &atom_weights = d["atom-weights"];

    auto n_atoms = atom_ids.size();

    for (int i = 0; i != n_atoms; ++i)
    {
      auto id = atom_ids[i].get<int>();
      auto weight = atom_weights[i].get<double>();

      auto index = id2index_atom[id];
      auto mass = ms_atom(index) * weight;

      m_tmp += mass;
      r_tmp += mass * rs_atom.row(index);
    }

    r_tmp /= m_tmp;

    d["mass"] = m_tmp;

    d["xu"] = r_tmp(0);
    d["yu"] = r_tmp(1);
    d["zu"] = r_tmp(2);
  }
}

/* ------------------------------------------------------------------ */

void AddCoMPositions::compute_without_weights(
  Json &data,
  const ShPtr<Element> &gen_atoms)
{
  auto id2index_atom = ut::map_to_index(gen_atoms->get_data(), "id");

  ArrayXd ms_atom;
  gen_atoms->array1d(ms_atom, "mass");

  ArrayXXd rs_atom;
  gen_atoms->array2d(rs_atom, {"xu", "yu", "zu"});

  for (auto &d : data)
  {
    double m_tmp = 0.0;
    RowArrayXd r_tmp = RowArrayXd::Zero(3);

    for (const int id : d["atom-ids"])
    {
      auto index = id2index_atom[id];
      auto mass = ms_atom(index);

      m_tmp += mass;
      r_tmp += mass * rs_atom.row(index);
    }

    r_tmp /= m_tmp;

    d["mass"] = m_tmp;

    d["xu"] = r_tmp(0);
    d["yu"] = r_tmp(1);
    d["zu"] = r_tmp(2);
  }
}

/* ------------------------------------------------------------------ */

void AddCoMPositions::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  datakeys.required("atom-ids");

  auto gen_atoms = ext_generator->get_element();

  gen_atoms->required({"id", "mass", "xu", "yu", "zu"});

  if (datakeys.optional("atom-weights"))
  {
    compute_with_weights(data, gen_atoms);
  }
  else
  {
    compute_without_weights(data, gen_atoms);
  }

  datakeys.add({"mass", "xu", "yu", "zu"});
}
