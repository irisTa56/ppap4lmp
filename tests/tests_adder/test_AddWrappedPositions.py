import unittest
import traceback

import numpy as np

from ppap4lmp import \
  create, StaCustom, StaDumpAtoms, StaDumpBox, AddWrappedPositions

class TestAddWrappedPositions(unittest.TestCase):

  def test_error01(self):

    box = create(StaCustom({"foo": 0, "bar": 1}))
    atoms = create(
      StaDumpAtoms("dumps_bead/bead.2990000.dump", 2990000))
    atoms.append_updater(AddWrappedPositions(box))

    try:
      atoms.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Missing key(s) 'hi_x', 'hi_y', 'hi_z', "
        + "'lo_x', 'lo_y', 'lo_z'")

  def test_error02(self):

    box = create(StaDumpBox("dumps_bead/bead.2990000.dump", 2990000))
    atoms = create(
      StaCustom([{"A": i, "B": i*i} for i in range(1000)]))
    atoms.append_updater(AddWrappedPositions(box))

    try:
      atoms.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Missing key(s) 'xu', 'yu', 'zu'")

  def test_wrapping(self):

    self._test_wrapping(("dumps_bead/bead.2990000.dump", 2990000))
    self._test_wrapping(("dumps_atom/atom.0.dump", 0))

  def _test_wrapping(self, arguments):

    box = create(StaDumpBox(*arguments))
    atoms = create(StaDumpAtoms(*arguments))
    atoms.append_updater(AddWrappedPositions(box))

    wrapped = atoms.get_2d_float("x", "y", "z")
    unwrapped = atoms.get_2d_float("xu", "yu", "zu")

    box_data = box.get_data()

    diff = unwrapped - wrapped
    diff_x = diff.T[0] / (box_data["hi_x"] - box_data["lo_x"])
    diff_y = diff.T[1] / (box_data["hi_y"] - box_data["lo_y"])
    diff_z = diff.T[2] / (box_data["hi_z"] - box_data["lo_z"])

    self.assertTrue(np.all(diff_x.round() == diff_x))
    self.assertTrue(np.all(diff_y.round() == diff_y))
    self.assertTrue(np.all(diff_z.round() == diff_z))