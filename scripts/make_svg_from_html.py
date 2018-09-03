htmlpath = "../doc/images/class_diagram.html"
svgpath = htmlpath[:-4] + "svg"

print(svgpath)

with open(htmlpath, "r") as f:

  data = "<svg" + f.read().split("<svg")[1].split("svg>")[0] + "svg>"

with open(svgpath, "w") as f:

  f.write(data)