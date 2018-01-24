#include "state.hpp"

template <class S, class A> unsigned State<S, A>::current_agent() const {
    return turn + 1;
}

template <class S, class A> unsigned State<S, A>::other_agent() const {
    return turn ? 1 : 2;
}
