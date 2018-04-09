project(tests)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/test/")
enable_testing()

find_path(CATCH_INCLUDE_DIR "catch.hpp")
include_directories(${INCLUDE_DIRECTORIES} ${CATCH_INCLUDE_DIR})



file(GLOB SOURCE_FILES "*.cpp")
SET(LIBRARIES parser scanner symboltable automat buffer)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})


include(ParseAndAddCatchTests)
ParseAndAddCatchTests(${PROJECT_NAME})


add_definitions( -DTEST_ROOT_DIR="${CMAKE_SOURCE_DIR}/test" )