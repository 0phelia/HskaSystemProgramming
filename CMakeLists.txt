cmake_minimum_required(VERSION 3.5)
MESSAGE(STATUS "Running cmake version ${CMAKE_VERSION}")

project(Sysprog VERSION 0.1.0 LANGUAGES CXX)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic")

#SET(LIB_SRC
#        lib/Buffer/Buffer.cpp
#        lib/scanner/scanner.cpp
#        lib/state-machine/state-machine.cpp
#        lib/symboltable/symboltable.cpp)


# -DWITH_TESTS=ON -DWITH_VALGRIND=ON -DWITH_COVERALLS=ON
OPTION(WITH_TESTS OFF)
OPTION(WITH_VALGRIND OFF)
OPTION(WITH_COVERALLS "Turn on coveralls support" OFF)
OPTION(COVERALLS_UPLOAD "Upload the generated coveralls json" ON)


IF (WITH_TESTS)
    MESSAGE(STATUS "Tests active")
    #    ENABLE_TESTING()
ENDIF ()
IF (WITH_VALGRIND)
    MESSAGE(STATUS "Valgrind analysis active")
ENDIF ()


# Will set GIT_EXECUTABLE and GIT_FOUND
#FIND_PACKAGE(Git)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

INCLUDE_DIRECTORIES(include)
ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)


## Setup the coveralls target and tell it to gather
## coverage data for all the lib sources.
#if (WITH_COVERALLS)
#    coveralls_setup(
#            "${LIB_SRC}"
#            ${COVERALLS_UPLOAD}
#            "${PROJECT_SOURCE_DIR}/coveralls-cmake/cmake")
#endif()


MESSAGE(STATUS "CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
GET_PROPERTY(cwd_definitions DIRECTORY PROPERTY COMPILE_DEFINITIONS)
MESSAGE(STATUS "COMPILE_DEFINITIONS: ${cwd_definitions}")
MESSAGE(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
MESSAGE(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
MESSAGE(STATUS "CMAKE_C_LINK_FLAGS: ${CMAKE_C_LINK_FLAGS}")
MESSAGE(STATUS "CMAKE_CXX_LINK_FLAGS: ${CMAKE_CXX_LINK_FLAGS}")