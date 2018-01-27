

 #include <string>
 #include <vector>






 #include <limits>
 #include <vector>






 #include <iostream>






 #include <map>

template <class S> class Cache {
    std::map<S, double> memory;

  public:
    void flush();
    void push(const S &state, const double score);
    bool hit(const S &state) const;
    double retrieve(const S &state) const;
};

template <class S> void Cache<S>::flush() {
    memory.clear();
}

template <class S> void Cache<S>::push(const S &state, const double score) {
    memory[state] = score;
}

template <class S> bool Cache<S>::hit(const S &state) const {
    return memory.find(state) != memory.end();
}
template <class S> double Cache<S>::retrieve(const S &state) const {
    return memory.at(state);
}

template <class S, class A> class Agent {
    Cache<S> cache;

    virtual double evaluate(const S &state);
    virtual A query(const S &state) = 0;

  protected:
    double evaluate_with_cache(const S &state);

  public:
    A flush_cache_and_query(const S &state);
};

template <class S, class A>
double Agent<S, A>::evaluate(const S &state) {
    return state.evaluate();
}

template <class S, class A>
double Agent<S, A>::evaluate_with_cache(const S &state) {
    if (!cache.hit(state)) {
        cache.push(state, evaluate(state));
    }
    return cache.retrieve(state);
}

template <class S, class A>
A Agent<S, A>::flush_cache_and_query(const S &state) {
    cache.flush();
    return query(state);
}

template <class S, class A> class Negamax : public Agent<S, A> {
    unsigned max_depth, depth;

    double evaluate(const S &state) override;

  public:
    Negamax();
    explicit Negamax(const unsigned max_depth);
    A query(const S &state) override;
};

template <class S, class A> Negamax<S, A>::Negamax() : max_depth(6) {}

template <class S, class A>
Negamax<S, A>::Negamax(const unsigned max_depth) : max_depth(max_depth) {}

template <class S, class A>
double Negamax<S, A>::evaluate(const S &state) {
    if (depth == 0 || state.winner() != -2) {
        return state.evaluate();
    }
    double best = std::numeric_limits<double>::lowest();
    depth--;
    for (const A &action : state.legal_actions()) {
        S neighbor = state.transition(action);
        best = std::max(best, -this->evaluate_with_cache(neighbor));
    }
    depth++;
    return best;
}

template <class S, class A> A Negamax<S, A>::query(const S &state) {
    depth = max_depth;
    double best_eval = std::numeric_limits<double>::lowest();
    A best_action = state.legal_actions()[0];
    for (const A &action : state.legal_actions()) {
        S neighbor = state.transition(action);
        double eval = -this->evaluate_with_cache(neighbor);
        if (best_eval < eval) {
            best_eval = eval;
            best_action = action;
        }
    }
    return best_action;
}










 #include <string>











 #include <string>

class Serializable {
  public:
    virtual std::string serialize() const = 0;
};

template <class A> class Action : public Serializable {
  public:
    explicit Action() = default;
};

class ConnectFourAction : public Action<ConnectFourAction> {
    friend class ConnectFourState;

    bool next_turn;
    unsigned row, column;

  public:
    ConnectFourAction(const bool, const unsigned, const unsigned);

    std::string serialize() const override;
};





 #include <array>
 #include <tuple>






 #include <array>
 #include <string>
 #include <tuple>






 #include <iostream>

 #include <array>
 #include <bitset>

template <unsigned R, unsigned C> class Bitboard {
    static constexpr unsigned L = (R + 1) * C;
    static constexpr std::array<unsigned, 4> directions{1, R, R + 1, R + 2};

    std::bitset<L> board;

  public:
    Bitboard();
    explicit Bitboard(const std::bitset<L> &board);
    explicit Bitboard(const std::array<std::array<bool, C>, R> &matrix);

    bool operator<(const Bitboard &rhs) const;
    Bitboard operator|(const Bitboard &rhs) const;

    bool three_consecutive_bits() const;
    bool four_consecutive_bits() const;

    bool get(const unsigned row, const unsigned column) const;
    void set(const unsigned row, const unsigned column, const bool value);
};



