set( UIS
    FlightDialog.ui
    LocationDialog.ui
    PlaneDialog.ui
    MainWindow.ui
    map.qml
)
set_source_files_properties(${UIS} PROPERTIES HEADER_FILE_ONLY TRUE)

set( SOURCES
  FlightDialog.h
  FlightDialog.cpp
  FlightListModel.h
  FlightListModel.cpp
  LocationDialog.h
  LocationDialog.cpp
  LocationListModel.h
  LocationListModel.cpp
  PlaneDialog.h
  PlaneDialog.cpp
  PlaneListModel.h
  PlaneListModel.cpp
  MainWindow.h
  MainWindow.cpp
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library( widgets SHARED ${SOURCES} ${UIS} )
target_compile_definitions( widgets PUBLIC _WIN32_WINNT=0x0501 )
target_link_libraries( widgets PUBLIC
    core
    Qt5::Widgets
    Qt5::Gui
    Qt5::QuickWidgets
)
install(TARGETS widgets RUNTIME DESTINATION .)
install( FILES map.qml DESTINATION . )
file( COPY map.qml DESTINATION ${PROJECT_BINARY_DIR} )

#add_executable( widgetsTest
#)
#target_link_libraries( widgetsTest
#    widgets
#    ${GTEST_LIBS}
#)
# GTest throws tons of C4996 LNK4099 - Disable it
#target_compile_options( widgetsTest PRIVATE "/wd4996" )
#target_link_options( widgetsTest PRIVATE "/ignore:4099" )
#target_compile_definitions( widgetsTest PRIVATE TEST_DATA="${CMAKE_SOURCE_DIR}/testdata" )
#add_test( NAME widgetsTest COMMAND ${CMAKE_BINARY_DIR}/app/widgetsTest )

