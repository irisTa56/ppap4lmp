/* ---------------------------------------------------------------------
This file is for Data class.

create: 2018/06/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "data.h"

/* ------------------------------------------------------------------ */

int Data::get_i(const std::string &key) {

  return prop_i[key];

}

/* ------------------------------------------------------------------ */

double Data::get_d(const std::string &key) {

  return prop_d[key];

}

/* ------------------------------------------------------------------ */

const Eigen::VectorXi &Data::get_iv(const std::string &key) {

  return prop_iv[key];

}

/* ------------------------------------------------------------------ */

const Eigen::VectorXd &Data::get_dv(const std::string &key) {

  return prop_dv[key];

}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXi &Data::get_ia(const std::string &key) {

  return prop_ia[key];

}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXd &Data::get_da(const std::string &key) {

  return prop_da[key];

}

/* ------------------------------------------------------------------ */

void Data::set_i(const std::string &key, int val) {

  prop_i[key] = val;

}

/* ------------------------------------------------------------------ */

void Data::set_d(const std::string &key, double val) {

  prop_d[key] = val;

}

/* ------------------------------------------------------------------ */

void Data::set_iv(const std::string &key, const Eigen::VectorXi &val) {

  prop_iv[key] = val;

}

/* ------------------------------------------------------------------ */

void Data::set_dv(const std::string &key, const Eigen::VectorXd &val) {

  prop_dv[key] = val;

}

/* ------------------------------------------------------------------ */

void Data::set_ia(const std::string &key, const Eigen::ArrayXXi &val) {

  prop_ia[key] = val;

}

/* ------------------------------------------------------------------ */

void Data::set_da(const std::string &key, const Eigen::ArrayXXd &val) {

  prop_da[key] = val;

}
