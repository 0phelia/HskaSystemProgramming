SET(LIB_NAME scanner)
SET(SRC
        include/Information.h
        include/Scanner.h
        include/Token.h
        src/Information.cpp
        src/Scanner.cpp
        src/Token.cpp
        )

add_library(${LIB_NAME} ${SRC})
target_include_directories(${LIB_NAME} PUBLIC include)

install(
        TARGETS ${LIB_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)