/*!
  @file src/processors/processor.h
  @brief This file has a definition of Processor class,
  where an analysis process is programmed.
  @author Takayuki Kobayashi
  @date 2018/06/22
*/

#ifndef PROESSOR_H
#define PROESSOR_H

#include <core/generators.h>

/*!
  @brief Processor analyzes data contained
  in one or more Generator objects.
*/
class Processor {
  /*!
    Index in #generators for a Generator object currently used
    for analysis. This member is set to 0 in #startup,
    and updated in #run. Both the modifications are thread-safe.
  */
  int i_generator;
 protected:
  /*!
    Length of #generators. Considering a dynamics simulation,
    for example, a length of #generators is equal to a length
    of the simulation trajectory.
  */
  int n_generators;
   /*!
    A sequence of Generators objects to be used for analysis.
    This member can be set only by #register_generator
    or #register_generators.
  */
  Vec<ShPtr<Generator>> generators;
  /*!
    @brief Implementation of analysis using an element of #generators.

    @param index
      An index in #generators for a Generator object to be analyzed.

    @return None.
  */
  virtual void run_impl(const int index) = 0;
  /*!
    Store an object of Element, GenDict or GenList class
    in #generators.

    @param gen
      Shared pointer to an object of Element, GenDict or GenList class.
      This pointer is up-casted to a shared pointer of Generator class
      when being stored in #generators.

    @return None.

    Note that this method is thread-unsafe because it accesses
    its members thread-globally. It is recommended to call this method
    only from constructors of subclasses of this class. Please ensure
    that these constructors are used outside a multithreading context.
  */
  template <class GEN>
  void register_generator(
    const ShPtr<GEN> &gen);
  /*!
    Store objects of Element, GenDict or GenList class
    in #generators.

    @param gens
      List of shared pointers to objects of Element, GenDict
      or GenList class. These pointers are up-casted to
      shared pointers of Generator class when being stored
      in #generators.

    @return None.

    Note that this method is thread-unsafe because it accesses
    its members thread-globally. It is recommended to call this method
    only from constructors of subclasses of this class. Please ensure
    that these constructors are used outside a multithreading context.
  */
  template <class GEN>
  void register_generators(
    const Vec<ShPtr<GEN>> &gens);
 public:
  //! Constructor of Processor class (default).
  Processor() = default;
  virtual ~Processor() = default;
  /*!
    @brief Prepare analysis.

    @return None.

    This method is called in Invoker::execute.
    Please see the subclasses for more details
    (some subclasses do nothing by this method).
  */
  virtual void prepare() {}
  /*!
    @brief Finish analysis.

    @return None.

    This method is called in Invoker::execute.
    Please see the subclasses for more details
    (some subclasses do nothing by this method).
  */
  virtual void finish() {}
  /*!
    @brief Run analysis using \e i th Generator object in #generators,
    where \e i = #i_generator.

    @return A boolean whether all Generator objects in #generators
    have finished being used in #run_impl.

    First, this method copies #i_generator as an index in #generators
    for a Generator object to be analyzed.
    This method then calls Generator::hello
    to execute updating processes associated with the Generator object,
    and calls #run_impl taking the copied index,
    and finally calls Generator::goodbye
    to clears Element::data if it is no longer to be used.
  */
  virtual bool run();
  /*!
    @brief Startup this Processor object.

    @return None.

    This method (re)sets #i_generator to 0, and then
    calls Generator::appoint of Generator objects in #generators.
  */
  void startup();
};

#endif
