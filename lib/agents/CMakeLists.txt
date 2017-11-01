project (agents)

file (GLOB agents_SRC "src/*.cpp")

add_library(agents ${agents_SRC})

target_include_directories(agents PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

