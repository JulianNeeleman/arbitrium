// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include "action.hpp"

template <class A>
Action<A>::Action(const unsigned next_agent) : next_agent(next_agent) {}
