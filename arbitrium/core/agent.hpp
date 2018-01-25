// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef AGENT_HPP
#define AGENT_HPP

template <class S, class A> class Agent {
  public:
    virtual A query(const S &) const = 0;
};

#endif // AGENT_HPP
