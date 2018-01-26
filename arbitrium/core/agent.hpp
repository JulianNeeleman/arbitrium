// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef AGENT_HPP
#define AGENT_HPP

#include "cache.hpp"

template <class S, class A> class Agent {
    Cache<S> cache;

    virtual double evaluate(const S &state, const unsigned depth) {} // NOLINT

  protected:
    double evaluate_with_cache(const S &state, const unsigned depth);

  public:
    virtual A query(const S &state) = 0;
};

template <class S, class A>
double Agent<S, A>::evaluate_with_cache(const S &state, const unsigned depth) {
    if (!cache.hit(state)) {
        cache.push(state, evaluate(state, depth));
    }
    return cache.retrieve(state);
}

#endif // AGENT_HPP
