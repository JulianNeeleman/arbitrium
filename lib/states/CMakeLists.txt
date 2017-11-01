project (states)

file (GLOB states_SRC "src/*.cpp")

add_library(states ${states_SRC})

target_include_directories(states PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

