#include "games/connect_four/connect_four_action.h"

unsigned ConnectFourAction::get_column() const { return column_; }

ConnectFourAction::ConnectFourAction(unsigned column) : column_(column) {}

std::string ConnectFourAction::serialize() const {
    return "place token in column " + std::to_string(column_) + '\n';
}
