/* ---------------------------------------------------------------------
Starter: is an abstract class to parse data from a file or other data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STARTER_H
#define STARTER_H

#include "updater.h"

class Starter : public Updater {
 public:
  Starter() = default;
  virtual ~Starter() = default;
  virtual void compute(nlohmann::json &) override;
  virtual const bool is_callable_as_initializer(std::string &) override;
 protected:
  std::string datatype_to_be_initialized;
};

/* ------------------------------------------------------------------ */
// for pubind11

static void pybind_starter(py::module &m)
{
  py::class_<Starter,PyUpdater<Starter>,Updater,std::shared_ptr<Starter>>(m, "Starter")
    .def(py::init<>());
}

#endif