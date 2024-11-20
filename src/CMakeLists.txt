list(APPEND SEABATTLE_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/ship.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ship_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ai_controller.cpp
    ${CMAKE_CURRENT_LIST_DIR}/player.cpp
    ${CMAKE_CURRENT_LIST_DIR}/game.cpp
    ${CMAKE_CURRENT_LIST_DIR}/field.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ability_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ability_registry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/state_registry.cpp
)

include(${CMAKE_CURRENT_LIST_DIR}/input/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/renderer/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/abilities/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/states/CMakeLists.txt)
