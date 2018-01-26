// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef NEGAMAX_HPP
#define NEGAMAX_HPP

#include <iostream>
#include <limits>
#include <vector>

#include "../core/agent.hpp"

template <class S, class A> class Negamax : public Agent<S, A> {
    unsigned max_depth;

    double negamax(const S &state, const unsigned depth) const;

  public:
    Negamax();
    explicit Negamax(const unsigned max_depth);
    A query(const S &state) const override;
};

template <class S, class A> Negamax<S, A>::Negamax() : max_depth(6) {}

template <class S, class A>
Negamax<S, A>::Negamax(const unsigned max_depth) : max_depth(max_depth) {}

template <class S, class A>
double Negamax<S, A>::negamax(const S &state, const unsigned depth) const {
    if (depth == 0 || state.winner() != -1) {
        return state.evaluate();
    }
    double best = std::numeric_limits<double>::lowest();
    for (const A &action : state.legal_actions()) {
        S neighbor = state.transition(action);
        best = std::max(best, -negamax(neighbor, depth - 1));
    }
    return best;
}

template <class S, class A> A Negamax<S, A>::query(const S &state) const {
    double best_eval = std::numeric_limits<double>::lowest();
    A best_action = state.legal_actions()[0];
    for (const A &action : state.legal_actions()) {
        S neighbor = state.transition(action);
        double eval = -negamax(neighbor, max_depth);
        if (best_eval < eval) {
            best_eval = eval;
            best_action = action;
        }
    }
    return best_action;
}

#endif // NEGAMAX_HPP
