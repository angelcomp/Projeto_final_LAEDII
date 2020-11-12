#!/bin/sh
rm -r build
cmake -B build
cd build
make
exec ./restaurante
