import unittest
import traceback

import numpy as np

from random import randrange

from ppap4lmp import \
  Element, StaCustom, StaDumpAtoms, StaMolecules, StaBeads, \
  AddMap, AddCoMPositions

class TestAddCoMPositions(unittest.TestCase):

  def test_error01(self):

    atoms = Element(
      StaDumpAtoms("dumps_bead/bead.2990000.dump", 2990000))
    molecules = Element(StaMolecules(atoms))

    molecules.append_updater(
      AddCoMPositions(Element(StaCustom({"foo": 0, "bar": 1}))))

    try:
      molecules.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddCoMPositions needs 'id', 'mass', 'xu', "
        + "'yu', 'zu' externally")

  def test_positions(self):

    atoms = Element(
      StaDumpAtoms("dumps_bead/bead.2990000.dump", 2990000))
    atoms.append_updater(AddMap("type", "mass", {1: 147.28}))

    self._test_positions(atoms)

    atoms = Element(
      StaDumpAtoms("dumps_dodecane_10000atm/atom.0.dump", 0))

    self._test_positions(atoms)

  def _test_positions(self, atoms):

    mols = Element(StaMolecules(atoms))
    mols.append_updater(AddCoMPositions(atoms))

    mol_data = mols.get_data()

    target = mol_data[randrange(len(mol_data))]

    atom_ids = set(target["atom-ids"])
    atom_data = atoms.get_data()

    tmpm = 0.0
    tmpx = 0.0
    tmpy = 0.0
    tmpz = 0.0

    for atom in atom_data:

      if atom["id"] in atom_ids:

        m = atom["mass"]

        tmpm += m
        tmpx += m * atom["xu"]
        tmpy += m * atom["yu"]
        tmpz += m * atom["zu"]

    tmpx /= tmpm
    tmpy /= tmpm
    tmpz /= tmpm

    self.assertEqual(target["xu"], tmpx)
    self.assertEqual(target["yu"], tmpy)
    self.assertEqual(target["zu"], tmpz)

  def test_beads(self):

    abst_atoms = []
    atom_id = 0

    for imol in range(10):
      for iatom in range(20):

        atom_id += 1

        abst_atoms.append({
          "id": atom_id,
          "mol": imol+1,
          "mass": 1.0,
          "xu": float(iatom//4)})

        if iatom%4 == 0:
          abst_atoms[-1]["yu"] = 1.0
          abst_atoms[-1]["zu"] = float(imol) * 10
        elif iatom%4 == 1:
          abst_atoms[-1]["yu"] = 0.0
          abst_atoms[-1]["zu"] = -1.0 + float(imol) * 10
        elif iatom%4 == 2:
          abst_atoms[-1]["yu"] = -1.0
          abst_atoms[-1]["zu"] = float(imol) * 10
        elif iatom%4 == 3:
          abst_atoms[-1]["yu"] = 0.0
          abst_atoms[-1]["zu"] = 1.0 + float(imol) * 10

    atoms = Element(StaCustom(abst_atoms))
    moles = Element(StaMolecules(atoms))
    beads = Element(StaBeads(moles, [
      {"indices-in-mol": list(range(4*i, 4*(i+1)))}
      for i in range(5)]))

    beads.append_updater(AddCoMPositions(atoms))

    rs = beads.get_2d_double(["xu", "yu", "zu"])

    expected_rs = []

    for imol in range(10):
      for ibead in range(5):

        expected_rs.append([float(ibead), 0.0, 10.0*imol])

    self.assertTrue(np.allclose(rs, np.array(expected_rs)))
