#!/bin/bash

rm -rf build/
mkdir build
cp cascade.xml build/
cd build
cmake ..
make



