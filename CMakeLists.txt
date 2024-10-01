cmake_minimum_required(VERSION 3.25)
project(seabattle)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_executable(seabattle)
include_directories(seabattle src)
add_subdirectory(src)

target_link_libraries(seabattle sfml-graphics sfml-window sfml-system OpenGL::GL)
