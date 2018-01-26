// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef STATE_HPP
#define STATE_HPP

#include <vector>

#include "serializable.hpp"

template <class S, class A> class State : public Serializable {
  protected:
    bool turn;

  public:
    explicit State(const bool turn);

    virtual bool operator<(const S &) const = 0;

    virtual std::vector<A> legal_actions() const = 0;
    virtual S transition(const A &) const = 0;

    virtual int winner() const = 0;
    virtual double evaluate() const = 0;

    unsigned current_agent() const;
    unsigned other_agent() const;
};

template <class S, class A> State<S, A>::State(const bool turn) : turn(turn) {}

template <class S, class A> unsigned State<S, A>::current_agent() const {
    return turn + 1;
}

template <class S, class A> unsigned State<S, A>::other_agent() const {
    return turn ? 1 : 2;
}

#endif // STATE_HPP
