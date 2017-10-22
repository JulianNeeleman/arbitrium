#ifndef LIB_ACTION_H
#define LIB_ACTION_H

class Action {
  protected:
    // Private member variables.
    int player_;

    // Private member functions.

  public:
    // Constructors.
    Action(unsigned);
    // Public member functions.

    // Setters.

    // Getters.
    int get_player() const;
};

#endif // LIB_ACTION_H
