import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import TestCasePPAP

import numpy as np

from ppap4lmp import (
  create, StaCustom, StaDumpAtoms, StaDumpBox, AddWrappedPosition)

class TestAddWrappedPosition(TestCasePPAP):

  def test_error01(self):

    box = create(StaCustom({"foo": 0, "bar": 1}))
    atoms = create(
      StaDumpAtoms("dumps_bead/bead.2990000.dump", 2990000))
    atoms.append_updater(AddWrappedPosition(box))

    self.check_error_msg(
      "RuntimeError: Missing key(s) 'hi_x', 'hi_y', 'hi_z', 'lo_x', 'lo_y', 'lo_z' in AddWrappedPosition", atoms.get_data)

  def test_error02(self):

    box = create(StaDumpBox("dumps_bead/bead.2990000.dump", 2990000))
    atoms = create(
      StaCustom([{"A": i, "B": i*i} for i in range(1000)]))
    atoms.append_updater(AddWrappedPosition(box))

    self.check_error_msg(
      "RuntimeError: Missing key(s) 'xu', 'yu', 'zu' in AddWrappedPosition", atoms.get_data)

  def test_wrapping(self):

    self._test_wrapping(("dumps_bead/bead.2990000.dump", 2990000))
    self._test_wrapping(("dumps_atom/atom.0.dump", 0))

  def _test_wrapping(self, arguments):

    box = create(StaDumpBox(*arguments))
    atoms = create(StaDumpAtoms(*arguments))
    atoms.append_updater(AddWrappedPosition(box))

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

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddWrappedPosition("test_error01"))
  suite.addTest(TestAddWrappedPosition("test_error02"))
  suite.addTest(TestAddWrappedPosition("test_wrapping"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
