/*!
  @file src/starters/sta_dump.h
  @brief This file has a definition of StaDump class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef STA_DUMP_H
#define STA_DUMP_H

#include <starters/starter.h>

/*!
  @brief StaDump is an abstract class whose subclasses read
  a Lammps' dump file.
  @details This class inherits Starter class.
  This class is an abstract class and has a pure virtual function,
  StaDump::compute_impl.
*/
class StaDump : public Starter {
 protected:
  /*!
    @brief A timestep of simulation to be read.
    @details In a Lammps' dump file, this value is printed
    below the line saying <c>ITEM: TIMESTEP</c>. This member is
    useful to read one timestep from a Lammps' dump file containing
    multiple timesteps.
  */
  int timestep;
  //! A path to a Lammps' dump file to be read.
  Str filepath;
 public:
  /*!
    @brief Constructor of StaDump class.
    @param filepath_ : A path to a Lammps' dump file to be read.
    This argument is assigned to #filepath.
    @param timestep_ : A timestep of simulation to be read.
    This argument is assigned to #timestep.
  */
  StaDump(
    const Str &filepath_,
    const int timestep_);
  virtual ~StaDump() = default;
};

#endif