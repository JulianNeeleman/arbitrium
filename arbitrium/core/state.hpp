// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef STATE_HPP
#define STATE_HPP

#include <vector>

#include "serializable.hpp"

template <class S, class A> class State : public Serializable {
  public:
    virtual bool operator<(const S &) const = 0;

    virtual std::vector<A> legal_actions() const = 0;
    virtual S transition(const A &) const = 0;

    virtual int winner() const = 0;
    virtual double evaluate() const = 0;

    virtual unsigned get_turn() const = 0;
};

#endif // STATE_HPP