template <unsigned R, unsigned C> unsigned L = std::max(R, C) * std::max(R, C);
template <unsigned R, unsigned C>
constexpr std::array<unsigned, 4> Bitboard<R, C>::directions;

template <unsigned R, unsigned C> Bitboard<R, C>::Bitboard() : board{} {}

template <unsigned R, unsigned C>
Bitboard<R, C>::Bitboard(const std::bitset<L> &board) : board(board) {}

template <unsigned R, unsigned C>
Bitboard<R, C>::Bitboard(const std::array<std::array<bool, C>, R> &matrix) {
    for (unsigned row = 0; row < R; row++) {
        for (unsigned column = 0; column < C; column++) {
            set(row, column, matrix.at(row).at(column));
        }
    }
}

template <unsigned R, unsigned C>
bool Bitboard<R, C>::operator<(const Bitboard<R, C> &rhs) const {
    for (unsigned i = 0; i < L; i++) {
        if (board[i]^rhs.board[i]) {
            return board[i] < rhs.board[i];
        }
    }
    return false;
}

template <unsigned R, unsigned C>
Bitboard<R, C> Bitboard<R, C>::operator|(const Bitboard<R, C> &rhs) const {
    return Bitboard<R, C>(board | rhs.board);
}

template <unsigned R, unsigned C>
bool Bitboard<R, C>::three_consecutive_bits() const {
    for (unsigned direction : Bitboard<R, C>::directions) {
        std::bitset<L> shifted = board & (board >> direction);
        if ((board & (shifted >> direction)) != 0) {
            return true;
        }
    }
    return false;
}

template <unsigned R, unsigned C>
bool Bitboard<R, C>::four_consecutive_bits() const {
    for (unsigned direction : Bitboard<R, C>::directions) {
        std::bitset<L> shifted = board & (board >> direction);
        if ((shifted & (shifted >> (2 * direction))) != 0) {
            return true;
        }
    }
    return false;
}

template <unsigned R, unsigned C>
bool Bitboard<R, C>::get(const unsigned row, const unsigned column) const {
    return board[row + (R + 1) * column];
}

template <unsigned R, unsigned C>
void Bitboard<R, C>::set(const unsigned row, const unsigned column,
                         const bool value) {
    board.set(row + (R + 1) * column, value);
}


template <unsigned R, unsigned C> class BitboardPair : public Serializable {
    std::pair<Bitboard<R, C>, Bitboard<R, C>> board;

  protected:
    bool turn;

  public:
    BitboardPair();
    explicit BitboardPair(
        const std::pair<Bitboard<R, C>, Bitboard<R, C>> &board,
        const bool turn);

    virtual bool operator<(const BitboardPair<R, C> &rhs) const;

    Bitboard<R, C> board_union() const;

    Bitboard<R, C> current_agent_board() const;
    Bitboard<R, C> other_agent_board() const;

    Bitboard<R, C> &current_agent_board();
    Bitboard<R, C> &other_agent_board();

    std::string serialize() const override;
};

template <unsigned R, unsigned C>
BitboardPair<R, C>::BitboardPair() : board{}, turn(false) {}

template <unsigned R, unsigned C>
BitboardPair<R, C>::BitboardPair(
    const std::pair<Bitboard<R, C>, Bitboard<R, C>> &board, const bool turn)
    : board(board), turn(turn) {}

template <unsigned R, unsigned C>
bool BitboardPair<R, C>::operator<(const BitboardPair<R, C> &rhs) const {
    return std::tie(turn, board) < std::tie(rhs.turn, rhs.board);
}

template <unsigned R, unsigned C>
Bitboard<R, C> BitboardPair<R, C>::board_union() const {
    return board.first | board.second;
}

template <unsigned R, unsigned C>
Bitboard<R, C> BitboardPair<R, C>::current_agent_board() const {
    return turn ? board.second : board.first;
}

