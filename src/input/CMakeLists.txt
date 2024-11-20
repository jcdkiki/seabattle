list(APPEND SEABATTLE_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/tui_game_input.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gui_game_input.cpp
)

include(${CMAKE_CURRENT_LIST_DIR}/gui/CMakeLists.txt)
