//#include "include/lib/minimax.h"
//
///**
// * Assignment constructor.
// */
// Minimax::Minimax(int max_depth) : max_depth_(max_depth) {}
//
///**
// * Implementation of the minimax algorithm.
// */
// double Minimax::minimax(const std::unique_ptr<State> &state, int depth,
//                        bool maximize) const {
//    if (depth == 0 || state->is_terminal()) {
//        return state->evaluate();
//    }
//
//    if (maximize) {
//        double best_score = std::numeric_limits<double>::lowest();
//        for (const std::unique_ptr<Action> &action : state->actions()) {
//            double score = minimax(state->transition(action), depth - 1,
//            false);
//            best_score = std::max(best_score, score);
//        }
//        return best_score;
//    } else {
//        double best_score = std::numeric_limits<double>::max();
//        for (const std::unique_ptr<Action> &action : state->actions()) {
//            double score = minimax(state->transition(action), depth - 1,
//            true);
//            best_score = std::min(best_score, score);
//        }
//        return best_score;
//    }
//}
//
///**
// * Choose the best action from the current state.
// */
// std::unique_ptr<Action>
// Minimax::choose_action(const std::unique_ptr<State> &state) const {
//    std::unique_ptr<Action> best_action;
//    double best_score = std::numeric_limits<double>::lowest();
//
//    for (std::unique_ptr<Action> &action : state->actions()) {
//        double score =
//            minimax(state->transition(action), max_depth_ - 1, false);
//        if (score < best_score) {
//            best_action = std::move(action);
//            best_score = score;
//        }
//    }
//    return std::move(best_action);
//}
