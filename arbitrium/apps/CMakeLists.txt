include_directories(${PROJECT_SOURCE_DIR}/core ${PROJECT_SOURCE_DIR}/agents)

add_executable(sample main.cpp)
target_link_libraries(sample games)
