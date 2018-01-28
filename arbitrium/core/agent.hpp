// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef AGENT_HPP
#define AGENT_HPP

#include "hourglass.hpp"
#include "cache.hpp"

template <class S, class A> class Agent {
  protected:
    Cache<S> cache;
    Hourglass hourglass;

  private:
    virtual double evaluate(const S &state);

  public:
    virtual A query(const S &state, const unsigned) = 0;
};

template <class S, class A> double Agent<S, A>::evaluate(const S &state) {
    return state.evaluate();
}

#endif // AGENT_HPP
