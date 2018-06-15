import ppap4lmp as pp
import ppap4lmp.data as ppd
import ppap4lmp.processor as ppp

print("version: " + pp.__version__)

data_name = "test"

d = ppd.Data(data_name)
p = ppp.Processor()

p.execute(d)

assert p.get_result() == data_name

print("Pass! (^o^)b")
