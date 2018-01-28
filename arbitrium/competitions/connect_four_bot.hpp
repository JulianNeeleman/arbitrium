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
    std::pair<Bitboard<6, 7>, Bitboard<6, 7>> board {};
    for (unsigned i = 0; i < 42; i++) {
        unsigned row = i / 7, column = i % 7;
        if (cells[i] == "0") {
            board.first.set(5 - row, column, true);
        } else if (cells[i] == "1") {
            board.second.set(5 - row, column, true);
        }
    }
    this->state = ConnectFourState(board, this->your_botid);
}

template <class T> void ConnectFourBot<T>::move(const unsigned clock) {
    ConnectFourAction action = this->agent.query(this->state);
    std::cout << "place_disc " << action.serialize() << std::endl;
}

#endif // CONNECT_FOUR_BOT_HPP
