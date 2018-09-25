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
    Processor objects to be executed.
    This member can be set only in the constructor.
  */
  Vec<ShPtr<Processor>> processors;
  /*!
    @brief Implementation how to execute a main part of analysis.
    @return None.
  */
  virtual void execute_impl() = 0;
 public:
  /*!
    @brief Constructor of Invoker class,
    which uses one Processor object.

    @param proc
      A Processor object to be executed.

    <span class="remove_in_table">
      This constructor is thread-unsafe because it accesses its
      members thread-globally. Ensure this constructor is not called in
      a multithreading context. Please be careful that constructors of
      subclasses of this class are also thread-unsafe.
    </span>
  */
  Invoker(
    const ShPtr<Processor> &proc);
  /*!
    @brief Constructor of Invoker class,
    which uses multiple Processor objects.

    @param procs
      List of Processor objects to be executed.

    <span class="remove_in_table">
      This constructor is thread-unsafe because it accesses its
      members thread-globally. Ensure this constructor is not called in
      a multithreading context. Please be careful that constructors of
      subclasses of this class are also thread-unsafe.
    </span>
  */
  Invoker(
    const Vec<ShPtr<Processor>> &procs);
  virtual ~Invoker() = default;
  /*!
    @brief Execute analysis programmed in Processor objects
    owned by this object.

    @return None.

    First, this method calls Processor::startup
    of each object in #processors. Next, this method calls
    Processor::prepare of each object in #processors, and then calls
    #execute_impl where computationally expensive calculations are
    conducted. Finally, this method calls Processor::finish
    of each object in #processors.
  */
  void execute();
};

#endif
