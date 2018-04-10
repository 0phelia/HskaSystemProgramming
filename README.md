# SysProg2018

## System Recommendations
- OS: If possible, use **Linux, MacOS or Windows 10 with WSL**. Else, use Windows with Cygwin. 
- IDE: If possible, use **Jetbrains CLion 2018.1** (on Windows 10, use the WSL toolchain) or **XCode**
 
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
(vom Projekt-Root-Verzeichnis aus)

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

## Generate Docs
```
doxygen .doxygen.txt
```






=========================================
#### Alte Readme:

Run ./ParserTest.sh

Input file: test/parser5.txt out.txt

Output file: Parser/out.txt


