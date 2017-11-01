#include "../../../include/agents/human/human.h"

/**
 * Choose the best action from the current state.
 */
template <class State, class Action>
Action Human<State, Action>::choose_action(const State &state) {
    std::vector<Action> actions = state.actions();

    unsigned choice;
    std::cin >> choice;

    return std::move(actions[choice]);
}
