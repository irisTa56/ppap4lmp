import unittest

import os
import sys
sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import check_error_msg

from ppap4lmp import create, StaCustom

class TestStaCustom(unittest.TestCase):

  def test_error01(self):

    elem = create(StaCustom([{"foo": 1}, {"bar": 2}]))

    check_error_msg(
      self, "RuntimeError: Invalid key(s) in array data", elem.get_data)

  def test_get_data(self):

    self._test_get_data({"prop1": 1, "prop2": 0.1})
    self._test_get_data(
      [{"foo": i, "bar": 0.1*i} for i in range(1000)])

  def _test_get_data(self, data):

    elem = create(StaCustom(data))
    self.assertEqual(data, elem.get_data())

  def test_get_keys(self):

    self._test_get_keys({"prop1": 1, "prop2": 0.1}, {"prop1", "prop2"})
    self._test_get_keys(
      [{"A": i, "B": [2*i, i*i]} for i in range(100)], {"A", "B"})

  def _test_get_keys(self, data, keys):

    elem = create(StaCustom(data))
    self.assertEqual(keys, elem.get_keys())

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestStaCustom("test_error01"))
  suite.addTest(TestStaCustom("test_get_data"))
  suite.addTest(TestStaCustom("test_get_keys"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
