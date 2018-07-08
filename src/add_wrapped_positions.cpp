/* ---------------------------------------------------------------------
AddWrappedPositions: stands for Adder for Wrapped Postisions ('x', 'y',
'z').

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_wrapped_positions.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddWrappedPositions::AddWrappedPositions(
  std::shared_ptr<Generator> gen)
{
  if (gen->get_datatype() == "Box")
  {
    reference_generator = gen;
  }
  else
  {
    runtime_error(
      "AddWrappedPositions cannot use " + gen->get_dataname());
  }

  callable_datatypes = {"Atoms", "Molecules", "Beads"};
}

/* ------------------------------------------------------------------ */

void AddWrappedPositions::compute_impl(nlohmann::json &data)
{

}
