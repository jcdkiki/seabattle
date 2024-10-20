cmake_minimum_required(VERSION 3.25)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

project(seabattle)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(seabattle)
include_directories(seabattle src ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
add_subdirectory(src)

target_link_libraries(seabattle ${SDL2_LIBRARIES} SDL2_ttf.so)
