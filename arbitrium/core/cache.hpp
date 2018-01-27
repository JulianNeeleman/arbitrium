// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef CACHE_HPP
#define CACHE_HPP

#include <map>
#include <iostream>

template <class S> class Cache {
    std::map<S, double> memory;

  public:
    void flush();
    void push(const S &state, const double score);
    bool hit(const S &state) const;
    double retrieve(const S &state) const;
};

template <class S> void Cache<S>::flush() {
    std::cout << "flushing cache with " << memory.size() << " elements"
              << std::endl;
    memory.clear();
}

template <class S> void Cache<S>::push(const S &state, const double score) {
    memory[state] = score;
}

template <class S> bool Cache<S>::hit(const S &state) const {
    return memory.find(state) != memory.end();
}
template <class S> double Cache<S>::retrieve(const S &state) const {
    return memory.at(state);
}

#endif // CACHE_HPP
