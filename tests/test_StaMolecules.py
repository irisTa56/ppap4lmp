import unittest
import traceback

from ppap4lmp import Element, StaDumpBox, StaDumpAtoms, StaMolecules

class TestStaMolecules(unittest.TestCase):

  def test_error01(self):

    molecules = Element(StaMolecules(
      Element(StaDumpBox("dumps_bead/bead.2990000.dump", 2990000))))

    try:
      molecules.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: StaMolecules needs 'mol', 'id' externally")

  def test_get_data(self):

    self._test_get_data(
      ("dumps_bead/bead.2990000.dump", 2990000),
      6, set(range(120136, 120163)))

    self._test_get_data(
      ("dumps_atom/atom.0.dump", 0),
      5, set(range(153, 191)))

  def _test_get_data(self, arguments, expected_id, expected_atoms):

    molecules = Element(StaMolecules(Element(StaDumpAtoms(*arguments))))
    data = molecules.get_data()

    self.assertEqual(data[expected_id-1]["id"], expected_id)
    self.assertEqual(set(data[expected_id-1]["atom-ids"]), expected_atoms)

  def test_get_keys(self):

    self._test_get_keys(
      ("dumps_bead/bead.2990000.dump", 2990000), {"id", "atom-ids"})

    self._test_get_keys(
      ("dumps_atom/atom.0.dump", 0), {"id", "atom-ids"})

  def _test_get_keys(self, arguments, expectation):

    molecules = Element(StaMolecules(Element(StaDumpAtoms(*arguments))))

    self.assertEqual(molecules.get_keys(), expectation)
