// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef BITBOARD_HPP
#define BITBOARD_HPP

#include <iostream>

#include <array>
#include <bitset>

template <unsigned R, unsigned C> class Bitboard {
    static constexpr unsigned L = (R + 1) * C;
    static constexpr std::array<unsigned, 4> directions{1, R, R + 1, R + 2};

    friend struct std::hash<Bitboard<R, C>>;

    std::bitset<L> board;

  public:
    Bitboard();
    explicit Bitboard(const std::bitset<L> &board);

    bool operator==(const Bitboard &rhs) const;
    Bitboard operator|(const Bitboard &rhs) const;

    unsigned two_consecutive_bits_count() const;
    unsigned three_consecutive_bits_count() const;
    bool three_consecutive_bits() const;
    bool four_consecutive_bits() const;

    bool get(const unsigned row, const unsigned column) const;
    void set(const unsigned row, const unsigned column, const bool value);
};

// Definition needs to be outside class statement.
// https://stackoverflow.com/questions/8016780/undefined-reference-to-static-constexpr-char
template <unsigned R, unsigned C> constexpr unsigned Bitboard<R, C>::L;
template <unsigned R, unsigned C>
constexpr std::array<unsigned, 4> Bitboard<R, C>::directions;

template <unsigned R, unsigned C> Bitboard<R, C>::Bitboard() : board{} {}

template <unsigned R, unsigned C>
Bitboard<R, C>::Bitboard(const std::bitset<L> &board) : board(board) {}

template <unsigned R, unsigned C>
bool Bitboard<R, C>::operator==(const Bitboard<R, C> &rhs) const {
    return board == rhs.board;
}

template <unsigned R, unsigned C>
Bitboard<R, C> Bitboard<R, C>::operator|(const Bitboard<R, C> &rhs) const {
    return Bitboard<R, C>(board | rhs.board);
}

template <unsigned R, unsigned C>
unsigned Bitboard<R, C>::two_consecutive_bits_count() const {
    unsigned result = 0;
    for (unsigned direction : Bitboard<R, C>::directions) {
        std::bitset<L> shifted = board & (board >> direction);
        result += shifted.count();
    }
    return result;
}

template <unsigned R, unsigned C>
unsigned Bitboard<R, C>::three_consecutive_bits_count() const {
    unsigned result = 0;
    for (unsigned direction : Bitboard<R, C>::directions) {
        std::bitset<L> shifted = board & (board >> direction),
                       double_shifted = board & (shifted >> direction);
        result += double_shifted.count();
    }
    return result;
}

template <unsigned R, unsigned C>
bool Bitboard<R, C>::three_consecutive_bits() const {
    return three_consecutive_bits_count() > 0;
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
    return board[row + (R + 1) * column];
}

template <unsigned R, unsigned C>
void Bitboard<R, C>::set(const unsigned row, const unsigned column,
                         const bool value) {
    board.set(row + (R + 1) * column, value);
}

#endif // BITBOARD_HPP
