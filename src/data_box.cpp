/* ---------------------------------------------------------------------
This file is for DataBox class.

create: 2018/06/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "data_box.h"

/* ------------------------------------------------------------------ */

DataBox::DataBox() : Data() {

  prop_iv["periodicity"] = Eigen::VectorXi::Zero(3);
  prop_da["edge"] = Eigen::ArrayXXd::Zero(3, 2);

}


/* ------------------------------------------------------------------ */

void DataBox::set_periodicity(const Eigen::VectorXi &val) {

  set_iv("periodicity", val);

}

/* ------------------------------------------------------------------ */

const Eigen::VectorXi &DataBox::get_periodicity() {

  return get_iv("periodicity");

}

/* ------------------------------------------------------------------ */

void DataBox::set_edge(const Eigen::ArrayXXd &val) {

  set_da("edge", val);

}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXd &DataBox::get_edge() {

  return get_da("edge");

}
