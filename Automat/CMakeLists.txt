cmake_minimum_required(VERSION 3.5)
project(sysprog_automat)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})


add_library(automat_lib SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Automat.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Stack.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Syntax.cpp)
target_include_directories(automat_lib PRIVATE includes)


set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/TestAutomat.cpp)
add_executable(automat_test ${TEST_SOURCES})
target_link_libraries(automat_test automat_lib Catch)
