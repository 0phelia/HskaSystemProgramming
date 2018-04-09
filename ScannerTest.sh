#!/bin/bash

# compile and run SCANNER   
echo "C&R Scanner"


mkdir build && cd build && cmake .. 2>&1 >/dev/null | grep "error"
./test/tests [scanner]
cd ..