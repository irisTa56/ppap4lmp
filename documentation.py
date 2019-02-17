#!/usr/bin/env python

# execute Doxygen

import os
import subprocess

version_ns = {}
with open(os.path.join("ppap4lmp", "_version.py")) as f:
  exec(f.read(), {}, version_ns)

dox_env = os.environ.copy()
dox_env["PROJECT_NUMBER"] = ".".join(
  map(str, version_ns["version_info"][:3]))

p = subprocess.run(
  ['doxygen', 'Doxyfile'],
  stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=dox_env)

lines = p.stderr.decode().split("\n")

for line in lines:

  if not (
    ("src/pybind" in line or "src/ppap4lmp.cpp" in line)
    and (
      "could not be resolved" in line
      or "override (function) of class Py" in line)
      or "@param is not found in the argument list of pybind::" in line):
    print(line)

# modify generated HTML file

from bs4 import BeautifulSoup

htmlpath = "docs/index.html"

with open(htmlpath, "r") as f:
  contents = f.read()

mainpage = BeautifulSoup(contents, "html.parser")

def modify_table(soup):

  for dl_return in soup.find_all("dl", class_="section return"):
    dl_return.extract()

  for h1 in soup.find_all("h1"):
    h1["class"] = "main_page"

  for h2 in soup.find_all("h2"):
    h2["class"] = "main_page"

  for h3 in soup.find_all("h3"):
    h3["class"] = "main_page"

  for span in soup.find_all("span", class_="remove_in_table"):
    span.extract()

  for p_endtd in soup.find_all("p", class_="endtd"):
    p_endtd.extract()

  for dt in soup.find_all("dt"):
    try:
      if "property" in dt["class"]:
        dt["class"].append("main_page")
    except KeyError:
      pass

  for dd in soup.find_all("dd"):
    try:
      if "property" in dd["class"]:
        dd["class"].append("main_page")
    except KeyError:
      pass

  for starttd in soup.find_all("p", class_="starttd"):
    starttd.insert_after(BeautifulSoup(
      "".join("".join(map(str, starttd.contents))), "html.parser"))
    starttd.extract()

  for dl in soup.find_all("dl", class_="params"):

    paramname = dl.find("td", class_="paramname")

    if paramname and paramname.text == "m":
      dl.extract()
      continue

    param_html = []

    for tr in dl.find_all("tr"):

      tds = tr.find_all("td")

      param_html.append("""
        <dl class="parameters">
          <dt>{}</dt>
          <dd>{}</dd>
        </dl>
      """.format(tds[0].text, "".join(map(str, tds[1].contents))))

    dl.insert_after(BeautifulSoup("".join(param_html), "html.parser"))
    dl.extract()

  # remove specific span in list

  for table in soup.find_all("table", class_="py_constructor"):
    if table.a.text == "ProRadialDistributionFunction":
      for li in table.find_all("li"):
        try:
          if li.find("span", class_="remove_in_rdf").text:
            li.extract()
        except AttributeError:
          pass

def get_properties_to_be_adde(soup):

  name_alias = {
    "<code>ITEM: ATOMS</code>": "<code>ITEM: ATOMS</code> &mdash in Lammps DUMP file"
  }

  target_table = soup.find("table", class_="properties_list")

  for table in soup.find_all("table", class_="py_constructor"):

    class_name = table.a.text

    if class_name.startswith("Sta") or class_name.startswith("Add"):

      target_table.contents.append(BeautifulSoup("""  <tr>
    <td class="properties_list">{}</td>
    <td class="properties_list" colspan="4">{}</td>
  </tr>
""".format(str(table.a), ", ".join(sorted(list(set(
        name_alias[str(code)] if str(code) in name_alias else str(code)
        for dd in table.find_all("dd", class_="added")
        for code in dd.find_all("code")
      ))))), "html.parser"))

modify_table(mainpage)

get_properties_to_be_adde(mainpage)

mainpage.body.append(BeautifulSoup("""
  <script src="js/mermaid.min.js"></script>
  <script>mermaid.initialize({startOnLoad:true});</script>
""", "html.parser"))

mainpage.head.append(BeautifulSoup("""
  <link href="css/prettify.css" type="text/css" rel="stylesheet">
""", "html.parser"))

mainpage.body.append(BeautifulSoup("""
  <script src="js/prettify.js"></script>
  <script>prettyPrint();</script>
""", "html.parser"))


with open(htmlpath, "wb") as f:
  contents = f.write(mainpage.encode("utf-8"))


htmlpath = "docs/namespacepybind.html"

with open(htmlpath, "r") as f:
  contents = f.read()

pybind = BeautifulSoup(contents, "html.parser")

for table in pybind.find_all("table"):

  modify_table(table)


pybind.head.append(BeautifulSoup("""
  <link href="css/prettify.css" type="text/css" rel="stylesheet">
""", "html.parser"))

pybind.body.append(BeautifulSoup("""
  <script src="js/prettify.js"></script>
  <script>prettyPrint();</script>
""", "html.parser"))


with open(htmlpath, "wb") as f:
  contents = f.write(pybind.encode("utf-8"))
