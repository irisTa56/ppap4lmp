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

const Eigen::VectorXi &DataBox::get_periodicity() {

  return get_iv("periodicity");

}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXd &DataBox::get_edge() {

  return get_da("edge");

}
