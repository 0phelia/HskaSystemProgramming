SET(LIB_NAME automat)
SET(SRC
        include/Automat.h
        include/Stack.h
        include/Syntax.h
        src/Automat.cpp
        src/Stack.cpp
        src/Syntax.cpp
        )

add_library(${LIB_NAME} ${SRC})
target_include_directories(${LIB_NAME} PUBLIC include)

install(
        TARGETS ${LIB_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)