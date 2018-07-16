/* ---------------------------------------------------------------------
ProValueArray: stands for Processor returning selected (double) Values
contained in Arrays.

create: 2018/07/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_VALUE_ARRAY_H
#define PRO_VALUE_ARRAY_H

#include "processor.h"

using ArrayXXdDict = std::unordered_map<std::string,ArrayXXd>;

class ProValueArray : public Processor {
  ArrayXXdDict results;
  std::vector<std::string> selected_keys;
  std::unordered_map<std::string,std::vector<RowArrayXd>> results_tmp;
 protected:
  virtual void run_impl(int) override;
  virtual void prepare_impl() override;
 public:
  using Processor::Processor;
  virtual ~ProValueArray() = default;
  virtual void finish() override;
  void select(py::args);
  const ArrayXXdDict &get_results();
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_pro_value_array(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<ProValueArray,PyProcessor<ProValueArray>,Processor,std::shared_ptr<ProValueArray>>(m, "ProValueArray")
    .def(py::init<std::shared_ptr<Generator>>())
    .def(py::init<std::vector<std::shared_ptr<Generator>>>())
    .def("select", &ProValueArray::select)
    .def("get_results", &ProValueArray::get_results);
}

#endif
