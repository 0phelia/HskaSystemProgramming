#!/bin/bash

# compile and run SCANNER   
echo "C&R Parser"

make 2>&1 >/dev/null | grep "error"
cd Parser
make 2>&1 >/dev/null | grep "error"

./debug/ParserTest ../test/parser3.txt out.txt
cd ..