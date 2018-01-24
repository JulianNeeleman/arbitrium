#ifndef STATE_HPP
#define STATE_HPP

#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>


class Serializable {
  public:
    virtual std::string serialize() const = 0;
};

template<class A> class Action : public Serializable {
  protected:
    unsigned next_agent;

  public:
    Action(const unsigned);
};

template<class A> Action<A>::Action(const unsigned next_agent) : next_agent(next_agent) {}

template <class S, class A> class State : public Serializable {
  protected:
    bool turn;

  public:
    State() = default;
    virtual bool operator<(const S &) const = 0;

    virtual std::vector<A> legal_actions() const = 0;
    virtual S transition(const A &) const = 0;

    virtual int winner() const = 0;
    virtual double evaluate() const = 0;

    unsigned current_agent() const;
    unsigned other_agent() const;
};

template <class S, class A> unsigned State<S, A>::current_agent() const {
    return turn + 1;
}

template <class S, class A> unsigned State<S, A>::other_agent() const {
    return turn ? 1 : 2;
}

template <class S, class A> class Agent {
  public:
    virtual A query(const S &) const = 0;
};

template <class S, class A> class Engine {
  private:
    S state;
    const std::vector<std::unique_ptr<Agent<S, A>>> &agents;

    void next_turn();
    void dump_log() const;

  public:
    Engine(const S &, const std::vector<std::unique_ptr<Agent<S, A>>> &);
    void run();
};

template <class S, class A>
Engine<S, A>::Engine(const S &state,
                     const std::vector<std::unique_ptr<Agent<S, A>>> &agents)
    : state(state), agents(std::move(agents)) {}

template <class S, class A> void Engine<S, A>::next_turn() {
    A action = agents[state.current_agent() - 1]->query(state);
    std::cout << "player " << state.current_agent() << " chose action \""
              << action.serialize() << std::endl;
    state = state.transition(action);
}

template <class S, class A> void Engine<S, A>::dump_log() const {
    std::cout << "state:" << std::endl << state.serialize() << std::endl;
    std::vector<A> actions = state.legal_actions();
    std::cout << "actions:" << std::endl;
    for (unsigned option = 0; option < actions.size(); option++) {
        std::cout << option << " " << actions[option].serialize() << std::endl;
    }
}

template <class S, class A> void Engine<S, A>::run() {
    while (state.winner() == -1) {
        dump_log();
        next_turn();
    }
}

///// TIC TAC TOE /////

class TicTacToeAction : public Action<TicTacToeAction> {
    friend class TicTacToeState;

    unsigned i, j;

  public:
    TicTacToeAction(const unsigned, const unsigned, const unsigned);

    std::string serialize() const override;
};

class TicTacToeState : public State<TicTacToeState, TicTacToeAction> {
    std::array<std::array<unsigned, 3>, 3> board;

  public:
    TicTacToeState();

    bool operator<(const TicTacToeState &) const override;

    std::vector<TicTacToeAction> legal_actions() const override;
    TicTacToeState transition(const TicTacToeAction &) const override;

    int winner() const override;
    bool check_cells(const std::array<unsigned, 3> &) const;
    double evaluate() const override;

    std::string serialize() const override;
};

///// RANDOM /////

template <class S, class A> class Random : public Agent<S, A> {
  public:
    Random() = default;
    A query(const S &) const override;
};

///// IMPLEMENTATIONS /////

// action

TicTacToeAction::TicTacToeAction(const unsigned next_turn, const unsigned i, const unsigned j)
    : Action(next_turn), i(i), j(j) {}

std::string TicTacToeAction::serialize() const {
    return "place token on (" + std::to_string(i) + ", " + std::to_string(j) +
           ")";
}

// state

TicTacToeState::TicTacToeState() : State(), board({{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}) {}

bool TicTacToeState::operator<(const TicTacToeState &rhs) const {
    bool l_turn = current_agent(), r_turn = rhs.current_agent();
    return l_turn == r_turn ? board < rhs.board : l_turn < r_turn;
}

std::vector<TicTacToeAction> TicTacToeState::legal_actions() const {
    std::vector<TicTacToeAction> actions;
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                actions.push_back(TicTacToeAction(other_agent(), i, j));
            }
        }
    }
    return actions;
}

TicTacToeState TicTacToeState::transition(const TicTacToeAction &action) const {
    TicTacToeState child = *this;
    child.board[action.i][action.j] = current_agent();
    child.turn = action.next_agent - 1;
    return child;
}

int TicTacToeState::winner() const {
    double score = evaluate();
    if (score != 0) {
        return other_agent();
    }
    return legal_actions().empty() ? 0 : -1;
}

bool TicTacToeState::check_cells(const std::array<unsigned, 3> &cells) const {
    for (unsigned cell : cells) {
        if (cell == 0 || cell == current_agent()) {
            return false;
        }
    }
    return true;
}

double TicTacToeState::evaluate() const {
    for (unsigned i = 0; i < 3; i++) {
        if (check_cells(board[i]) ||
            check_cells({board[0][i], board[1][i], board[2][i]})) {
            return -1;
        }
    }

    if (check_cells({board[0][0], board[1][1], board[2][2]}) ||
        check_cells({board[0][2], board[1][1], board[2][0]})) {
        return -1;
    }
    return 0;
}

std::string TicTacToeState::serialize() const {
    std::string serialization = "";
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            serialization += std::to_string(board[i][j]) + '\t';
        }
        serialization += '\n';
    }
    return serialization;
}

// agent

template <class S, class A> A Random<S, A>::query(const S &state) const {
    std::vector<A> actions = state.legal_actions();
    return actions[rand() % actions.size()];
}

///// APPLICATION /////

int main() {
    srand(time(NULL));
    TicTacToeState initial_state;
    std::vector<std::unique_ptr<Agent<TicTacToeState, TicTacToeAction>>> agents;
    std::unique_ptr<Agent<TicTacToeState, TicTacToeAction>> a(
        new Random<TicTacToeState, TicTacToeAction>),
        b(new Random<TicTacToeState, TicTacToeAction>);
    agents.push_back(std::move(a));
    agents.push_back(std::move(b));
    Engine<TicTacToeState, TicTacToeAction> engine(initial_state, agents);
    engine.run();
    return 0;
}

#endif // STATE_HPP
