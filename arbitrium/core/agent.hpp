// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef AGENT_HPP
#define AGENT_HPP

#include <iostream>

#include "cache.hpp"

template <class S, class A> class Agent {
    Cache<S> cache;

    virtual double evaluate(const S &state);
    virtual A query(const S &state) = 0;

  protected:
    double evaluate_with_cache(const S &state);

  public:
    A flush_cache_and_query(const S &state);
};

template <class S, class A>
double Agent<S, A>::evaluate(const S &state) {
    return state.evaluate();
}

template <class S, class A>
double Agent<S, A>::evaluate_with_cache(const S &state) {
    if (!cache.hit(state)) {
        cache.push(state, evaluate(state));
    }
    return cache.retrieve(state);
}

template <class S, class A>
A Agent<S, A>::flush_cache_and_query(const S &state) {
    cache.flush();
    return query(state);
}

#endif // AGENT_HPP
