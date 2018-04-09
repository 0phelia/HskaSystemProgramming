SET(LIB_NAME symboltable)
SET(SRC
        include/StringTab.h
        include/Symboltable.h
        include/SymtabEntry.h
        src/StringTab.cpp
        src/Symboltable.cpp
        src/SymtabEntry.cpp
        )

add_library(${LIB_NAME} ${SRC})
target_include_directories(${LIB_NAME} PUBLIC include)

install(
        TARGETS ${LIB_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)