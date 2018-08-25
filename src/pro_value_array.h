/* ---------------------------------------------------------------------
ProValueArray: stands for Processor returning selected (double) Values
contained in Arrays.

create: 2018/07/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_VALUE_ARRAY_H
#define PRO_VALUE_ARRAY_H

#include "processor.h"

class ProValueArray : public Processor {
  bool do_sort = false;
  List<Str> selected_keys;
  Dict<Str,ArrayXXd> results;
  Dict<Str,List<RowArrayXd>> results_trajs;
  void run_sort(
    int index,
    const Json &data);
  void run_no_sort(
    int index,
    const Json &data);
 protected:
  virtual void run_impl(
    int index) override;
 public:
  ProValueArray(
    ShPtr<GenElement> elem);
  ProValueArray(
    List<ShPtr<GenElement>> elems);
  virtual ~ProValueArray() = default;
  virtual void prepare() override;
  virtual void finish() override;
  void select(
    py::args args);
  void force_sort(
    bool do_sort_ = true);
  const Dict<Str,ArrayXXd> &get_results();
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_pro_value_array(py::module &m)
{
  py::class_<ProValueArray,PyProcessor<ProValueArray>,Processor,ShPtr<ProValueArray>>(m, "ProValueArray")
    .def(py::init<ShPtr<GenElement>>())
    .def(py::init<List<ShPtr<GenElement>>>())
    .def("select", &ProValueArray::select)
    .def(
      "force_sort", &ProValueArray::force_sort,
      py::arg("do_sort_") = true)
    .def(
      "get_results", &ProValueArray::get_results,
      py::return_value_policy::reference_internal);
}

#endif
