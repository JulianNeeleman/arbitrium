// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef BITBOARD_PAIR_HPP
#define BITBOARD_PAIR_HPP

#include <array>
#include <string>
#include <tuple>

#include "bitboard.hpp"
#include "serializable.hpp"

template <unsigned R, unsigned C> class BitboardPair : public Serializable {
    friend struct std::hash<BitboardPair<R, C>>;

    std::pair<Bitboard<R, C>, Bitboard<R, C>> board;

  protected:
    bool turn;

  public:
    BitboardPair();
    explicit BitboardPair(
        const std::pair<Bitboard<R, C>, Bitboard<R, C>> &board,
        const bool turn);

    bool operator==(const BitboardPair<R, C> &rhs) const;

    Bitboard<R, C> board_union() const;

    Bitboard<R, C> current_agent_board() const;
    Bitboard<R, C> other_agent_board() const;

    Bitboard<R, C> &current_agent_board();
    Bitboard<R, C> &other_agent_board();

    std::string serialize() const override;
};

template <unsigned R, unsigned C>
BitboardPair<R, C>::BitboardPair() : board{}, turn(false) {}

template <unsigned R, unsigned C>
BitboardPair<R, C>::BitboardPair(
    const std::pair<Bitboard<R, C>, Bitboard<R, C>> &board, const bool turn)
    : board(board), turn(turn) {}

template <unsigned R, unsigned C>
bool BitboardPair<R, C>::operator==(const BitboardPair<R, C> &rhs) const {
    return std::tie(turn, board) == std::tie(rhs.turn, rhs.board);
}

template <unsigned R, unsigned C>
Bitboard<R, C> BitboardPair<R, C>::board_union() const {
    return board.first | board.second;
}

template <unsigned R, unsigned C>
Bitboard<R, C> BitboardPair<R, C>::current_agent_board() const {
    return turn ? board.second : board.first;
}

template <unsigned R, unsigned C>
Bitboard<R, C> BitboardPair<R, C>::other_agent_board() const {
    return turn ? board.first : board.second;
}

template <unsigned R, unsigned C>
Bitboard<R, C> &BitboardPair<R, C>::current_agent_board() {
    return turn ? board.second : board.first;
}

template <unsigned R, unsigned C>
Bitboard<R, C> &BitboardPair<R, C>::other_agent_board() {
    return turn ? board.first : board.second;
}

template <unsigned R, unsigned C>
std::string BitboardPair<R, C>::serialize() const {
    std::string serialization = "";
    for (int row = R - 1; row >= 0; row--) {
        for (unsigned column = 0; column < C; column++) {
            if (board.first.get(row, column)) {
                serialization += "0\t";
            } else if (board.second.get(row, column)) {
                serialization += "1\t";
            } else {
                serialization += ".\t";
            }
        }
        serialization += '\n';
    }
    return serialization;
}

#endif // BITBOARD_PAIR_HPP
