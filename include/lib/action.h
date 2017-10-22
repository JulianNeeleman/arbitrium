#ifndef LIB_ACTION_H
#define LIB_ACTION_H

#include <string>

class Action {
  protected:
    // Private member variables.
    int player_;

    // Private member functions.

  public:
    // Constructors.
    Action(unsigned);

    // Public member functions.
    virtual std::string serialize() const = 0;

    // Setters.

    // Getters.
    int get_player() const;
};

#endif // LIB_ACTION_H
