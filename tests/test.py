from ppap4lmp import __version__, \
  Data, Processor

print("version: " + __version__)

data_name = "test"

d = Data(data_name)
p = Processor()

p.execute(d)

assert p.get_result() == data_name

print("Pass! (^o^)b")
