import unittest
import traceback

from ppap4lmp import Element, StaCustom

class TestStaCustom(unittest.TestCase):

  def test_error(self):

    try:
      elem = Element(StaCustom([{"foo": 1}, {"var": 2}]))
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Invalid keys in array data")

  def test_get_data(self):

    self._test_get_data({"prop1": 1, "prop2": 0.1})
    self._test_get_data(
      [{"foo": i, "var": 0.1*i} for i in range(1000)])

  def _test_get_data(self, data):

    elem = Element(StaCustom(data))
    self.assertEqual(data, elem.get_data())

  def test_get_keys(self):

    self._test_get_keys({"prop1": 1, "prop2": 0.1}, {"prop1", "prop2"})
    self._test_get_keys(
      [{"A": i, "B": [2*i, i*i]} for i in range(100)], {"A", "B"})

  def _test_get_keys(self, data, keys):

    elem = Element(StaCustom(data))
    self.assertEqual(keys, elem.get_keys())
