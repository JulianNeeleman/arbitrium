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
    virtual double evaluate() const;

    virtual unsigned get_turn() const = 0;
};

template <class S, class A> double State<S, A>::evaluate() const {
    int result = winner();
    if (result < 0) {
        return 0.0;
    }
    return result == get_turn() ? 1.0 : -1.0;
}

#endif // STATE_HPP
