import unittest

from ppap4lmp import \
  log_switch, Element, StaDumpAtoms, \
  ProValueArray, ProData, InvOMP, AddMap

log_switch(False)

class TestProValueArray(unittest.TestCase):

  def __init__(self, *args, **kwargs):

    super().__init__(*args, **kwargs)

    self.args_list = [
      (".".join(["dumps_bead/bead", str(n), "dump"]), n)
      for n in range(2990000, 3000000, 1000)]

  def test_with_Atomses(self):

    print("\n\nTestProValueArray.test_with_Atomses:")

    expected_results = [
      [{"xu": 3.77161, "yu": 3.01851, "mass": 147.28},
        {"xu": -43.7141, "yu": -0.108626, "mass": 147.28}],
      [{"xu": 2.42064, "yu": 4.2208, "mass": 147.28},
        {"xu": 631.581, "yu": 220.847, "mass": 147.28}],
      [{"xu": 3.56883, "yu": 3.48234, "mass": 147.28},
        {"xu": 613.709, "yu": 220.913, "mass": 147.28}],
      [{"xu": 2.53184, "yu": 2.4027, "mass": 147.28},
        {"xu": 578.869, "yu": 313.452, "mass": 147.28}],
      [{"xu": 2.61604, "yu": 1.55081, "mass": 147.28},
        {"xu": 622.83, "yu": 220.889, "mass": 147.28}],
      [{"xu": 3.03762, "yu": 1.85909, "mass": 147.28},
        {"xu": 631.489, "yu": 220.766, "mass": 147.28}],
      [{"xu": 1.52936, "yu": 2.8839, "mass": 147.28},
        {"xu": 661.185, "yu": 244.144, "mass": 147.28}],
      [{"xu": 2.92311, "yu": 0.231183, "mass": 147.28},
        {"xu": 579.589, "yu": 258.126, "mass": 147.28}],
      [{"xu": 663.113, "yu": 66.2965, "mass": 147.28},
        {"xu": 643.749, "yu": 220.777, "mass": 147.28}],
      [{"xu": 6.57633, "yu": 2.11582, "mass": 147.28},
        {"xu": 591.039, "yu": 220.716, "mass": 147.28}]]

    gens = [
      Element(initializer)
      for initializer in [StaDumpAtoms(*args) for args in self.args_list]]

    for gen in gens:
      gen.append_updater(AddMap("type", "mass", {1: 147.28}))

    proc1 = ProValueArray(gens)
    proc1.select("xu", "yu", "mass")

    proc2 = ProData(gens)
    proc2.select("id")

    InvOMP([proc1, proc2]).execute()

    r1 = proc1.get_results()
    r2 = proc2.get_results()

    for i, exp in enumerate(expected_results):

      front_index = r2[i][0]["id"] - 120001

      front = {
        "xu": r1["xu"][i][front_index],
        "yu": r1["yu"][i][front_index],
        "mass": r1["mass"][i][front_index]}

      back_index = r2[i][-1]["id"] - 120001

      back = {
        "xu": r1["xu"][i][back_index],
        "yu": r1["yu"][i][back_index],
        "mass": r1["mass"][i][back_index]}

      self.assertEqual([front, back], exp)
