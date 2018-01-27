// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef ACTION_HPP
#define ACTION_HPP

#include "serializable.hpp"

template <class A> class Action : public Serializable {
  public:
    explicit Action() = default;
};

#endif // ACTION_HPP
