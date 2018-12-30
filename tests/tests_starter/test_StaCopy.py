import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import check_error_msg

from ppap4lmp import create, StaCustom, StaCopy

class TestStaCopy(unittest.TestCase):

  def test_get_data(self):

    self._test_get_data({"prop1": 1, "prop2": 0.1})
    self._test_get_data(
      [{"foo": i, "bar": 0.1*i} for i in range(1000)])

  def _test_get_data(self, data):

    elem = create(StaCustom(data))
    elem2 = create(StaCopy(elem))

    self.assertEqual(elem.get_data(), elem2.get_data())

  def test_get_keys(self):

    self._test_get_keys({"prop1": 1, "prop2": 0.1}, {"prop1", "prop2"})
    self._test_get_keys(
      [{"A": i, "B": [2*i, i*i]} for i in range(100)], {"A", "B"})

  def _test_get_keys(self, data, keys):

    elem = create(StaCustom(data))
    elem2 = create(StaCopy(elem))

    self.assertEqual(elem.get_keys(), elem2.get_keys())

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestStaCopy("test_get_data"))
  suite.addTest(TestStaCopy("test_get_keys"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
