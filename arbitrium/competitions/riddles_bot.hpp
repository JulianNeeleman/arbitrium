// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef RIDDLES_BOT_HPP
#define RIDDLES_BOT_HPP

#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

template <class S, class A, class T> class RiddlesBot {
  protected:
    unsigned timebank, time_per_move, your_botid, round;
    std::array<std::string, 2> player_names;
    std::string your_bot;

    S state;
    T agent;

    bool try_base_setting(const std::string &key, const std::string &value);
    virtual void custom_setting(const std::string &key,
                                const std::string &value) = 0;
    void setting(const std::string &key, const std::string &value);

    virtual void update_state(const std::string &value) = 0;
    void update(const std::string &key, const std::string &value);

    virtual void move(unsigned timeout) = 0;

    std::vector<std::string> split(const std::string &line, char delim);

  public:
    RiddlesBot() = default;
    void run();
};

template <class S, class A, class T>
bool RiddlesBot<S, A, T>::try_base_setting(const std::string &key,
                                           const std::string &value) {
    if (key == "timebank") {
        timebank = std::stoi(value);
    } else if (key == "time_per_move") {
        time_per_move = std::stoi(value);
    } else if (key == "player_names") {
        std::vector<std::string> names = split(value, ',');
        player_names[0] = names[0];
        player_names[1] = names[1];
    } else if (key == "your_bot") {
        your_bot = value;
    } else if (key == "your_botid") {
        your_botid = std::stoi(value);
    } else {
        return false;
    }
    return true;
}

template <class S, class A, class T>
void RiddlesBot<S, A, T>::setting(const std::string &key,
                                  const std::string &value) {
    if (!this->try_base_setting(key, value)) {
        custom_setting(key, value);
    }
}

template <class S, class A, class T>
void RiddlesBot<S, A, T>::update(const std::string &key,
                                 const std::string &value) {
    if (key == "round") {
        round = std::stoi(value);
    } else if (key == "field") {
        update_state(value);
    }
}

template <class S, class A, class T>
std::vector<std::string> RiddlesBot<S, A, T>::split(const std::string &line,
                                                    char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

template <class S, class A, class T> void RiddlesBot<S, A, T>::run() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<std::string> command = split(line, ' ');
        if (command[0] == "settings") {
            setting(command[1], command[2]);
        } else if (command[0] == "update" && command[1] == "game") {
            update(command[2], command[3]);
        } else if (command[0] == "action" && command[1] == "move") {
            move(std::stoi(command[2]));
        }
    }
}

#endif // RIDDLES_BOT_HPP
