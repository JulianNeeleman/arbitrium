project (actions)

file (GLOB actions_SRC "src/*.cpp")

add_library(actions ${actions_SRC})

target_include_directories(actions PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

