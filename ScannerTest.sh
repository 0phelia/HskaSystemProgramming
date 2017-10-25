#!/bin/bash

# compile and run SCANNER   
echo "C&R Scanner"

make 2>&1 >/dev/null | grep "error"
cd Scanner
make 2>&1 >/dev/null | grep "error"

./debug/ScannerTest test.txt out.txt
cd ..