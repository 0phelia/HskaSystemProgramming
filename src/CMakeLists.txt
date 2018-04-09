SET(SRC main.cpp)
add_executable(main ${SRC})
target_link_libraries(main buffer automat parser scanner symboltable)