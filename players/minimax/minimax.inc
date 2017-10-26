#include "include/lib/player/minimax.h"

/**
 * Assignment constructor.
 */
template <class State, class Action>
Minimax<State, Action>::Minimax(int max_depth) : max_depth_(max_depth) {}

/**
 * Implementation of the minimax algorithm.
 */
template <class State, class Action>
double Minimax<State, Action>::minimax(const State &state, int depth,
                                       bool maximize) const {
    if (depth == 0 || state.is_terminal()) {
        return state.evaluate();
    }

    if (maximize) {
        double best_score = std::numeric_limits<double>::lowest();
        for (const Action &action : state.actions()) {
            double score = minimax(state.transition(action), depth - 1, false);
            best_score = std::max(best_score, score);
        }
        return best_score;
    } else {
        double best_score = std::numeric_limits<double>::max();
        for (const Action &action : state.actions()) {
            double score = minimax(state.transition(action), depth - 1, true);
            best_score = std::min(best_score, score);
        }
        return best_score;
    }
}

/**
 * Choose the best action from the current state.
 */
template <class State, class Action>
Action Minimax<State, Action>::choose_action(const State &state) const {
    // Generate a list of possible actions.
    std::vector<Action> actions = state.actions();

    Action best_action = *actions.begin();
    double best_score = std::numeric_limits<double>::max();

    int color = state.get_turn() ? -1.0 : 1.0;
    for (const Action &action : actions) {
        double score = color * minimax(state.transition(action), max_depth_ - 1,
                                       !state.get_turn());
        std::cout << "score " << score << std::endl;
        if (score < best_score) {
            best_action = action;
            best_score = score;
        }
    }
    return std::move(best_action);
}