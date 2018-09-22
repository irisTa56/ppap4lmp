/*!
  @file src/invokers/inv_omp.h
  @brief This file has a definition of InvOMP class,
  which is a subclass of Invoker class.
  @author Takayuki Kobayashi
  @date 2018/06/23
*/

#ifndef INV_OMP_H
#define INV_OMP_H

#include <invokers/invoker.h>

/*!
  @brief InvOMP is an Invoker's subclass using OpenMP to execute
  a computationally expensive part of analysis.
  @details This class executes a computationally expensive calculation,
  such as an update process defined by Generator::update_chain
  or analytical computations conducted in Processor::run_impl,
  under multithread environment using OpenMP.
  An object of this class use all threads
  if the \c OMP_NUM_THREADS environment variable is not set.

  Please be careful when you modify any member of any object
  in a multithreading context!!

  About usage in Python,
  please see src/pybind/invokers/py_inv_omp.h.
*/
class InvOMP : public Invoker {
 protected:
  /*!
    @brief Implementation how to execute
    a computationally expensive part of analysis.
    @return None.
    @details This method calls Processor::run in parallel.
    Note that exceptions (runtime errors)
    thrown inside the parallel scope must be catched in the same scope.
    Since error messages thrown in the parallel scope are assigned to
    a thread-global variable, older error messages are overwritten
    by newer one thrown in another thread.
  */
  virtual void execute_impl() override;
 public:
  //! Constructor of InvOMP class (inherited).
  using Invoker::Invoker;
  virtual ~InvOMP() = default;
};

#endif
