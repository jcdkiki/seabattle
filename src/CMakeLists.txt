file(GLOB SRCFILES "*.cpp")
target_sources(seabattle PRIVATE ${SRCFILES})

add_subdirectory(states)
