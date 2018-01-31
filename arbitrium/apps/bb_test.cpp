// Copyright 2018 ReSnap b.v. All Rights Reserved.

#include <iostream>
#include <bitset>

#include "../core/bitboard.hpp"

int main() {
    Bitboard<10, 10> board;
    board.set(5, 5, true);
    std::cout << board.four_bit_or_count() << std::endl;
    return 0;
}

