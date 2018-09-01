/* ---------------------------------------------------------------------
AddInertiaMoment: stands for Adder for Inertia Moment (of molecules).

create: 2018/07/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_inertia_moment.h"
#include "../utils.h"

/* ------------------------------------------------------------------ */

AddInertiaMoment::AddInertiaMoment(
  ShPtr<GenElement> elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddInertiaMoment::compute_with_weights(
  Json &data,
  ShPtr<GenElement> gen_atoms)
{
  auto id2index_atom = get_map_to_index(gen_atoms->get_data(), "id");

  auto ms_atom = gen_atoms->get_1d_double("mass");
  auto rs_atom = gen_atoms->get_2d_double({"xu", "yu", "zu"});

  for (auto &d : data)
  {
    RowArrayXd r_mol(3);
    r_mol << d["xu"], d["yu"], d["zu"];

    MatrixXd sum = MatrixXd::Zero(3, 3);

    auto &atom_ids = d["atom-ids"];
    auto &atom_weights = d["atom-weights"];

    auto n_atoms = atom_ids.size();

    for (int i = 0; i != n_atoms; ++i)
    {
      auto id = atom_ids[i].get<int>();
      auto weight = atom_weights[i].get<double>();

      auto index = id2index_atom[id];
      auto mass = ms_atom(index) * weight;

      RowVectorXd dr = rs_atom.row(index) - r_mol;

      sum += mass * dr.transpose() * dr;
    }

    auto tr = sum.trace();

    d["I_xx"] = tr - sum(0, 0);
    d["I_yy"] = tr - sum(1, 1);
    d["I_zz"] = tr - sum(2, 2);
    d["I_xy"] = -sum(0, 1);
    d["I_yz"] = -sum(1, 2);
    d["I_zx"] = -sum(2, 0);
  }
}

/* ------------------------------------------------------------------ */

void AddInertiaMoment::compute_without_weights(
  Json &data,
  ShPtr<GenElement> gen_atoms)
{
  auto id2index_atom = get_map_to_index(gen_atoms->get_data(), "id");

  auto ms_atom = gen_atoms->get_1d_double("mass");
  auto rs_atom = gen_atoms->get_2d_double({"xu", "yu", "zu"});

  for (auto &d : data)
  {
    RowArrayXd r_mol(3);
    r_mol << d["xu"], d["yu"], d["zu"];

    MatrixXd sum = MatrixXd::Zero(3, 3);

    for (int id : d["atom-ids"])
    {
      auto index = id2index_atom[id];
      auto mass = ms_atom(index);

      RowVectorXd dr = rs_atom.row(index) - r_mol;

      sum += mass * dr.transpose() * dr;
    }

    auto tr = sum.trace();

    d["I_xx"] = tr - sum(0, 0);
    d["I_yy"] = tr - sum(1, 1);
    d["I_zz"] = tr - sum(2, 2);
    d["I_xy"] = -sum(0, 1);
    d["I_yz"] = -sum(1, 2);
    d["I_zx"] = -sum(2, 0);
  }
}

/* ------------------------------------------------------------------ */

void AddInertiaMoment::compute_impl(
  Json &data,
  Set<Str> &datakeys)
{
  auto gen_atoms = ext_generator->get_element();

  check_keys(gen_atoms, {"id", "mass", "xu", "yu", "zu"});
  check_keys(datakeys, {"atom-ids", "xu", "yu", "zu"});

  if (check_containment<Str>(datakeys, "atom-weights"))
  {
    compute_with_weights(data, gen_atoms);
  }
  else
  {
    compute_without_weights(data, gen_atoms);
  }

  datakeys.insert({"I_xx", "I_yy", "I_zz", "I_xy", "I_yz", "I_zx"});
}
