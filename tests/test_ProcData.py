import unittest

from ppap4lmp import GenBoxDump, ProcData, InvOMP

class TestProcData(unittest.TestCase):

  def __init__(self, *args, **kwargs):

    super().__init__(*args, **kwargs)

    self.args_list = [
      (".".join(["tests/dumps_bead/bead", str(n), "dump"]), n)
      for n in range(2990000, 3000000, 1000)]

  def test_with_select(self):

    print("\n\nTestGenBoxDump.test_with_select:")

    expected_result = {"min_x": 0.0, "max_x": 662.0}

    proc = ProcData([GenBoxDump(*args) for args in self.args_list])

    proc.select("min_x", "max_x")

    InvOMP(proc).execute()

    results = proc.get_results()

    for r in results:
      self.assertEqual(r, expected_result)

  def test_without_select(self):

    print("\n\nTestGenBoxDump.test_without_select:")

    expected_result = [212.3, False]

    proc = ProcData([GenBoxDump(*args) for args in self.args_list])

    InvOMP(proc).execute()

    results = proc.get_results()

    for r in results:
      self.assertEqual([r["max_z"], r["periodic_z"]], expected_result)
