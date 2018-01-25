include_directories(${PROJECT_SOURCE_DIR}/core ${PROJECT_SOURCE_DIR}/agents)

add_executable(tic_tac_toe tic_tac_toe.cpp)
target_link_libraries(tic_tac_toe games)

add_executable(connect_four connect_four.cpp)
target_link_libraries(connect_four games)
