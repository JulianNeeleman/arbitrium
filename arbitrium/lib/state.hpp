// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef STATE_HPP
#define STATE_HPP

#include <vector>

#include "serializable.hpp"

template <class S, class A> class State : public Serializable {
  protected:
    bool turn;

  public:
    State() = default;
    virtual bool operator<(const S &) const = 0;

    virtual std::vector<A> legal_actions() const = 0;
    virtual S transition(const A &) const = 0;

    virtual int winner() const = 0;
    virtual double evaluate() const = 0;

    unsigned current_agent() const;
    unsigned other_agent() const;
};

#endif // STATE_HPP
