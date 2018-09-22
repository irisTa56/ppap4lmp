/*!
  @file src/starters/sta_molecules.h
  @brief This file has a definition of StaMolecules class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/07/07
*/

#ifndef STA_MOLECULES_H
#define STA_MOLECULES_H

#include <starters/starter.h>

/*!
  @brief StaMolecules sets properties for molecules
  using atoms forming the molecules.
  @details An object of this class owns an Element object for atoms
  forming molecules to be computed.
  Note that if molecular types are required elsewhere,
  one needs to add \c type property using an Adder object,
  such as an AddMap object.

  About usage in Python,
  please see src/pybind/starters/py_sta_molecules.h.
*/
class StaMolecules : public Starter {
 protected:
  /*!
    @copydoc Updater::compute_impl
    @details

    <table class="py_table2">
      <caption>
        StaMolecules related properties
      </caption>
      <tr class="py_tr">
        <th class="py_th2">Key for property to be set</th>
        <th class="py_th2">Key for required property</th>
        <th class="py_th2">Key for externally required property</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">
          - \c id : integer
          - \c atom-ids : array of integers
        </td>
        <td class="py_td">
          None.
        </td>
        <td class="py_td">
          - \c id : integer
          - \c mol : integer
        </td>
      </tr>
    </table>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of StaMolecules class.
    @param el_atoms : Shared pointer to an Element object for atoms
    forming molecules to be computed.
    This argument is assigned to #ext_generator.
  */
  StaMolecules(
    const ElPtr &el_atoms);
  virtual ~StaMolecules() = default;
};

#endif