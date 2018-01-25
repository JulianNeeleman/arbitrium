include_directories(${PROJECT_SOURCE_DIR}/core)

add_library(games
    tic_tac_toe_state.hpp
    tic_tac_toe_state.cpp
    tic_tac_toe_action.hpp
    tic_tac_toe_action.cpp
)
