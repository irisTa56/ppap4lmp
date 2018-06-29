import unittest

from ppap4lmp import GenBox, ParDumpBox

class TestGenBoxDump(unittest.TestCase):

  def __init__(self, *args, **kwargs):

    super().__init__(*args, **kwargs)

    self.args_list = [
      (".".join(["tests/dumps_bead/bead", str(n), "dump"]), n)
      for n in range(2990000, 3000000, 1000)]

  def test_get_periodic(self):

    print("\n\nTestGenBoxDump.test_get_periodic:")

    expected_result = [True, True, False]

    gens = [GenBox() for i in range(len(self.args_list))]
    pars = [ParDumpBox(*args) for args in self.args_list]

    for gen, par in zip(gens, pars):
      gen.set_parser(par)

    for gen in gens:
      self.assertEqual(gen.get_periodic(), expected_result)

  def test_get_edge(self):

    print("\n\nTestGenBoxDump.test_get_edge:")

    expected_result = [
      {"min": 0.0, "max": 662.0},
      {"min": 0.0, "max": 331.0},
      {"min": 0.0, "max": 212.3},
    ]

    gens = [GenBox() for i in range(len(self.args_list))]
    pars = [ParDumpBox(*args) for args in self.args_list]

    for gen, par in zip(gens, pars):
      gen.set_parser(par)

    for gen in gens:
      self.assertEqual(gen.get_edge(), expected_result)
