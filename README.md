# SysProg2018

## Code Style

Consider the following Best Practices when contributing:
https://github.com/lefticus/cppbestpractices/blob/master/03-Style.md


## Build
```
mkdir build && cd build && cmake ..
make
```

## Test
```
cd build/test/
./tests [automat]
./tests [buffer]
./tests [parser]
./tests [scanner]
./tests [stringtab]
./tests [symboltable]
```

oder alle mit einem Befehl: 
```
cd build/test/
./tests *
```

## Generate Doxygen
```
doxygen .doxygen.txt
```

#### Alt

Run ./ParserTest.sh

Input file: test/parser5.txt out.txt

Output file: Parser/out.txt


