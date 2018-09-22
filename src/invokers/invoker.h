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
  @brief Invoker is an abstract class to execute analysis
  defined by one or more Processor objects.
*/
class Invoker {
 protected:
   /*!
    @brief Processor objects to be executed.
    @details This member can be set only in the constructor.
  */
  Vec<ShPtr<Processor>> processors;
  /*!
    @brief Implementation how to execute
    a computationally expensive part of analysis.
    @return None.
    @details This is a pure virtual function, please see the subclasses
    for more details.
  */
  virtual void execute_impl() = 0;
 public:
  /*!
    @brief Constructor of Invoker class,
    which uses one Processor object.
    @param proc : Shared pointer to a Processor object.
    This argument is used for initializing #processors.
    @details This constructor is thread-unsafe because it accesses its
    members thread-globally. Ensure this constructor is not called in
    a multithreading context. Please be careful that constructors of
    subclasses of this class are also thread-unsafe.
  */
  Invoker(
    const ShPtr<Processor> &proc);
  /*!
    @brief Constructor of Invoker class,
    which uses multiple Processor objects.
    @param procs : ::Vec of shared pointers to a Processor object.
    This argument is assigned to #processors.
    @details This constructor is thread-unsafe because it accesses its
    members thread-globally. Ensure this constructor is not called in
    a multithreading context. Please be careful that constructors of
    subclasses of this class are also thread-unsafe.
  */
  Invoker(
    const Vec<ShPtr<Processor>> &procs);
  virtual ~Invoker() = default;
  /*!
    @brief Execute analysis defined by elements of #processors.
    @return None.
    @details First, this method calls Processor::startup
    of each object in #processors. Next, this method calls
    Processor::prepare of each object in #processors, and then calls
    #execute_impl where computationally expensive calculations are
    conducted. Finally, this method calls Processor::finish
    of each object in #processors.
  */
  void execute();
};

#endif
