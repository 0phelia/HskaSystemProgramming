SET(LIB_NAME buffer)
SET(SRC
        include/Buffer.h
        src/Buffer.cpp
        )

add_library(${LIB_NAME} ${SRC})
target_include_directories(${LIB_NAME} PUBLIC include)

install(
        TARGETS ${LIB_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)