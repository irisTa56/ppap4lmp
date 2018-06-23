import unittest

from ppap4lmp import GenAtomsDump

class TestGenAtomsDump(unittest.TestCase):

  def __init__(self, *args, **kwargs):

    super().__init__(*args, **kwargs)

    self.args_list = [
      (".".join(["tests/dumps_bead/bead", str(n), "dump"]), n)
      for n in range(2990000, 3000000, 1000)]

  def test_position_type(self):

    print("\n\nTestGenAtomsDump.test_position_type:")

    expected_result = [False, False, True, False]

    for gen in [GenAtomsDump(*args) for args in self.args_list]:
      self.assertEqual([
        gen.is_unscaled(False),
        gen.is_scaled(False),
        gen.is_unwrapped(False),
        gen.is_scaled_unwrapped(False)], expected_result)

  def test_get_positions(self):

    print("\n\nTestGenAtomsDump.test_get_positions:")

    expected_results = [
      [3.77161, 3.01851, 14.3644, -43.7141, -0.108626, 14.3606],
      [2.42064, 4.2208, 14.338, 631.581, 220.847, 18.7689],
      [3.56883, 3.48234, 14.2686, 613.709, 220.913, 23.3183],
      [2.53184, 2.4027, 15.6776, 578.869, 313.452, 25.3019],
      [2.61604, 1.55081, 14.7762, 622.83, 220.889, 24.0168],
      [3.03762, 1.85909, 15.1187, 631.489, 220.766, 25.3291],
      [1.52936, 2.8839, 14.2927, 661.185, 244.144, 14.09],
      [2.92311, 0.231183, 14.3673, 579.589, 258.126, 14.2919],
      [663.113, 66.2965, 25.9261, 643.749, 220.777, 19.0525],
      [6.57633, 2.11582, 14.911, 591.039, 220.716, 27.2747]]

    for gen, exp in zip(
      [GenAtomsDump(*args) for args in self.args_list], expected_results):

      ps = gen.get_positions("unwrapped")
      self.assertEqual(list(ps[0])+list(ps[-1]), exp)
