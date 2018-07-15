/* ---------------------------------------------------------------------
AddInertiaMoment: stands for Adder for Inertia Moment (of molecules).

create: 2018/07/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_inertia_moment.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddInertiaMoment::AddInertiaMoment(
  std::shared_ptr<Generator> gen)
{
  if (gen->get_datatype() == "Atoms")
  {
    reference_generator = gen;
  }
  else
  {
    runtime_error(
      "AddInertiaMoment cannot use " + gen->get_dataname());
  }

  callable_datatypes = {"Molecules"};
}

/* ------------------------------------------------------------------ */

void AddInertiaMoment::compute_impl(json &data)
{
  auto &atoms = reference_generator->get_data();

  if (!check_key(atoms, {"id", "mass", "xu", "yu", "zu"}))
  {
    runtime_error(
      "AddInertiaMoment needs IDs, masses and unwrapped "
      "positions of Atoms");
  }

  auto atom_id2index = get_map_to_index(atoms, "id");

  auto atom_ms = reference_generator->get_1d_double("mass");
  auto atom_rs = reference_generator->get_2d_double({"xu", "yu", "zu"});

  if (!check_key(data, {"xu", "yu", "zu"}))
  {
    runtime_error("AddInertiaMoment needs the unwrapped positions");
  }

  for (auto &d : data)
  {
    RowArrayXd r_mol(3);
    r_mol << d["xu"], d["yu"], d["zu"];

    MatrixXd sum = MatrixXd::Zero(3, 3);

    for (int id : d["atom-ids"])
    {
      int index = atom_id2index[id];
      auto mass = atom_ms(index);

      auto dr = (atom_rs.row(index) - r_mol).matrix();

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
