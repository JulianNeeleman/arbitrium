// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef CONNECT_FOUR_BOT_HPP
#define CONNECT_FOUR_BOT_HPP

#include "../games/connect_four_action.hpp"
#include "../games/connect_four_state.hpp"
#include "riddles_bot.hpp"

template <class T>
class ConnectFourBot
    : public RiddlesBot<ConnectFourState, ConnectFourAction, T> {
    unsigned field_columns, field_rows;

    void custom_setting(const std::string &key,
                        const std::string &value) override;
    void update_state(const std::string &value) override;
    void move(const unsigned clock) override;
};

template <class T>
void ConnectFourBot<T>::custom_setting(const std::string &key,
                                       const std::string &value) {
    if (key == "field_columns") {
        field_columns = std::stoi(value);
    } else if (key == "field_rows") {
        field_rows = std::stoi(value);
    }
}

template <class T>
void ConnectFourBot<T>::update_state(const std::string &value) {
    std::vector<std::string> cells = this->split(value, ',');
    std::array<int64_t, 2> board;
    for (unsigned row = 0; row < 6; row++) {
        for (unsigned column = 0; column < 7; column++) {
            switch (cells[7 * row + column][0]) {
            case '0':
                board[0] |= 1ULL << (5 - row + 7 * column);
            case '1':
                board[1] |= 1ULL << (5 - row + 7 * column);
            default:
                break;
            }
        }
    }
    this->state = ConnectFourState(this->your_botid, board);
}

template <class T> void ConnectFourBot<T>::move(const unsigned clock) {
    ConnectFourAction action = this->agent.flush_cache_and_query(this->state);
    std::cout << "place_disc " << action.serialize() << std::endl;
}

#endif // CONNECT_FOUR_BOT_HPP
