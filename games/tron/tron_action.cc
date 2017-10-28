#include "games/tron/tron_action.h"

unsigned TronAction::get_position() const { return position_; }

TronAction::TronAction(unsigned position) : position_(position) {}

std::string TronAction::serialize() const {
    return "move to " + std::to_string(position_) + '\n';
}
