add_executable(${PROJECT_NAME})
# @NOTE: add more source files here
target_sources(${PROJECT_NAME} PRIVATE raylib_game.cpp
	Extension.cpp
	SwitchingPanel.cpp
	Switchboard.cpp
	ControlPanel.cpp
	CordSegment.cpp
	CordCircuit.cpp
	CircuitSwitch.cpp
	PhoneJack.cpp
	Machine.cpp
	TalkBox.cpp
	view_specs/IndicatorLightView.cpp
	view_specs/NumberPlateView.cpp
	view_specs/PhonePortView.cpp
	view_specs/PhoneJackView.cpp
	view_specs/CordSegmentView.cpp
	view_specs/CircuitSwitchView.cpp
	view_specs/BoxView.cpp
	view_specs/ExtensionView.cpp
	view_specs/CordCircuitView.cpp
	view_specs/SwitchingPanelView.cpp
	view_specs/SwitchboardView.cpp
	view_specs/ControlPanelView.cpp
	view_specs/MachineView.cpp
	view_specs/TalkBoxView.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_link_libraries(${PROJECT_NAME} raylib)
if(NOT WIN32)
    target_link_libraries(${PROJECT_NAME} m)
endif()

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html") # Tell Emscripten to build an example.html file.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s FORCE_FILESYSTEM=1 -s WASM=1")

    set(web_link_flags)
    if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
        set(web_link_flags "${web_link_flags} -s ASSERTIONS=1")
    endif()
    set(web_link_flags "${web_link_flags} --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/resources@resources --use-preload-plugins")
    set(web_link_flags "${web_link_flags} --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/minshell.html")

    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "${web_link_flags}")
endif()

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# misc
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
# set the startup project for the "play" button in MSVC
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
