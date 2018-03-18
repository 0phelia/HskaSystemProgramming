cmake_minimum_required(VERSION 3.5)
project(sysprog)

set(CMAKE_CXX_STANDARD 11)

include_directories(Automat/includes)
include_directories(Buffer)
include_directories(Buffer/includes)
include_directories(Compatibility)
include_directories(Parser/includes)
include_directories(Scanner/includes)
include_directories(Symboltable/includes)

add_executable(sysprog
        Automat/includes/Automat.h
        Automat/includes/Stack.h
        Automat/includes/Syntax.h
        Automat/src/Automat.cpp
        Automat/src/Stack.cpp
        Automat/src/Syntax.cpp
        Automat/src/TestAutomat.cpp
        Buffer/includes/Buffer.h
        Buffer/includes/malloc.h
        Buffer/src/Buffer.cpp
        Buffer/src/TestBuffer.cpp
        Compatibility/compab.h
        Parser/includes/Node.h
        Parser/includes/Parser.h
        Parser/src/Node.cpp
        Parser/src/Parser.cpp
        Parser/src/TestParser.cpp
        Scanner/includes/Information.h
        Scanner/includes/Scanner.h
        Scanner/includes/Token.h
        Scanner/src/Information.cpp
        Scanner/src/Scanner.cpp
        Scanner/src/TestScanner.cpp
        Scanner/src/Token.cpp
        Symboltable/includes/StringTab.h
        Symboltable/includes/Symboltable.h
        Symboltable/includes/SymtabEntry.h
        Symboltable/src/StringTab.cpp
        Symboltable/src/Symboltable.cpp
        Symboltable/src/SymtabEntry.cpp
        Symboltable/src/TestStringTab.cpp
        Symboltable/src/TestSymboltable.cpp
        main.cpp)