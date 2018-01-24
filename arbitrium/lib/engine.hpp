// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <memory>

#include "agent.hpp"

template <class S, class A> class Engine {
  private:
    S state;
    const std::vector<std::unique_ptr<Agent<S, A>>> &agents;

    void next_turn();
    void dump_log() const;

  public:
    Engine(const S &, const std::vector<std::unique_ptr<Agent<S, A>>> &);
    void run();
};

#endif // ENGINE_HPP
