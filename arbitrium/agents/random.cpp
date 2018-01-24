// Copyright 2018 ReSnap b.v. All Rights Reserved.

template <class S, class A> A Random<S, A>::query(const S &state) const {
    std::vector<A> actions = state.legal_actions();
    return actions[rand() % actions.size()];
}

