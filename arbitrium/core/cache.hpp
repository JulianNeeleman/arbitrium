// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef CACHE_HPP
#define CACHE_HPP

#include <map>
#include <vector>

template <class S> class Cache {
    std::map<S, double> memory;

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

    void order(std::vector<S> &states) const;
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

template <class S> void Cache<S>::order(std::vector<S> &states) const {
    sort(states.begin(), states.end(), Order(this));
}

#endif // CACHE_HPP
