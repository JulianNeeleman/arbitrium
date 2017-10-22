#ifndef TIC_TAC_TOE_ACTION_H
#define TIC_TAC_TOE_ACTION_H

#include "include/lib/action.h"

class TicTacToeAction : public Action {
  private:
    // Private member variables.
    unsigned i_, j_;

    // Private member functions.

  public:
    // Constructors.
    TicTacToeAction(int, unsigned, unsigned);

    // Public member functions.

    // Setters.

    // Getters.
    unsigned get_i() const;
    unsigned get_j() const;
};

#endif // TIC_TAC_TOE_ACTION_H
