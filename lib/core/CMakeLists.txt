project (core)

file (GLOB core_SRC "src/*.hpp")

add_library(core INTERFACE)
target_sources(core INTERFACE ${core_SRC})

target_include_directories(core INTERFACE
    "${PROJECT_SOURCE_DIR}/src"
)


