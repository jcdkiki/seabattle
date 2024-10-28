list(APPEND SEABATTLE_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/ship.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ship_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/human_player.cpp
    ${CMAKE_CURRENT_LIST_DIR}/game.cpp
    ${CMAKE_CURRENT_LIST_DIR}/field.cpp
)

include(${CMAKE_CURRENT_LIST_DIR}/state/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/io/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/abilities/CMakeLists.txt)
