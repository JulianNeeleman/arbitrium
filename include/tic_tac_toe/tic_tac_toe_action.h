#ifndef TIC_TAC_TOE_ACTION_H
#define TIC_TAC_TOE_ACTION_H

#include <string>

class TicTacToeAction {
  private:
    // Private member variables.
    unsigned i_, j_;

  public:
    // Constructors.
    TicTacToeAction(unsigned, unsigned);

    // Public member functions.
    std::string serialize() const;

    // Getters.
    unsigned get_i() const;
    unsigned get_j() const;
};

#endif // TIC_TAC_TOE_ACTION_H
