// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef NEGAMAX_HPP
#define NEGAMAX_HPP

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#include "../core/agent.hpp"

template <class S, class A> class Negamax : public Agent<S, A> {
    Cache<S> trans_table;
    unsigned max_depth;

    double evaluate_with_cache(const S &state, const unsigned depth,
                               const double alpha, const double beta);
    double evaluate(const S &state, const unsigned depth, const double alpha,
                    const double beta);
    double find_best_action(const S &state, const unsigned depth, double alpha,
                            const double beta);

    std::vector<S> ordered_states(const S &state) const;
    bool sort_by_trans_table(const S &lhs, const S &rhs) const;

  public:
    Negamax();
    explicit Negamax(const unsigned max_depth);
    A query(const S &state, const unsigned clock) override;
};

template <class S, class A> Negamax<S, A>::Negamax() : max_depth(5) {}

template <class S, class A>
Negamax<S, A>::Negamax(const unsigned max_depth) : max_depth(max_depth) {}

template <class S, class A>
double Negamax<S, A>::evaluate_with_cache(const S &state, const unsigned depth,
                                          const double alpha,
                                          const double beta) {
    if (this->hourglass.out_of_time()) {
        return 0.0;
    }
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
    for (const S &neighbor : ordered_states(state)) {
        double score = -evaluate_with_cache(neighbor, depth - 1, -beta, -alpha);
        best = std::max(best, score);
        alpha = std::max(alpha, best);
        if (alpha >= beta) {
            break;
        }
    }
    return best;
}

template <class S, class A>
std::vector<S> Negamax<S, A>::ordered_states(const S &state) const {
    std::vector<S> neighbors;
    for (const A &action : state.legal_actions()) {
        neighbors.push_back(state.transition(action));
    }
    trans_table.order(neighbors);
    return neighbors;
}

template <class S, class A>
A Negamax<S, A>::query(const S &state, const unsigned clock) {
    this->hourglass.set_time(clock / 2);
    double total_best_eval = std::numeric_limits<double>::lowest();
    A total_best_action = state.legal_actions()[0];
    for (unsigned depth = 1; !this->hourglass.out_of_time(); depth++) {
        double best_eval = std::numeric_limits<double>::lowest();
        A best_action = state.legal_actions()[0];
        for (const A &action : state.legal_actions()) {
            S neighbor = state.transition(action);
            double eval = -evaluate_with_cache(
                neighbor, depth, std::numeric_limits<double>::lowest(),
                std::numeric_limits<double>::max());
            if (best_eval < eval) {
                best_eval = eval;
                best_action = action;
            }
        }
        if (total_best_eval < best_eval && !this->hourglass.out_of_time()) {
            total_best_eval = best_eval;
            total_best_action = best_action;
        }
        trans_table = this->cache;
        this->cache.flush();
    }
    this->cache.flush();
    trans_table.flush();
    return total_best_action;
}

#endif // NEGAMAX_HPP
