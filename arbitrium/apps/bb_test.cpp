// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include <iostream>
#include <bitset>

#include "../core/bitboard.hpp"

int main() {
    Bitboard<3, 2> board;
    board.set(0, 0, true);
    board.set(1, 0, true);
    board.set(2, 0, true);
    std::cout << board.two_consecutive_bits_count() << std::endl;
    std::cout << board.three_consecutive_bits_count() << std::endl;
    return 0;
}

