cmake_minimum_required(VERSION 3.16)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

project(seabattle)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include(src/CMakeLists.txt)

function(add_seabattle suffix defines)
    string(APPEND executable_name "seabattle-" ${suffix})
    add_executable(${executable_name} ${SEABATTLE_SOURCES})
    include_directories(${executable_name} src ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
    
    target_compile_definitions(${executable_name} PRIVATE ${defines})
    target_link_libraries(${executable_name} ${SDL2_LIBRARIES} SDL2_ttf.so)
endfunction(add_seabattle)

add_seabattle("tui" "SEABATTLE_TUI_MODE")
add_seabattle("tui-gui" "SEABATTLE_TUI_GUI_MODE")
add_seabattle("gui" "SEABATTLE_GUI_MODE")
