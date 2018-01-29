// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef HASH_HPP
#define HASH_HPP

#include "bitboard.hpp"
#include "bitboard_pair.hpp"

namespace std {

template <unsigned R, unsigned C> struct hash<Bitboard<R, C>> {
    std::size_t operator()(const Bitboard<R, C> &key) const noexcept {
        return std::hash<std::bitset<Bitboard<R, C>::L>>()(key.board);
    }
};

template <unsigned R, unsigned C> struct hash<BitboardPair<R, C>> {
    std::size_t operator()(const BitboardPair<R, C> &key) const noexcept {
        std::size_t current = std::hash<Bitboard<R, C>>()(key.board.first),
                    other = std::hash<Bitboard<R, C>>()(key.board.second);
        return current & (other << 1);
    }
};

} // namespace std

#endif // HASH_HPP
