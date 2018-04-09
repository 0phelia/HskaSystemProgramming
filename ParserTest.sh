#!/bin/bash

# compile and run SCANNER   
echo "C&R Parser"

 if [ "$1" == "" ]
    then
    	echo "recompiling"
        mkdir build && cd build && cmake .. && make 2>&1 >/dev/null | grep "error"
		./test/tests [parser]
		cd ..
    else
    	echo "no recompiling"
        ./build/test/tests [parser]
		cd ..
fi
