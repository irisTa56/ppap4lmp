import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import check_error_msg

from ppap4lmp import create, StaDumpBox

class TestStaDumpBox(unittest.TestCase):

  def test_error01(self):

    box = create(StaDumpBox("dummy.file", 0))

    check_error_msg(
      self, "RuntimeError: No such a file 'dummy.file'", box.get_data)

  def test_get_data(self):

    self._test_get_data(
      ("dumps_bead/bead.2990000.dump", 2990000),
      {
        "pbc_x": True,
        "pbc_y": True,
        "pbc_z": False,
        "lo_x": 0.0, "hi_x": 662.0,
        "lo_y": 0.0, "hi_y": 331.0,
        "lo_z": 0.0, "hi_z": 212.3
      })

    self._test_get_data(
      ("dumps_atom/atom.0.dump", 0),
      {
        "pbc_x": True,
        "pbc_y": True,
        "pbc_z": True,
        "lo_x": 0.0, "hi_x": 3.7787347240000003e+01,
        "lo_y": 0.0, "hi_y": 3.7787347240000003e+01,
        "lo_z": 0.0, "hi_z": 3.7787347240000003e+01
      })

  def _test_get_data(self, arguments, expectation):

    box = create(StaDumpBox(*arguments))

    self.assertEqual(box.get_data(), expectation)

  def test_get_keys(self):

    self._test_get_keys(
      ("dumps_bead/bead.2990000.dump", 2990000),
      {
        "pbc_x", "pbc_y", "pbc_z",
        "lo_x", "hi_x", "lo_y", "hi_y", "lo_z", "hi_z"
      })

    self._test_get_keys(
      ("dumps_atom/atom.0.dump", 0),
      {
        "pbc_x", "pbc_y", "pbc_z",
        "lo_x", "hi_x", "lo_y", "hi_y", "lo_z", "hi_z"
      })

  def _test_get_keys(self, arguments, expectation):

    box = create(StaDumpBox(*arguments))

    self.assertEqual(box.get_keys(), expectation)

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestStaDumpBox("test_error01"))
  suite.addTest(TestStaDumpBox("test_get_data"))
  suite.addTest(TestStaDumpBox("test_get_keys"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
