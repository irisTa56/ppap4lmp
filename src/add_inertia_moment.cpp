/* ---------------------------------------------------------------------
AddInertiaMoment: stands for Adder for Inertia Moment (of molecules).

create: 2018/07/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_inertia_moment.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddInertiaMoment::AddInertiaMoment(ShPtr<GenElement> elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddInertiaMoment::compute_impl(Json &data, Set<Str> &datakeys)
{
  auto gen_atoms = ext_generator->get_element();

  if (!check_containment<Str>(
    gen_atoms->get_keys(), {"id", "mass", "xu", "yu", "zu"}))
  {
    runtime_error(
      "AddInertiaMoment needs 'id', 'mass' and '*u' (x/y/z) externally");
    return;
  }

  auto id2index_atom = get_map_to_index(gen_atoms->get_data(), "id");

  auto ms_atom = gen_atoms->get_1d_double("mass");
  auto rs_atom = gen_atoms->get_2d_double({"xu", "yu", "zu"});

  if (!check_containment<Str>(datakeys, {"xu", "yu", "zu"}))
  {
    runtime_error("AddInertiaMoment needs '*u' (x/y/z)");
    return;
  }

  for (auto &d : data)
  {
    RowArrayXd r_mol(3);
    r_mol << d["xu"], d["yu"], d["zu"];

    MatrixXd sum = MatrixXd::Zero(3, 3);

    for (int id : d["atom-ids"])
    {
      int index = id2index_atom[id];
      double mass = ms_atom(index);

      RowVectorXd dr = rs_atom.row(index) - r_mol;

      sum += mass * dr.transpose() * dr;
    }

    double tr = sum.trace();

    d["I_xx"] = tr - sum(0, 0);
    d["I_yy"] = tr - sum(1, 1);
    d["I_zz"] = tr - sum(2, 2);
    d["I_xy"] = -sum(0, 1);
    d["I_yz"] = -sum(1, 2);
    d["I_zx"] = -sum(2, 0);
  }

  datakeys.insert({"I_xx", "I_yy", "I_zz", "I_xy", "I_yz", "I_zx"});
}
