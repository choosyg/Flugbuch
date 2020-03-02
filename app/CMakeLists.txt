add_executable( FlugbuchApp main.cpp ../resources.qrc ../project.rc )
target_link_libraries( FlugbuchApp
    widgets
)
set_target_properties( FlugbuchApp PROPERTIES WIN32_EXECUTABLE YES LINK_FLAGS "/ENTRY:mainCRTStartup" )
install( TARGETS FlugbuchApp RUNTIME DESTINATION . )
