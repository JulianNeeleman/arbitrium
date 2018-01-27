// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef BITBOARD_HPP
#define BITBOARD_HPP

#include <array>
#include <bitset>

template <unsigned R, unsigned C> class Bitboard {
    static constexpr unsigned L = std::max(R, C) * std::max(R, C);
    static constexpr std::array<unsigned, 4> directions{1, C, C - 1, C + 1};

    std::bitset<L> board;

  public:
    Bitboard();
    explicit Bitboard(const std::bitset<L> &board);
    explicit Bitboard(const std::array<std::array<bool, C>, R> &matrix);

    bool operator<(const Bitboard &rhs) const;
    Bitboard operator|(const Bitboard &rhs) const;

    bool three_consecutive_bits() const;
    bool four_consecutive_bits() const;

    bool get(const unsigned row, const unsigned column) const;
    void set(const unsigned row, const unsigned column, const bool value);
};

// Definition needs to be outside class statement.
// https://stackoverflow.com/questions/8016780/undefined-reference-to-static-constexpr-char
template <unsigned R, unsigned C>
constexpr std::array<unsigned, 4> Bitboard<R, C>::directions;

template <unsigned R, unsigned C> Bitboard<R, C>::Bitboard() : board{} {}

template <unsigned R, unsigned C>
Bitboard<R, C>::Bitboard(const std::bitset<L> &board) : board(board) {}

template <unsigned R, unsigned C>
Bitboard<R, C>::Bitboard(const std::array<std::array<bool, C>, R> &matrix) {
    for (unsigned row = 0; row < R; row++) {
        for (unsigned column = 0; column < C; column++) {
            set(row, column, matrix.at(row).at(column));
        }
    }
}

template <unsigned R, unsigned C>
bool Bitboard<R, C>::operator<(const Bitboard<R, C> &rhs) const {
    return true;
}

template <unsigned R, unsigned C>
Bitboard<R, C> Bitboard<R, C>::operator|(const Bitboard<R, C> &rhs) const {
    return Bitboard<R, C>(board | rhs.board);
}

template <unsigned R, unsigned C>
bool Bitboard<R, C>::three_consecutive_bits() const {
    for (unsigned direction : Bitboard<R, C>::directions) {
        std::bitset<L> shifted = board & (board >> direction);
        if ((shifted & (shifted >> (2 * direction))) != 0) {
            return true;
        }
    }
    return false;
}

template <unsigned R, unsigned C>
bool Bitboard<R, C>::four_consecutive_bits() const {
    for (unsigned direction : Bitboard<R, C>::directions) {
        std::bitset<L> shifted = board & (board >> direction);
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
