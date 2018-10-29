import unittest
import traceback

from random import shuffle

from ppap4lmp import create, StaCustom, ProValueArray, execute_omp

class TestProValueArray(unittest.TestCase):

  def test_error01(self):

    elems = [
      create(StaCustom({"id": i, "A": i*i})) for i in range(1000)]

    pro = ProValueArray(elems)

    try:
      execute_omp(pro)
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Selected value(s) for ProValueArray")

  def test_error02(self):

    elems = [
      create(StaCustom({"id": i, "A": i*i})) for i in range(1000)]

    pro = ProValueArray(elems)
    pro.select("B")

    try:
      execute_omp(pro)
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Missing key(s) 'B'")

  def test_error03(self):

    data = [
      [{"id": j, "A": float(i*j)} for j in range(10*i+1)]
      for i in range(100)]
    elems = [create(StaCustom(d)) for d in data]
    pro = ProValueArray(elems)
    pro.select("A")

    try:
      execute_omp(pro)
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Data sizes must be the same")

  def test_select_one(self):

    data = [[
      {"id": j, "A": float(i+j), "B": float(i*j)}
      for j in range(1000)]
      for i in range(100)]
    elems = [create(StaCustom(d)) for d in data]
    pro = ProValueArray(elems)
    pro.select("A")

    execute_omp(pro)

    arr_A = pro.get_results()["A"]

    for i, elem in enumerate(elems):

      ds = elem.get_data()

      for d in ds:
        self.assertEqual(arr_A[i][d["id"]], d["A"])

  def test_select_two(self):

    ids = list(range(1000))
    shuffle(ids)

    data = [[
      {"id": j, "A": float(i+j), "B": float(i*j)}
      for j in ids]
      for i in range(100)]
    elems = [create(StaCustom(d)) for d in data]

    pro = ProValueArray(elems)
    pro.select("A", "B")

    execute_omp(pro)

    arrs = pro.get_results()

    for i, elem in enumerate(elems):

      ds = elem.get_data()

      for d in ds:
        self.assertEqual(arrs["A"][i][d["id"]], d["A"])
        self.assertEqual(arrs["B"][i][d["id"]], d["B"])
