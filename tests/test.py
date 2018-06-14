import ppap4lmp as pp
import ppap4lmp.data as ppd

print(pp.__version__)

data_name = "test"

d = ppd.Data(data_name)
assert d.get_name() == data_name

print("Pass! (^o^)b")
