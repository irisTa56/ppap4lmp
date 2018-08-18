import unittest
import traceback

import numpy as np

from ppap4lmp import \
  Element, StaCustom, StaDumpAtoms, StaDumpBox, AddWrappedPositions

class TestAddWrappedPositions(unittest.TestCase):

  def test_error(self):

    box = Element(StaCustom({"foo": 0, "bar": 1}))
    atoms = Element(
      StaDumpAtoms("dumps_bead/bead.2990000.dump", 2990000))
    atoms.append_updater(AddWrappedPositions(box))

    try:
      atoms.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddWrappedPositions needs 'lo_*' and 'hi_*' "
        + "(x/y/z) externally")

    box = Element(StaDumpBox("dumps_bead/bead.2990000.dump", 2990000))
    atoms = Element(
      StaCustom([{"A": i, "B": i*i} for i in range(1000)]))
    atoms.append_updater(AddWrappedPositions(box))

    try:
      atoms.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddWrappedPositions needs 'xu', 'yu' and 'zu'")

  def test_wrapping(self):

    self._test_wrapping(("dumps_bead/bead.2990000.dump", 2990000))
    self._test_wrapping(("dumps_dodecane_10000atm/atom.0.dump", 0))

  def _test_wrapping(self, arguments):

    box = Element(StaDumpBox(*arguments))
    atoms = Element(StaDumpAtoms(*arguments))
    atoms.append_updater(AddWrappedPositions(box))

    wrapped = atoms.get_2d_double(["x", "y", "z"])
    unwrapped = atoms.get_2d_double(["xu", "yu", "zu"])

    box_data = box.get_data()

    diff = unwrapped - wrapped
    diff_x = diff.T[0] / (box_data["hi_x"] - box_data["lo_x"])
    diff_y = diff.T[1] / (box_data["hi_y"] - box_data["lo_y"])
    diff_z = diff.T[2] / (box_data["hi_z"] - box_data["lo_z"])

    self.assertTrue(np.all(diff_x.round() == diff_x))
    self.assertTrue(np.all(diff_y.round() == diff_y))
    self.assertTrue(np.all(diff_z.round() == diff_z))