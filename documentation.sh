#!/bin/bash

doxygen ~/_github/ppap4lmp/Doxyfile

sed -i \
  -e "s/<!-- fragment -->/\n/g" \
  ~/_github/ppap4lmp/docs/index.html

sed -i \
  -e "/class=\"section author/d" \
  -e "/class=\"section date/d" \
  -e "/class=\"section return/d" \
  -e "/class=\"param/d" \
  -e "s/<h1>/<h1 class=\"main_page_h1\">/g" \
  -e "s/<h2>/<h2 class=\"main_page_h2\">/g" \
  -e "s/class=\"section note\"/class=\"section_note\"/g" \
  -e "s/<td class=\"py_td\"><ul>/<td class=\"py_td\"><ul class=\"py_ul\">/g" \
  ~/_github/ppap4lmp/docs/index.html