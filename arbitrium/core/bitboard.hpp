// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef BITBOARD_HPP
#define BITBOARD_HPP

#include <array>
#include <bitset>

template <unsigned R, unsigned C> class Bitboard {
    const std::array<unsigned, 4> directions;
    std::bitset<(R + 1) * C> board;

  public:
    explicit Bitboard(const std::array<std::array<bool, C>, R> &matrix);

    bool four_consecutive_bits() const;

    bool get(const unsigned row, const unsigned column) const;
    void set(const unsigned row, const unsigned column, const bool value);
};

template <unsigned R, unsigned C>
Bitboard<R, C>::Bitboard(const std::array<std::array<bool, C>, R> &matrix)
    : directions{1, C, C - 1, C + 1} {
    for (unsigned row = 0; row < R; row++) {
        for (unsigned column = 0; column < C; column++) {
            set(row, column, matrix.at(row).at(column));
        }
    }
}

template <unsigned R, unsigned C>
bool Bitboard<R, C>::four_consecutive_bits() const {
    for (unsigned direction : directions) {
        int64_t shifted = board & (board >> direction);
        if ((shifted & (shifted >> (2 * direction))) != 0) {
            return true;
        }
    }
    return false;
}

template <unsigned R, unsigned C>
bool Bitboard<R, C>::get(const unsigned row, const unsigned column) const {
    return board[row + R * column];
}

template <unsigned R, unsigned C>
void Bitboard<R, C>::set(const unsigned row, const unsigned column,
                         const bool value) {
    board.set(row + R * column, value);
}

#endif // BITBOARD_HPP
