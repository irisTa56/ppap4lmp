#!/bin/bash

tar xzvf tests/archive.dumps_bead.tar.gz
tar xzvf tests/archive.dumps_dodecane_10000atm.tar.gz
python tests/test.py