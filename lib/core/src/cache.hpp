#ifndef CORE_CACHE_H
#define CORE_CACHE_H

#include <map>

template <class State> class Cache {
  private:
    // Private member variables.
    std::map<State, double> memory_;

  public:
    // Public member functions.
    void flush() { memory_.clear(); }

    void add_to_cache(const State &state, double score) {
        memory_[state] = score;
    }

    std::pair<bool, double> retrieve_from_cache(const State &state) const {
        auto it = memory_.find(state);
        if (it != memory_.end()) {
            return {true, it->second};
        }
        return {false, 0.0};
    }
};

#endif // CORE_CACHE_H
