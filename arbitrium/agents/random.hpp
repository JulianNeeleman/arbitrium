// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <vector>

#include "../core/agent.hpp"

template <class S, class A> class Random : public Agent<S, A> {
  public:
    Random() = default;
    A query(const S &state, const unsigned clock) override;
};

template <class S, class A>
A Random<S, A>::query(const S &state, const unsigned clock) {
    std::vector<A> actions = state.legal_actions();
    return actions[rand() % actions.size()];
}

#endif // RANDOM_HPP
