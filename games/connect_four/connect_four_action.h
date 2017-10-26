#ifndef CONNECT_FOUR_ACTION_H
#define CONNECT_FOUR_ACTION_H

#include <string>

class ConnectFourAction {
  private:
    // Private member variables.
    unsigned column_;

  public:
    // Constructors.
    ConnectFourAction(unsigned);

    // Public member functions.
    std::string serialize() const;

    // Getters.
    unsigned get_column() const;
};

#endif // CONNECT_FOUR_ACTION_H
