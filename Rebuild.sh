#!/bin/bash

rm -rf build/
mkdir build
cp cascade.xml build/
cp campo.txt build/
cd build
cmake ..
make



