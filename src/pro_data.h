/* ---------------------------------------------------------------------
ProData: stands for Processor which returns Data itself.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PROC_DATA_H
#define PROC_DATA_H

#include "processor.h"

class ProData : public Processor {
 public:
  ProData(
    std::shared_ptr<Generator> gen) : Processor(gen) {}
  ProData(
    std::vector<std::shared_ptr<Generator>> gens) : Processor(gens) {}
  virtual ~ProData() = default;
  void select(pybind11::args);
  const std::vector<nlohmann::json> &get_results();
 protected:
  virtual void run_impl(int i_generator) override;
  virtual void prepare_impl() override;
 private:
  std::vector<std::string> selected_keys;
  std::vector<nlohmann::json> results;
};

/* ------------------------------------------------------------------ */
// for pubind11

static void pybind_pro_data(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<ProData,PyProcessor<ProData>,Processor,std::shared_ptr<ProData>>(m, "ProData")
    .def(py::init<std::shared_ptr<Generator>>())
    .def(py::init<std::vector<std::shared_ptr<Generator>>>())
    .def("select", &ProData::select)
    .def("get_results", &ProData::get_results,
      py::return_value_policy::reference_internal);
}

#endif
