#include "lib/include/cache.h"

template <class State> void Cache<State>::flush() { memory_.clear(); }

template <class State>
void Cache<State>::add_to_cache(const State &state, double score) {
    memory_[state] = score;
}

template <class State>
std::pair<bool, double>
Cache<State>::retrieve_from_cache(const State &state) const {
    auto it = memory_.find(state);
    if (it != memory_.end()) {
        return {true, it->second};
    }
    return {false, 0.0};
}
