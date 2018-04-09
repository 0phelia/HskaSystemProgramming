SET(LIB_NAME parser)
SET(SRC
        include/Parser.h
        include/Node.h
        src/Parser.cpp
        src/Node.cpp
        )

add_library(${LIB_NAME} ${SRC})
target_include_directories(${LIB_NAME} PUBLIC include)

install(
        TARGETS ${LIB_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)