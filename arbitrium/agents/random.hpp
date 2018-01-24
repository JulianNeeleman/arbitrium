// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "agent.hpp"

template <class S, class A> class Random : public Agent<S, A> {
  public:
    Random() = default;
    A query(const S &) const override;
};

#endif // RANDOM_HPP
