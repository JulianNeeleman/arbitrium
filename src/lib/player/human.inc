#include "include/lib/human.h"

/**
 * Assignment constructor.
 */
template <class State, class Action> Human<State, Action>::Human() {}

/**
 * Choose the best action from the current state.
 */
template <class State, class Action>
Action Human<State, Action>::choose_action(const State &state) const {
    // Ask human for input.
    unsigned choice;
    std::cin >> choice;

    std::vector<Action> actions = state.actions();
    return std::move(actions[choice]);
}
