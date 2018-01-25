include_directories(${PROJECT_SOURCE_DIR}/core)

add_library(games
    tic_tac_toe_state.hpp
    tic_tac_toe_state.cpp
    tic_tac_toe_action.hpp
    tic_tac_toe_action.cpp
    connect_four_state.hpp
    connect_four_state.cpp
    connect_four_action.hpp
    connect_four_action.cpp
)
