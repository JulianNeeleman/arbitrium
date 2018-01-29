// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef CACHE_HPP
#define CACHE_HPP

#include <unordered_map>
#include <vector>

#include "../games/connect_four_hash.hpp"
#include "../games/tic_tac_toe_hash.hpp"
#include "hash.hpp"

template <class S> class Cache {
    std::unordered_map<S, double> memory;

    struct Order {
        const Cache *cache;
        explicit Order(const Cache *cache) : cache(cache) {}
        bool operator()(const S &lhs, const S &rhs) const {
            if (!cache->hit(lhs)) {
                return false;
            }
            if (!cache->hit(rhs)) {
                return true;
            }
            return cache->retrieve(lhs) < cache->retrieve(rhs);
        };
    };

  public:
    void flush();
    void push(const S &state, const double score);
    bool hit(const S &state) const;
    double retrieve(const S &state) const;

    size_t size() const;

    void order(std::vector<S> &states) const;
    bool compare(const S &lhs, const S &rhs) const;
};

template <class S> void Cache<S>::flush() { memory.clear(); }

template <class S> void Cache<S>::push(const S &state, const double score) {
    memory[state] = score;
}

template <class S> bool Cache<S>::hit(const S &state) const {
    return memory.find(state) != memory.end();
}

template <class S> double Cache<S>::retrieve(const S &state) const {
    return memory.at(state);
}

template <class S> size_t Cache<S>::size() const { return memory.size(); }

template <class S> void Cache<S>::order(std::vector<S> &states) const {
    sort(states.begin(), states.end(), Order(this));
}

template <class S> bool Cache<S>::compare(const S &lhs, const S &rhs) const {
    return Order(this)(lhs, rhs);
}

#endif // CACHE_HPP
