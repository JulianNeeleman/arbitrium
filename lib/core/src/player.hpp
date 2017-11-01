#ifndef PLAYER_H
#define PLAYER_H

template <class State, class Action> class Player {
  public:
    // Public member functions.
    virtual Action choose_action(const State &) = 0;
};

#endif // PLAYER_H
