import unittest

from ppap4lmp import \
  Element, StaDumpBox, StaDumpAtoms, GenList, GenDict

class TestContainer(unittest.TestCase):

  def __init__(self, *args, **kwargs):

    super().__init__(*args, **kwargs)

    self.args_list = [
      (".".join(["tests/dumps_bead/bead", str(n), "dump"]), n)
      for n in range(2990000, 3000000, 1000)]

  def test_list(self):

    print("\n\nTestContainer.test_list:")

    gens = [
      Element(initializer)
      for initializer in [StaDumpBox(*args) for args in self.args_list]]

    glist = GenList(gens)

    self.assertEqual(glist.get_datatype(), "List(Box)")
    self.assertEqual(glist.get_length(), 10)

  def test_dict(self):

    print("\n\nTestContainer.test_dict:")

    atoms = [
      Element(initializer)
      for initializer in [StaDumpAtoms(*args) for args in self.args_list]]

    boxes = [
      Element(initializer)
      for initializer in [StaDumpBox(*args) for args in self.args_list]]

    alist = GenList(atoms)
    blist = GenList(boxes)

    gdict = GenDict({atoms[0], boxes[0], alist, blist})

    self.assertEqual(
      gdict.get_datatype(), "Dict(Atoms,Box,List(Atoms),List(Box))")
    self.assertEqual(
      gdict.get_keys(), {"Atoms", "Box", "List(Atoms)", "List(Box)"})