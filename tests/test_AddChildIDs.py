import unittest
import traceback

from ppap4lmp import \
  Element, StaCustom, StaDumpAtoms, StaMolecules, AddChildIDs

class TestAddChildIDs(unittest.TestCase):

  def test_error(self):

    atoms = Element(StaCustom(
      [{"id": i, "mol": i//10} for i in range(100)]))
    moles = Element(StaCustom([{"id": i} for i in range(10)]))

    moles.append_updater(AddChildIDs(atoms, "atom", "molecule-id"))

    try:
      moles.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddChildIDs needs 'id', 'molecule-id' externally")

    atoms = Element(StaCustom(
      [{"id": i, "mol": i//10} for i in range(100)]))
    moles = Element(StaCustom([{"index": i} for i in range(10)]))

    moles.append_updater(AddChildIDs(atoms, "atom", "mol"))

    try:
      moles.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddChildIDs needs 'id'")

  def test_2way_molecules(self):

    self._test_2way_molecules(
      ("dumps_bead/bead.2990000.dump", 2990000),
      list(range(1, 1001)))

    self._test_2way_molecules(
      ("dumps_dodecane_10000atm/atom.0.dump", 0),
      list(range(1, 181)))

  def _test_2way_molecules(self, arguments, mol_ids):

    atoms = Element(StaDumpAtoms(*arguments))

    mols1 = Element(StaMolecules(atoms))

    mols2 = Element(StaCustom([{"id": i} for i in mol_ids]))
    mols2.append_updater(AddChildIDs(atoms, "atom", "mol"))

    self.assertEqual(mols1.get_data(), mols2.get_data())
