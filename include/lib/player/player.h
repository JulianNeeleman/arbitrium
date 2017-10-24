#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H

template <class State, class Action> class Player {
  public:
    // Public member functions.
    virtual Action choose_action(const State &) const = 0;
};

#endif // LIB_PLAYER_H
