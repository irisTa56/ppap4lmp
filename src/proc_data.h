/* ---------------------------------------------------------------------
ProcData: stands for Processor which returns Data itself.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PROC_DATA_H
#define PROC_DATA_H

#include "processor.h"

class ProcData : public Processor {
 public:
  ProcData(
    std::shared_ptr<Generator> gen) : Processor(gen) {}
  ProcData(
    std::vector<std::shared_ptr<Generator>> gens) : Processor(gens) {}
  virtual ~ProcData() = default;
  void select(pybind11::args);
  const std::vector<nlohmann::json> &get_results();
 protected:
  std::vector<std::string> selected_keys;
  std::vector<nlohmann::json> results;
  virtual void run_impl(int i_generator) override;
  virtual void prepare_impl() override;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_proc_data(py::module &m) {
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<ProcData,PyProcessor<ProcData>,Processor,std::shared_ptr<ProcData>>(m, "ProcData")
    .def(py::init<std::shared_ptr<Generator>>())
    .def(py::init<std::vector<std::shared_ptr<Generator>>>())
    .def("select", &ProcData::select)
    .def("get_results", &ProcData::get_results,
      py::return_value_policy::reference_internal);

}

#endif
