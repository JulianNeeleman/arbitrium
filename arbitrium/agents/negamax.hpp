// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef NEGAMAX_HPP
#define NEGAMAX_HPP

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

#include "../core/agent.hpp"

const double LOW = std::numeric_limits<double>::lowest(),
             HIGH = std::numeric_limits<double>::max();

template <class S, class A> class Negamax : public Agent<S, A> {
    Cache<S> trans_table;

    void maybe_improve(std::pair<A, double> &target,
                       const std::pair<A, double> &source) const;

    std::pair<A, double> iterative_deepening(const S &state,
                                             const unsigned depth);
    double evaluate_with_cache(const S &state, const unsigned depth,
                               const double alpha, const double beta);
    double evaluate(const S &state, const unsigned depth, const double alpha,
                    const double beta);
    double find_best_action(const S &state, const unsigned depth, double alpha,
                            const double beta);

    std::vector<A> ordered_actions(const S &state) const;
    std::vector<S> ordered_states(const S &state) const;
    bool sort_by_trans_table(const S &lhs, const S &rhs) const;

  public:
    Negamax() = default;
    A query(const S &state, const unsigned clock) override;
};

template <class S, class A>
void Negamax<S, A>::maybe_improve(std::pair<A, double> &target,
                                  const std::pair<A, double> &source) const {
    if (target.second < source.second && !this->hourglass.out_of_time()) {
        target = source;
    }
}

template <class S, class A>
std::pair<A, double> Negamax<S, A>::iterative_deepening(const S &state,
                                                        const unsigned depth) {
    std::pair<A, double> best = std::make_pair(state.legal_actions()[0], LOW);
    for (const A &action : ordered_actions(state)) {
        S neighbor = state.transition(action);
        double current = -evaluate_with_cache(neighbor, depth, LOW, HIGH);
        maybe_improve(best, std::make_pair(action, current));
    }
    return best;
}

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
    double best = LOW;
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
std::vector<A> Negamax<S, A>::ordered_actions(const S &state) const {
    std::vector<A> actions = state.legal_actions();
    std::vector<S> neighbors = state.legal_neighbors();

    std::vector<std::size_t> perm(neighbors.size());
    std::iota(perm.begin(), perm.end(), 0);
    std::sort(perm.begin(), perm.end(), [&](std::size_t i, std::size_t j) {
        return trans_table.compare(neighbors.at(i), neighbors.at(j));
    });
    std::vector<A> permuted_actions(actions);
    std::transform(perm.begin(), perm.end(), permuted_actions.begin(),
                   [&](std::size_t i) { return actions.at(i); });
    return permuted_actions;
}

template <class S, class A>
std::vector<S> Negamax<S, A>::ordered_states(const S &state) const {
    std::vector<S> neighbors = state.legal_neighbors();
    trans_table.order(neighbors);
    return neighbors;
}

template <class S, class A>
A Negamax<S, A>::query(const S &state, const unsigned clock) {
    this->hourglass.set_time(std::min(1500U, clock - 50));
    A response = state.legal_actions()[0];
    bool terminal = false;
    for (unsigned depth = 1; !this->hourglass.out_of_time() && !terminal;
         depth++) {
        auto next_iteration = iterative_deepening(state, depth);
        if (std::abs(next_iteration.second) == 10000.0) {
            terminal = true;
        }
        if (!this->hourglass.out_of_time() &&
            next_iteration.second != -10000.0) {
            response = next_iteration.first;
        }
        trans_table = this->cache;
        this->cache.flush();
    }
    trans_table.flush();
    return response;
}

#endif // NEGAMAX_HPP
