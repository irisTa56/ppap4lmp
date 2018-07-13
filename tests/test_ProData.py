import unittest

from ppap4lmp import \
  log_switch, Element, StaDumpBox, StaDumpAtoms, \
  ProData, InvOMP, AddMap

log_switch(False)

class TestProData(unittest.TestCase):

  def __init__(self, *args, **kwargs):

    super().__init__(*args, **kwargs)

    self.args_list = [
      (".".join(["dumps_bead/bead", str(n), "dump"]), n)
      for n in range(2990000, 3000000, 1000)]

  def test_with_Boxes(self):

    print("\n\nTestProData.test_with_Boxes:")

    expected_result = {"min_x": 0.0, "max_x": 662.0, "pbc_x": True}

    gens = [
      Element(initializer)
      for initializer in [StaDumpBox(*args) for args in self.args_list]]

    proc1 = ProData(gens)

    proc2 = ProData(gens)
    proc2.select("min_x", "max_x")

    InvOMP([proc1, proc2]).execute()

    for r1, r2 in zip(proc1.get_results(), proc2.get_results()):

      r2["pbc_x"] = r1["periodic_x"]
      self.assertEqual(r2, expected_result)

  def test_with_Atomses(self):

    print("\n\nTestProData.test_with_Atomses:")

    expected_results = [
      [{"xu": 3.77161, "yu": 3.01851, "type": 1},
        {"xu": -43.7141, "yu": -0.108626, "mass": 147.28}],
      [{"xu": 2.42064, "yu": 4.2208, "type": 1},
        {"xu": 631.581, "yu": 220.847, "mass": 147.28}],
      [{"xu": 3.56883, "yu": 3.48234, "type": 1},
        {"xu": 613.709, "yu": 220.913, "mass": 147.28}],
      [{"xu": 2.53184, "yu": 2.4027, "type": 1},
        {"xu": 578.869, "yu": 313.452, "mass": 147.28}],
      [{"xu": 2.61604, "yu": 1.55081, "type": 1},
        {"xu": 622.83, "yu": 220.889, "mass": 147.28}],
      [{"xu": 3.03762, "yu": 1.85909, "type": 1},
        {"xu": 631.489, "yu": 220.766, "mass": 147.28}],
      [{"xu": 1.52936, "yu": 2.8839, "type": 1},
        {"xu": 661.185, "yu": 244.144, "mass": 147.28}],
      [{"xu": 2.92311, "yu": 0.231183, "type": 1},
        {"xu": 579.589, "yu": 258.126, "mass": 147.28}],
      [{"xu": 663.113, "yu": 66.2965, "type": 1},
        {"xu": 643.749, "yu": 220.777, "mass": 147.28}],
      [{"xu": 6.57633, "yu": 2.11582, "type": 1},
        {"xu": 591.039, "yu": 220.716, "mass": 147.28}]]

    gens = [
      Element(initializer)
      for initializer in [StaDumpAtoms(*args) for args in self.args_list]]

    for gen in gens:
      gen.append_updater(AddMap("type", "mass", {1: 147.28}))

    proc1 = ProData(gens)

    proc2 = ProData(gens)
    proc2.select("xu", "yu")

    InvOMP([proc1, proc2]).execute()

    for r1, r2, exp in zip(
      proc1.get_results(), proc2.get_results(), expected_results):

      head_tail = [r2[0], r2[-1]]
      head_tail[0]["type"] = r1[0]["type"]
      head_tail[1]["mass"] = r1[-1]["mass"]

      self.assertEqual(head_tail, exp)

  def test_with_Atomses_oneUpdater(self):

    print("\n\nTestProData.test_with_Atomses_oneUpdater:")

    expected_results = [
      [{"xu": 3.77161, "yu": 3.01851, "type": 1},
        {"xu": -43.7141, "yu": -0.108626, "mass": 147.28}],
      [{"xu": 2.42064, "yu": 4.2208, "type": 1},
        {"xu": 631.581, "yu": 220.847, "mass": 147.28}],
      [{"xu": 3.56883, "yu": 3.48234, "type": 1},
        {"xu": 613.709, "yu": 220.913, "mass": 147.28}],
      [{"xu": 2.53184, "yu": 2.4027, "type": 1},
        {"xu": 578.869, "yu": 313.452, "mass": 147.28}],
      [{"xu": 2.61604, "yu": 1.55081, "type": 1},
        {"xu": 622.83, "yu": 220.889, "mass": 147.28}],
      [{"xu": 3.03762, "yu": 1.85909, "type": 1},
        {"xu": 631.489, "yu": 220.766, "mass": 147.28}],
      [{"xu": 1.52936, "yu": 2.8839, "type": 1},
        {"xu": 661.185, "yu": 244.144, "mass": 147.28}],
      [{"xu": 2.92311, "yu": 0.231183, "type": 1},
        {"xu": 579.589, "yu": 258.126, "mass": 147.28}],
      [{"xu": 663.113, "yu": 66.2965, "type": 1},
        {"xu": 643.749, "yu": 220.777, "mass": 147.28}],
      [{"xu": 6.57633, "yu": 2.11582, "type": 1},
        {"xu": 591.039, "yu": 220.716, "mass": 147.28}]]

    gens = [
      Element(initializer)
      for initializer in [StaDumpAtoms(*args) for args in self.args_list]]

    mass_map = AddMap("type", "mass", {1: 147.28})

    for gen in gens:
      gen.append_updater(mass_map)

    proc = ProData(gens)
    proc.select("xu", "yu", "type", "mass")

    InvOMP(proc).execute()

    for r, exp in zip(proc.get_results(), expected_results):

      r1 = r[0]
      r2 = r[-1]

      self.assertEqual([
        {"xu": r1["xu"], "yu": r1["yu"], "type": r1["type"]},
        {"xu": r2["xu"], "yu": r2["yu"], "mass": r2["mass"]}], exp)
