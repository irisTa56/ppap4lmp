/* ---------------------------------------------------------------------
AddGyrationRadius: stands for Adder for Gyration Radius (of molecules).

create: 2018/07/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_gyration_radius.h"

/* ------------------------------------------------------------------ */

void AddGyrationRadius::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  datakeys.required({"mass", "I_xx", "I_yy", "I_zz"});

  for (auto &d : data)
  {
    auto reciprocal_mass = 1.0 / d["mass"].get<double>();

    auto ixx_per_mass = d["I_xx"].get<double>() * reciprocal_mass;
    auto iyy_per_mass = d["I_yy"].get<double>() * reciprocal_mass;
    auto izz_per_mass = d["I_zz"].get<double>() * reciprocal_mass;

    auto tr_per_mass = 0.5 * (ixx_per_mass+iyy_per_mass+izz_per_mass);

    if (add_squared)
    {
      d["Rg^2"] = tr_per_mass;
      d["Rg^2(y+z)"] = ixx_per_mass;
      d["Rg^2(z+x)"] = iyy_per_mass;
      d["Rg^2(x+y)"] = izz_per_mass;
      d["Rg^2(x)"] = tr_per_mass - ixx_per_mass;
      d["Rg^2(y)"] = tr_per_mass - iyy_per_mass;
      d["Rg^2(z)"] = tr_per_mass - izz_per_mass;
    }

    if (add_sqrted)
    {
      d["Rg"] = sqrt(tr_per_mass);
      d["Rg(y+z)"] = sqrt(ixx_per_mass);
      d["Rg(z+x)"] = sqrt(iyy_per_mass);
      d["Rg(x+y)"] = sqrt(izz_per_mass);
      d["Rg(x)"] = sqrt(tr_per_mass - ixx_per_mass);
      d["Rg(y)"] = sqrt(tr_per_mass - iyy_per_mass);
      d["Rg(z)"] = sqrt(tr_per_mass - izz_per_mass);
    }
  }

  if (add_squared)
  {
    datakeys.add({
      "Rg^2", "Rg^2(y+z)", "Rg^2(z+x)", "Rg^2(x+y)",
      "Rg^2(x)", "Rg^2(y)", "Rg^2(z)"});
  }

  if (add_sqrted)
  {
    datakeys.add({
      "Rg", "Rg(y+z)", "Rg(z+x)", "Rg(x+y)",
      "Rg(x)", "Rg(y)", "Rg(z)"});
  }
}

/* ------------------------------------------------------------------ */

ShPtr<AddGyrationRadius> AddGyrationRadius::with_squared(
  bool add_squared_)
{
  add_squared = add_squared_;

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

ShPtr<AddGyrationRadius> AddGyrationRadius::without_sqrted(
  bool without_sqrted_)
{
  add_sqrted = !without_sqrted_;

  return shared_from_this();
}