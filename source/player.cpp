#include <iostream>
#include <string>

#include "player.h"

Player::Player (std::string pcol, std::vector<std::string> ars) : p_color(pcol), arsenal(ars) {}

std::string Player::getPlayerColor() const{
    return p_color;
}

void Player::setPlayerColor (std::string pcol) {
    p_color = pcol;
}