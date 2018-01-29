// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef CONNECT_FOUR_HASH_HPP
#define CONNECT_FOUR_HASH_HPP

#include "../core/hash.hpp"
#include "connect_four_state.hpp"

namespace std {

template <> struct hash<ConnectFourState> {
    std::size_t operator()(const ConnectFourState &key) const noexcept {
        return std::hash<BitboardPair<6, 7>>()(
            static_cast<BitboardPair<6, 7>>(key));
    }
};

} // namespace std

#endif // CONNECT_FOUR_HASH_HPP
