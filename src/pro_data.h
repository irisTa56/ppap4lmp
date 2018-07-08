/* ---------------------------------------------------------------------
ProData: stands for Processor which returns Data itself.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_DATA_H
#define PRO_DATA_H

#include "processor.h"

class ProData : public Processor {
  std::vector<std::string> selected_keys;
  std::vector<json> results;
 protected:
  virtual void run_impl(int) override;
  virtual void prepare_impl() override;
 public:
  using Processor::Processor;
  virtual ~ProData() = default;
  void select(py::args);
  const std::vector<json> &get_results();
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_pro_data(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<ProData,PyProcessor<ProData>,Processor,std::shared_ptr<ProData>>(m, "ProData")
    .def(py::init<std::shared_ptr<Generator>>())
    .def(py::init<std::vector<std::shared_ptr<Generator>>>())
    .def("select", &ProData::select)
    .def("get_results", &ProData::get_results);
}

#endif
