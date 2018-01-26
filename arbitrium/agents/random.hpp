// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <vector>
#include <random>

#include "../core/agent.hpp"

template <class S, class A> class Random : public Agent<S, A> {
  public:
    Random() = default;
    A query(const S &)  override;
};

template <class S, class A> A Random<S, A>::query(const S &state) {
    std::vector<A> actions = state.legal_actions();
    return actions[rand() % actions.size()];
}

#endif // RANDOM_HPP
