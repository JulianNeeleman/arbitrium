#ifndef TRON_ACTION_H
#define TRON_ACTION_H

#include <string>

class TronAction {
  private:
    // Private member variables.
    unsigned position_;

  public:
    // Constructors.
    TronAction(unsigned);

    // Public member functions.
    std::string serialize() const;

    // Getters.
    unsigned get_position() const;
};

#endif // TRON_ACTION_H
