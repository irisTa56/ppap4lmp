/*!
  @file src/adders/add_gyration_radius.cpp
  @brief This file has an implementation of AddGyrationRadius class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/15
*/

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

    d["Rg^2"] = tr_per_mass;
    d["Rg^2(y+z)"] = ixx_per_mass;
    d["Rg^2(z+x)"] = iyy_per_mass;
    d["Rg^2(x+y)"] = izz_per_mass;
    d["Rg^2(x)"] = tr_per_mass - ixx_per_mass;
    d["Rg^2(y)"] = tr_per_mass - iyy_per_mass;
    d["Rg^2(z)"] = tr_per_mass - izz_per_mass;

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


  datakeys.add({
    "Rg^2", "Rg^2(y+z)", "Rg^2(z+x)", "Rg^2(x+y)",
    "Rg^2(x)", "Rg^2(y)", "Rg^2(z)"});

  if (add_sqrted)
  {
    datakeys.add({
      "Rg", "Rg(y+z)", "Rg(z+x)", "Rg(x+y)",
      "Rg(x)", "Rg(y)", "Rg(z)"});
  }
}

/* ------------------------------------------------------------------ */

ShPtr<AddGyrationRadius> AddGyrationRadius::with_sqrted(
  bool add_sqrted_)
{
  add_sqrted = add_sqrted_;

  return shared_from_this();
}

/* ------------------------------------------------------------------ */
