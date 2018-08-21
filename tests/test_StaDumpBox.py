import unittest
import traceback

from ppap4lmp import Element, StaDumpBox

class TestStaDumpBox(unittest.TestCase):

  def test_error01(self):

    box = Element(StaDumpBox("dummy.file", 0))

    try:
      box.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: No such a file: dummy.file")

  def test_get_data(self):

    self._test_get_data(
      ("dumps_bead/bead.2990000.dump", 2990000),
      {
        "periodic_x": True,
        "periodic_y": True,
        "periodic_z": False,
        "lo_x": 0.0, "hi_x": 662.0,
        "lo_y": 0.0, "hi_y": 331.0,
        "lo_z": 0.0, "hi_z": 212.3
      })

    self._test_get_data(
      ("dumps_dodecane_10000atm/atom.0.dump", 0),
      {
        "periodic_x": True,
        "periodic_y": True,
        "periodic_z": True,
        "lo_x": 0.0, "hi_x": 3.7787347240000003e+01,
        "lo_y": 0.0, "hi_y": 3.7787347240000003e+01,
        "lo_z": 0.0, "hi_z": 3.7787347240000003e+01
      })

  def _test_get_data(self, arguments, expectation):

    box = Element(StaDumpBox(*arguments))

    self.assertEqual(box.get_data(), expectation)

  def test_get_keys(self):

    self._test_get_keys(
      ("dumps_bead/bead.2990000.dump", 2990000),
      {
        "periodic_x", "periodic_y", "periodic_z",
        "lo_x", "hi_x", "lo_y", "hi_y", "lo_z", "hi_z"
      })

    self._test_get_keys(
      ("dumps_dodecane_10000atm/atom.0.dump", 0),
      {
        "periodic_x", "periodic_y", "periodic_z",
        "lo_x", "hi_x", "lo_y", "hi_y", "lo_z", "hi_z"
      })

  def _test_get_keys(self, arguments, expectation):

    box = Element(StaDumpBox(*arguments))

    self.assertEqual(box.get_keys(), expectation)
