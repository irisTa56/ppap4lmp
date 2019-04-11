/*!
  @file src/invokers/invoker.h
  @brief This file has a definition of Invoker class,
  which executes one or more analysis.
  @author Takayuki Kobayashi
  @date 2018/06/23
*/

#ifndef INVOKER_H
#define INVOKER_H

#include <processors/processor.h>

/*!
  @brief Invoker executes analysis programmed
  in one or more Processor objects.
*/
class Invoker {
 protected:
  /*!
    @brief Implementation how to execute a main part of analysis.
    @return None.
  */
  virtual void execute_impl(
    const Vec<ShPtr<Processor>> &procs) = 0;
 public:
  //! Constructor of Invoker class (default).
  Invoker() = default;
  virtual ~Invoker() = default;
  /*!
    @brief Execute analysis programmed in given Processor objects.

    @param procs
      List of Processor objects to be executed.

    @return None.

    First, this method calls Processor::startup.
    Next, this method calls Processor::prepare, and then calls
    #execute_impl where computationally expensive calculations are
    conducted. Finally, this method calls Processor::finish.
  */
  void execute(
    const Vec<ShPtr<Processor>> &procs);
};

#endif
