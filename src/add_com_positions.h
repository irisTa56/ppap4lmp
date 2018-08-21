/* ---------------------------------------------------------------------
AddCoMPositions: stands for Adder for Center of Mass added as Position.

create: 2018/07/13 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_COM_POSITIONS_H
#define ADD_COM_POSITIONS_H

#include "adder.h"

class AddCoMPositions : public Adder {
  void compute_with_weights(
    Json &data,
    ShPtr<GenElement> gen_atoms);
  void compute_without_weights(
    Json &data,
    ShPtr<GenElement> gen_atoms);
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  AddCoMPositions(
    ShPtr<GenElement> elem);
  virtual ~AddCoMPositions() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_com_positions(py::module &m)
{
  py::class_<AddCoMPositions,PyUpdater<AddCoMPositions>,Adder,Updater,ShPtr<AddCoMPositions>>(m, "AddCoMPositions")
    .def(py::init<ShPtr<GenElement>>());
}

#endif