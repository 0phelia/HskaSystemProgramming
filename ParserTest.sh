#!/bin/bash

# compile and run SCANNER   
echo "C&R Parser"

 if [ "$1" == "" ]
    then
    	echo "recompiling"
        make 2>&1 >/dev/null | grep "error"
		cd Parser
		make 2>&1 >/dev/null | grep "error"
		./debug/ParserTest ../test/parser5.txt out.txt
		cd ..
    else
    	echo "no recompiling"
        ./debug/ParserTest ../test/parser5.txt out.txt
		cd ..
fi

#make 2>&1 >/dev/null | grep "error"
#cd Parser
#make 2>&1 >/dev/null | grep "error"
#
#./debug/ParserTest ../test/parser3.txt out.txt
#cd ..