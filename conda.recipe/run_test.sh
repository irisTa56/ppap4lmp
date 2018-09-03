#!/bin/bash

cd tests
tar xzvf archive.dumps_bead.tar.gz
tar xzvf archive.dumps_atom.tar.gz
python test.py