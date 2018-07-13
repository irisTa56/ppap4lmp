/* ---------------------------------------------------------------------
AddCoMPosition: stands for Adder for Center of Mass added as Position.

create: 2018/07/13 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_COM_POSITION_H
#define ADD_COM_POSITION_H

#include "adder.h"

class AddCoMPosition : public Adder {
 protected:
  virtual void compute_impl(json &) override;
 public:
  AddCoMPosition(std::shared_ptr<Generator>);
  virtual ~AddCoMPosition() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_com_position(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddCoMPosition,PyUpdater<AddCoMPosition>,Adder,Updater,std::shared_ptr<AddCoMPosition>>(m, "AddCoMPosition")
    .def(py::init<std::shared_ptr<Generator>>());
}

#endif