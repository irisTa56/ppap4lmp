#!/bin/bash

doxygen ~/_github/ppap4lmp/Doxyfile

sed -i \
  -e "s/<!-- fragment -->/\n/g" \
  ~/_github/ppap4lmp/docs/index.html

sed -i \
  -e "/section author/d" \
  -e "/section date/d" \
  -e "s/<h1>/<h1 class=\"main_page_h1\">/g" \
  -e "s/<h2>/<h2 class=\"main_page_h2\">/g" \
  ~/_github/ppap4lmp/docs/index.html