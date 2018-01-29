// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef TIC_TAC_TOE_HASH_HPP
#define TIC_TAC_TOE_HASH_HPP

#include "../core/hash.hpp"
#include "tic_tac_toe_state.hpp"

namespace std {

template <> struct hash<TicTacToeState> {
    std::size_t operator()(const TicTacToeState &key) const noexcept {
        return std::hash<BitboardPair<3, 3>>()(
            static_cast<BitboardPair<3, 3>>(key));
    }
};

} // namespace std

#endif // TIC_TAC_TOE_HASH_HPP
