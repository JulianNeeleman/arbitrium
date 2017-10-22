#ifndef LIB_STATE_H
#define LIB_STATE_H

#include <memory>
#include <vector>

class State {
  private:
    // Private member variables.

    // Private member functions.

  public:
    // Constructors.

    // Public member functions.
    virtual std::unique_ptr<State>
    transition(const std::unique_ptr<Action> &) const = 0;

    virtual bool is_terminal() const = 0;
    virtual double evaluate() const = 0;
    virtual std::vector<std::unique_ptr<Action>> actions() const = 0;
    // Setters.
};

#endif // LIB_STATE_H
