import unittest
import traceback

import numpy as np

from ppap4lmp import Element, StaDumpAtoms, FilSet, FilComparison

class TestFilComparison(unittest.TestCase):

  def test_error01(self):

    atoms = Element(
      StaDumpAtoms("dumps_bead/bead.2990000.dump", 2990000))
    atoms.append_updater(FilComparison([("dummy", "<", 0)]))

    try:
      atoms.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: FilComparison needs 'dummy'")

  def test_error02(self):

    atoms = Element(
      StaDumpAtoms("dumps_bead/bead.2990000.dump", 2990000))
    atoms.append_updater(FilComparison([("mol", "dummy", 10)]))

    try:
      atoms.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: FilComparison supports six operators: "
        + "'<', '>', '<=', '>=', '==' and '!='")

  def test_equivalent_filter(self):

    self._test_equivalent_filter(
      ("dumps_bead/bead.2990000.dump", 2990000),
      {"mol": {7, 8, 9}}, [("mol", ">", 6), ("mol", "<", 10)])

    self._test_equivalent_filter(
      ("dumps_atom/atom.0.dump", 0),
      {"mol": {10, 11, 12, 13, 14, 15, 16, 17, 18, 19}},
       [("mol", ">=", 10), ("mol", "<", 20)])

  def _test_equivalent_filter(self, arguments, filterset, filtercom):

    atoms = Element(StaDumpAtoms(*arguments))
    filtered_atoms1 = Element(FilSet(atoms, filterset))
    filtered_atoms2 = Element(FilComparison(atoms, filtercom))

    self.assertEqual(
      filtered_atoms1.get_data(), filtered_atoms2.get_data())
    self.assertEqual(
      filtered_atoms1.get_keys(), filtered_atoms2.get_keys())

  def test_remaining_number(self):

    self._test_remaining_number(
      ("dumps_bead/bead.2990000.dump", 2990000), ("mol", "<=", 3), 81)

    self._test_remaining_number(
      ("dumps_atom/atom.0.dump", 0),
      [("mol", "<=", 3), ("type", "==", 1)], 36)

    self._test_remaining_number(
      ("dumps_atom/atom.0.dump", 0),
      [("mol", "<=", 2), ("type", "!=", 2)], 24)

  def _test_remaining_number(self, arguments, filtercom, num):

    atoms = Element(StaDumpAtoms(*arguments))
    atoms.append_updater(FilComparison(filtercom))

    self.assertEqual(len(atoms.get_data()), num)

  def test_de_morgan(self):

    self._test_de_morgan(
      ("dumps_bead/bead.2990000.dump", 2990000),
      "xu", 0.0, "yu", 0.0)

    self._test_de_morgan(
      ("dumps_atom/atom.0.dump", 0),
      "xu", 10.0, "zu", 10.0)

  def _test_de_morgan(self, arguments, key1, lim1, key2, lim2):

    atoms = Element(StaDumpAtoms(*arguments))
    num_total = len(atoms.get_data())

    filtered_atoms1 = Element(FilComparison(atoms, (key1, "<", lim1)))
    vec1 = filtered_atoms1.get_1d_double(key1)
    num1 = len(vec1)
    self.assertTrue(np.all(vec1 < lim1))

    filtered_atoms2 = Element(FilComparison(atoms, (key2, "<", lim2)))
    vec2 = filtered_atoms2.get_1d_double(key2)
    num2 = len(vec2)
    self.assertTrue(np.all(vec2 < lim2))

    filtered_atoms = Element(FilComparison(
      atoms, [(key1, "<", lim1), (key2, "<", lim2)]))
    arr = filtered_atoms.get_2d_double([key1, key2])
    num = arr.shape[0]
    self.assertTrue(np.all(arr.T[0] < lim1) and np.all(arr.T[1] < lim2))

    atoms.append_updater(
      FilComparison([(key1, ">=", lim1), (key2, ">=", lim2)]))

    self.assertEqual(
      len(atoms.get_data()) + num1 + num2 - num, num_total)
