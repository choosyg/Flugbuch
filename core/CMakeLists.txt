set( SOURCES
    domain/Flight.h
    domain/Flight.cpp
    domain/Location.h
    domain/Location.cpp
    domain/Plane.h
    domain/Plane.cpp

    persistence/AbstractStore.h
    persistence/sqlite/SqLiteStore.h
    persistence/sqlite/SqLiteStore.cpp
)

set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
add_library( core SHARED ${SOURCES} )
target_compile_definitions( core PUBLIC _WIN32_WINNT=0x0501 )
target_link_libraries( core PUBLIC
    Qt5::Core
    Qt5::Positioning
    Qt5::Sql
)
install( TARGETS core RUNTIME DESTINATION . )

add_executable( coreTest
    domain/Flight.test.cpp
    domain/Location.test.cpp
    domain/Plane.test.cpp
    persistence/sqlite/SqLiteStore.test.cpp
)
target_link_libraries( coreTest
    core
    ${GTEST_LIBS}
)
# GTest throws tons of C4996 LNK4099 - Disable it
target_compile_options( coreTest PRIVATE "/wd4996" )
target_link_options( coreTest PRIVATE "/ignore:4099" )
target_compile_definitions( coreTest PRIVATE TEST_DATA="${CMAKE_SOURCE_DIR}/testdata" )
add_test( NAME coreTest COMMAND ${CMAKE_BINARY_DIR}/app/coreTest )