template <unsigned R, unsigned C>
Bitboard<R, C> BitboardPair<R, C>::other_agent_board() const {
    return turn ? board.first : board.second;
}

template <unsigned R, unsigned C>
Bitboard<R, C> &BitboardPair<R, C>::current_agent_board() {
    return turn ? board.second : board.first;
}

template <unsigned R, unsigned C>
Bitboard<R, C> &BitboardPair<R, C>::other_agent_board() {
    return turn ? board.first : board.second;
}

template <unsigned R, unsigned C>
std::string BitboardPair<R, C>::serialize() const {
    std::string serialization = "";
    for (int row = R - 1; row >= 0; row--) {
        for (unsigned column = 0; column < C; column++) {
            if (board.first.get(row, column)) {
                serialization += "0\t";
            } else if (board.second.get(row, column)) {
                serialization += "1\t";
            } else {
                serialization += ".\t";
            }
        }
        serialization += '\n';
    }
    return serialization;
}





 #include <vector>



template <class S, class A> class State : public Serializable {
  public:
    virtual bool operator<(const S &) const = 0;

    virtual std::vector<A> legal_actions() const = 0;
    virtual S transition(const A &) const = 0;

    virtual int winner() const = 0;
    virtual double evaluate() const;

    virtual unsigned get_turn() const = 0;
};

template <class S, class A> double State<S, A>::evaluate() const {
    int result = winner();
    if (result < 0) {
        return 0.0;
    }
    return result == get_turn() ? 1.0 : -1.0;
}

class ConnectFourState : public State<ConnectFourState, ConnectFourAction>,
                         public BitboardPair<6, 7> {
    std::array<unsigned, 7> heights;

  public:
    ConnectFourState();
    explicit ConnectFourState(
        const std::pair<Bitboard<6, 7>, Bitboard<6, 7>> &board,
        const bool turn);

    bool operator<(const ConnectFourState &rhs) const override;

    std::vector<ConnectFourAction> legal_actions() const override;
    ConnectFourState transition(const ConnectFourAction &action) const override;

    int winner() const override;
    bool check(const std::array<unsigned, 4> &) const;

    std::string serialize() const override;

    unsigned get_turn() const override;
};





 #include <array>
 #include <iostream>
 #include <sstream>
 #include <string>
 #include <vector>

template <class S, class A, class T> class RiddlesBot {
  protected:
    unsigned timebank, time_per_move, your_botid, round;
    std::array<std::string, 2> player_names;
    std::string your_bot;

    S state;
    T agent;

    bool try_base_setting(const std::string &key, const std::string &value);
    virtual void custom_setting(const std::string &key,
                                const std::string &value) = 0;
    void setting(const std::string &key, const std::string &value);

    virtual void update_state(const std::string &value) = 0;
    void update(const std::string &key, const std::string &value);

    virtual void move(unsigned timeout) = 0;

    std::vector<std::string> split(const std::string &line, char delim);

  public:
    RiddlesBot() = default;
    void run();
};

template <class S, class A, class T>
bool RiddlesBot<S, A, T>::try_base_setting(const std::string &key,
                                           const std::string &value) {
    if (key == "timebank") {
        timebank = std::stoi(value);
    } else if (key == "time_per_move") {
        time_per_move = std::stoi(value);
    } else if (key == "player_names") {
        std::vector<std::string> names = split(value, ',');
        player_names[0] = names[0];
        player_names[1] = names[1];
    } else if (key == "your_bot") {
        your_bot = value;
    } else if (key == "your_botid") {
        your_botid = std::stoi(value);
    } else {
        return false;
    }
    return true;
}

template <class S, class A, class T>
void RiddlesBot<S, A, T>::setting(const std::string &key,
                                  const std::string &value) {
    if (!this->try_base_setting(key, value)) {
        custom_setting(key, value);
    }
}

template <class S, class A, class T>
void RiddlesBot<S, A, T>::update(const std::string &key,
                                 const std::string &value) {
    if (key == "round") {
        round = std::stoi(value);
    } else if (key == "field") {
        update_state(value);
    }
}

