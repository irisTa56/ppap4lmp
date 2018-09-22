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
  @details An object of this class reads properties of simulation box
  from a Lammps' dump file specified by #filepath.
  Note that only properties at a time specified by #timestep are read.

  About usage in Python,
  please see src/pybind/starters/py_sta_dump_box.h.
*/
class StaDumpBox : public StaDump {
 protected:
  /*!
    @copydoc Updater::compute_impl
    @details
    <table class="py_table2">
      <caption>
        StaDumpBox related properties
      </caption>
      <tr class="py_tr">
        <th class="py_th2">Key for property to be set</th>
        <th class="py_th2">Key for required property</th>
        <th class="py_th2">Key for externally required property</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">
          - \c periodic_x : boolean
          - \c periodic_y : boolean
          - \c periodic_z : boolean
          - \c lo_x : float
          - \c lo_y : float
          - \c lo_z : float
          - \c hi_x : float
          - \c hi_y : float
          - \c hi_z : float
        </td>
        <td class="py_td">
          None.
        </td>
        <td class="py_td">
          None.
        </td>
      </tr>
    </table>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  //! Constructor of StaDumpBox class (inherited).
  using StaDump::StaDump;
  virtual ~StaDumpBox() = default;
};

#endif