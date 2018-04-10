project(tests)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/test/")
enable_testing()

find_path(CATCH_INCLUDE_DIR "catch.hpp")
include_directories(${INCLUDE_DIRECTORIES} ${CATCH_INCLUDE_DIR})



file(GLOB SOURCE_FILES "tests/*.cpp")
SET(LIBRARIES parser scanner symboltable automat buffer)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})


include(ParseAndAddCatchTests)
ParseAndAddCatchTests(${PROJECT_NAME})


add_definitions( -DTEST_DIR="${CMAKE_SOURCE_DIR}/test/data/" )

configure_file( testconfig.h.in ${CMAKE_BINARY_DIR}/generated/testconfig.h )
include_directories( ${CMAKE_BINARY_DIR}/generated/ )