template <class S, class A, class T>
std::vector<std::string> RiddlesBot<S, A, T>::split(const std::string &line,
                                                    char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

template <class S, class A, class T> void RiddlesBot<S, A, T>::run() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<std::string> command = split(line, ' ');
        if (command[0] == "settings") {
            setting(command[1], command[2]);
        } else if (command[0] == "update" && command[1] == "game") {
            update(command[2], command[3]);
        } else if (command[0] == "action" && command[1] == "move") {
            move(std::stoi(command[2]));
        }
    }
}

template <class T>
class ConnectFourBot
    : public RiddlesBot<ConnectFourState, ConnectFourAction, T> {
    unsigned field_columns, field_rows;

    void custom_setting(const std::string &key,
                        const std::string &value) override;
    void update_state(const std::string &value) override;
    void move(const unsigned clock) override;
};

template <class T>
void ConnectFourBot<T>::custom_setting(const std::string &key,
                                       const std::string &value) {
    if (key == "field_columns") {
        field_columns = std::stoi(value);
    } else if (key == "field_rows") {
        field_rows = std::stoi(value);
    }
}

template <class T>
void ConnectFourBot<T>::update_state(const std::string &value) {
    std::vector<std::string> cells = this->split(value, ',');
    std::pair<Bitboard<6, 7>, Bitboard<6, 7>> board;
    for (unsigned row = 0; row < 6; row++) {
        for (unsigned column = 0; column < 7; column++) {
            switch (cells[7 * row + column][0]) {
            case '0':
                board.first.set(row, column, true);
            case '1':
                board.second.set(row, column, true);
            default:
                break;
            }
        }
    }
    this->state = ConnectFourState(board, this->your_botid);
}

template <class T> void ConnectFourBot<T>::move(const unsigned clock) {
    ConnectFourAction action = this->agent.flush_cache_and_query(this->state);
    std::cout << "place_disc " << action.serialize() << std::endl;
}




ConnectFourState::ConnectFourState() : BitboardPair<6, 7>(), heights{} {}

ConnectFourState::ConnectFourState(
    const std::pair<Bitboard<6, 7>, Bitboard<6, 7>> &board, const bool turn)
    : BitboardPair<6, 7>(board, turn), heights{} {}

bool ConnectFourState::operator<(const ConnectFourState &rhs) const {
    return BitboardPair<6, 7>::operator<(rhs);
}

std::vector<ConnectFourAction> ConnectFourState::legal_actions() const {
    std::vector<ConnectFourAction> actions;
    for (unsigned column = 0; column < 7; column++) {
        if (heights.at(column) < 6) {
            actions.push_back({!turn, heights.at(column), column});
        }
    }
    return actions;
}

ConnectFourState
ConnectFourState::transition(const ConnectFourAction &action) const {
    ConnectFourState child = *this;
    child.current_agent_board().set(action.row, action.column, true);
    child.heights.at(action.column) = action.row + 1;
    child.turn = action.next_turn;
    return child;
}

int ConnectFourState::winner() const {
    if (current_agent_board().four_consecutive_bits()) {
        return static_cast<int>(turn);
    }
    if (other_agent_board().four_consecutive_bits()) {
        return static_cast<int>(!turn);
    }
    return legal_actions().empty() ? -1 : -2;
}

std::string ConnectFourState::serialize() const {
    return BitboardPair<6, 7>::serialize();
}

unsigned ConnectFourState::get_turn() const {
    return static_cast<unsigned>(turn);
}



ConnectFourAction::ConnectFourAction(const bool next_turn, const unsigned row,
                                     const unsigned column)
    : next_turn(next_turn), row(row), column(column) {}

std::string ConnectFourAction::serialize() const {
    return std::to_string(column);
}

int main() {
    ConnectFourBot<Negamax<ConnectFourState, ConnectFourAction>> bot;
    bot.run();
    return 0;
}
