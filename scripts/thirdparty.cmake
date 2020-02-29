
#############################################################
# QT
#############################################################
set( CMAKE_PREFIX_PATH "C:/Qt/Qt5.14.1/5.14.1/msvc2017_64" )
find_package(Qt5Core REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS})
find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
find_package(Qt5Sql REQUIRED)
include_directories(${Qt5Sql_INCLUDE_DIRS})
find_package(Qt5Svg REQUIRED)
include_directories(${Qt5Svg_INCLUDE_DIRS})
find_package(Qt5Positioning REQUIRED)
include_directories(${Qt5Positioning_INCLUDE_DIRS})
find_package(Qt5Qml REQUIRED)
include_directories(${Qt5Qml_INCLUDE_DIRS})
find_package(Qt5Quick REQUIRED)
include_directories(${Qt5Quick_INCLUDE_DIRS})
find_package(Qt5QuickWidgets REQUIRED)
include_directories(${Qt5QuickWidgets_INCLUDE_DIRS})

get_filename_component(QT_DIR ${QT_QMAKE_EXECUTABLE} DIRECTORY)
set( QT_INSTALL_DLLS
    ${QT_DIR}/Qt5Core.dll
    ${QT_DIR}/Qt5Gui.dll
    ${QT_DIR}/Qt5Network.dll
    ${QT_DIR}/Qt5Positioning.dll
    ${QT_DIR}/Qt5Qml.dll
    ${QT_DIR}/Qt5QmlModels.dll
    ${QT_DIR}/Qt5Quick.dll
    ${QT_DIR}/Qt5Quickwidgets.dll
    ${QT_DIR}/Qt5Sql.dll
    ${QT_DIR}/Qt5Svg.dll
    ${QT_DIR}/Qt5Widgets.dll
)
install( FILES ${QT_INSTALL_DLLS} DESTINATION . )
file( COPY ${QT_INSTALL_DLLS} DESTINATION ${PROJECT_BINARY_DIR} )

file( COPY ${QT_DIR}/../qml/QtLocation DESTINATION ${PROJECT_BINARY_DIR}/qml )
file( COPY ${QT_DIR}/../qml/QtPositioning DESTINATION ${PROJECT_BINARY_DIR}/qml )
file( COPY ${QT_DIR}/../qml/QtQuick.2 DESTINATION ${PROJECT_BINARY_DIR}/qml )

file( COPY ${QT_DIR}/../plugins/geoservices DESTINATION ${PROJECT_BINARY_DIR} )
file( COPY ${QT_DIR}/../plugins/imageformats DESTINATION ${PROJECT_BINARY_DIR} )
file( COPY ${QT_DIR}/../plugins/platforms DESTINATION ${PROJECT_BINARY_DIR} )
file( COPY ${QT_DIR}/../plugins/sqldrivers DESTINATION ${PROJECT_BINARY_DIR} )

install( FILES ${QT_DIR}/../plugins/platforms/qwindows.dll DESTINATION ./platforms )

file( COPY ${QT_DIR}/Qt5Cored.dll DESTINATION ${PROJECT_BINARY_DIR} )
file( COPY ${QT_DIR}/Qt5Widgetsd.dll DESTINATION ${PROJECT_BINARY_DIR} )
file( COPY ${QT_DIR}/Qt5Guid.dll DESTINATION ${PROJECT_BINARY_DIR} )
file( COPY ${QT_DIR}/Qt5Sqld.dll DESTINATION ${PROJECT_BINARY_DIR} )
file( COPY ${QT_DIR}/Qt5Svgd.dll DESTINATION ${PROJECT_BINARY_DIR} )
file( COPY ${QT_DIR}/Qt5Positioning.dll DESTINATION ${PROJECT_BINARY_DIR} )

#############################################################
# GTest
#############################################################
set( GTEST_DIR "${PROJECT_SOURCE_DIR}/../Resources/3rd-party-windows-x86_64/gtest-vc141-1.7.0" )
include_directories( ${GTEST_DIR}/include )
link_directories( "${GTEST_DIR}/lib" )
set( GTEST_LIBS
    optimized gtest
    debug gtestD
    optimized gtest_main
    debug gtest_mainD
    )
