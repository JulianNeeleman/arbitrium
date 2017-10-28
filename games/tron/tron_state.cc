#include "games/tron/tron_state.h"

/**
 * Default constructor.
 */
TronState::TronState() : turn_(0), board_(std::bitset<256>()) {
    // Random initial game state.
    unsigned i = (rand() % 5) + 1;
    unsigned j = (rand() % 15) + 1;

    // Mirror opening position.
    positions_[0] = i + j * 16;
    positions_[1] = 15 - i + j * 16;
}

/**
 * Update the board with the action on a copy of the state.
 */
TronState TronState::transition(const TronAction &action) const {
    TronState child = *this;

    // Apply changes to the model.
    child.board_.set(positions_[turn_]);
    child.positions_[child.turn_] = action.get_position();

    // Move turn to next player.
    child.turn_ = !turn_;

    return child;
}

/**
 * Provide a way to sort states in cache.
 */
bool TronState::operator<(const TronState &rhs) const {
    if (turn_ != rhs.turn_) {
        return turn_ < rhs.turn_;
    }

    for (unsigned player : {0, 1}) {
        if (positions_[player] != rhs.positions_[player]) {
            return positions_[player] < rhs.positions_[player];
        }
    }

    for (unsigned i = 0; i < 256; i++) {
        if (board_[i] ^ rhs.board_[i]) {
            return board_[i];
        }
    }
    return false;
}

/**
 * Check if one or both of the players ran into a wall.
 */
bool TronState::is_terminal() const {
    return positions_[0] == positions_[1] || board_[positions_[0]] ||
           board_[positions_[1]];
}

/**
 * Decide a winner, or declare a draw, when the game ends.
 */
int TronState::result() const {
    assert(is_terminal());
    if (positions_[0] == positions_[1] ||
        (board_[positions_[0]] && board_[positions_[1]])) {
        // Draw.
        return -1;
    }

    // Decisive result.
    return board_[positions_[0]] ? 1 : 0;
}

/**
 * Evaluate the position.
 */
double TronState::evaluate() const {
    std::set<unsigned> latest[2];
    std::queue<std::tuple<bool, unsigned, unsigned>> q;

    if (is_terminal()) {
        int res = result();
        return res == -1 ? (turn_ ? 255.0 : -255.0) : (res ? 256.0 : -256.0);
    }

    // Work on a copy.
    TronState cp = *this;

    for (bool i : {0, 1}) {
        cp.board_.set(positions_[i]);
        latest[i].insert(positions_[i]);
        q.push(std::make_tuple(i, positions_[i], 0));
    }

    double score = 0.0;
    unsigned last = 0;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();

        cp.turn_ = std::get<0>(t);
        cp.positions_[cp.turn_] = std::get<1>(t);
        unsigned dist = std::get<2>(t);

        if (dist > last) {
            // Flush latest arrays.
            last = dist;
            latest[0].clear();
            latest[1].clear();
        }

        for (const TronAction &action : cp.actions()) {
            unsigned pos = action.get_position();
            if (cp.board_[pos]) {
                if (latest[!cp.turn_].find(pos) != latest[!cp.turn_].end()) {
                    score += cp.turn_ ? 1.0 : -1.0;
                }
            } else {
                cp.board_.set(pos);
                score += cp.turn_ ? 1.0 : -1.0;
                latest[cp.turn_].insert(pos);
                q.push(std::make_tuple(cp.turn_, pos, dist + 1));
            }
        }
    }

    return score;
}

/**
 * Return all empty fields on the board, which are precisely the set of legal
 * actions.
 */
std::vector<TronAction> TronState::actions() const {
    std::vector<TronAction> legal;

    unsigned p = positions_[turn_];
    if (!(p % 16 == 0)) {
        // Left.
        legal.push_back(p - 1);
    }

    if (!(p % 16 == 15)) {
        // Right.
        legal.push_back(p + 1);
    }

    if (p + 16 < 256) {
        // Up.
        legal.push_back(p + 16);
    }

    if (p >= 16) {
        // Down.
        legal.push_back(p - 16);
    }

    return legal;
}

/**
 * Provide a serialization of the state.
 */
std::string TronState::serialize() const {
    std::string out = "";

    // Serialize the board.
    for (unsigned i = 0; i < 16; i++) {
        for (unsigned j = 0; j < 16; j++) {
            if (i + j * 16 == positions_[0]) {
                out += "X";
            } else if (i + j * 16 == positions_[1]) {
                out += "Y";
            } else {
                out += std::to_string(board_[i + j * 16]);
            }
        }
        out += '\n';
    }

    return out;
}

/**
 * Retrieve who's turn it is in this state.
 */
unsigned TronState::get_turn() const { return turn_; }

/**
 * Increment the turn;
 */
void TronState::next_turn() { turn_ = !turn_; }
