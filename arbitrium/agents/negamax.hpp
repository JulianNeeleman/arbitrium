// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef NEGAMAX_HPP
#define NEGAMAX_HPP

#include <limits>
#include <vector>

#include "../core/agent.hpp"

template <class S, class A> class Negamax : public Agent<S, A> {
    unsigned max_depth;

    double evaluate_with_cache(const S &state, const unsigned depth,
                               const double alpha, const double beta);
    double evaluate(const S &state, const unsigned depth, const double alpha,
                    const double beta);
    double find_best_action(const S &state, const unsigned depth, double alpha,
                            const double beta);

  public:
    Negamax();
    explicit Negamax(const unsigned max_depth);
    A query(const S &state) override;
};

template <class S, class A> Negamax<S, A>::Negamax() : max_depth(5) {}

template <class S, class A>
Negamax<S, A>::Negamax(const unsigned max_depth) : max_depth(max_depth) {}

template <class S, class A>
double Negamax<S, A>::evaluate_with_cache(const S &state, const unsigned depth,
                                          const double alpha,
                                          const double beta) {
    if (!this->cache.hit(state)) {
        this->cache.push(state, evaluate(state, depth, alpha, beta));
    }
    return this->cache.retrieve(state);
}

template <class S, class A>
double Negamax<S, A>::evaluate(const S &state, const unsigned depth,
                               const double alpha, const double beta) {
    if (depth == 0 || state.winner() != -2) {
        return state.evaluate();
    }
    return find_best_action(state, depth, alpha, beta);
}

template <class S, class A>
double Negamax<S, A>::find_best_action(const S &state, const unsigned depth,
                                       double alpha, const double beta) {
    double best = std::numeric_limits<double>::lowest();
    for (const A &action : state.legal_actions()) {
        S neighbor = state.transition(action);
        best = std::max(
            best, -evaluate_with_cache(neighbor, depth - 1, -beta, -alpha));
        alpha = std::max(alpha, best);
        if (alpha >= beta) {
            break;
        }
    }
    return best;
}

template <class S, class A> A Negamax<S, A>::query(const S &state) {
    double best_eval = std::numeric_limits<double>::lowest();
    A best_action = state.legal_actions()[0];
    for (const A &action : state.legal_actions()) {
        S neighbor = state.transition(action);
        double eval = -evaluate_with_cache(
            neighbor, max_depth, std::numeric_limits<double>::lowest(),
            std::numeric_limits<double>::max());
        if (best_eval < eval) {
            best_eval = eval;
            best_action = action;
        }
    }
    this->cache.flush();
    return best_action;
}

#endif // NEGAMAX_HPP
