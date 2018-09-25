/*!
  @file src/starters/sta_dump_box.h
  @brief This file has a definition of StaDumpBox class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef STA_DUMP_BOX_H
#define STA_DUMP_BOX_H

#include <starters/sta_dump.h>

/*!
  @brief StaDumpBox reads a Lammps' dump file
  and sets properties for simulation box.

  An object of this class reads properties of simulation box
  from a Lammps' dump file specified by #filepath.
  Note that only properties at a time specified by #timestep are read.

  About usage in Python,
  please see pybind::py_sta_dump_box.
*/
class StaDumpBox : public StaDump {
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - \c periodic_x : boolean
        - \c periodic_y : boolean
        - \c periodic_z : boolean
        - \c lo_x : float
        - \c lo_y : float
        - \c lo_z : float
        - \c hi_x : float
        - \c hi_y : float
        - \c hi_z : float
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  using StaDump::StaDump;
  virtual ~StaDumpBox() = default;
};

#endif