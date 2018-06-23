import unittest

from ppap4lmp import GenBoxDump

class TestGenBoxDump(unittest.TestCase):

  def __init__(self, *args, **kwargs):

    super().__init__(*args, **kwargs)

    self.args_list = [
      (".".join(["tests/dumps_bead/bead", str(n), "dump"]), n)
      for n in range(2990000, 3000000, 1000)]

  def test_get_periodic(self):

    print("\n\nTestGenBoxDump.test_get_periodic:")

    expected_result = [True, True, False]

    for gen in [GenBoxDump(*args) for args in self.args_list]:
      self.assertEqual(gen.get_periodic(), expected_result)

  def test_get_edge(self):

    print("\n\nTestGenBoxDump.test_get_edge:")

    expected_result = [
      {"min": 0.0, "max": 662.0},
      {"min": 0.0, "max": 331.0},
      {"min": 0.0, "max": 212.3},
    ]

    for gen in [GenBoxDump(*args) for args in self.args_list]:
      self.assertEqual(gen.get_edge(), expected_result)
