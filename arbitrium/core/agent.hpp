// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef AGENT_HPP
#define AGENT_HPP

#include <iostream>

#include "cache.hpp"

template <class S, class A> class Agent {
  protected:
    Cache<S> cache;

  private:
    virtual double evaluate(const S &state);

  public:
    virtual A query(const S &state) = 0;
};

template <class S, class A> double Agent<S, A>::evaluate(const S &state) {
    return state.evaluate();
}

#endif // AGENT_HPP
