#include <iostream>
#include <string>

#include "player.h"

Player::Player (std::string pcol) : p_color(pcol) {
    arsenal.push_back(Gobblet(pcol, "S", "a", ""));
    arsenal.push_back(Gobblet(pcol, "S", "a", ""));

    arsenal.push_back(Gobblet(pcol, "M", "a", ""));
    arsenal.push_back(Gobblet(pcol, "M", "a", ""));

    arsenal.push_back(Gobblet(pcol, "L", "a", ""));
    arsenal.push_back(Gobblet(pcol, "L", "a", ""));
}

std::string Player::getPlayerColor() const{
    return p_color;
}

void Player::setPlayerColor (std::string pcol) {
    p_color = pcol;
}

void Player::printArsenal() {
    std::string col_disp;
    if (p_color == "B") col_disp = "Blue";
    if (p_color == "O") col_disp = "Orange";
    
    std::cout << "\nPlayer" << col_disp << "  Arsenal: [ ";
    for(const auto& g : arsenal ) {
        if(g.getStatus() == "a") {
            std::cout << g.getSize()  << " ";
        } else {
            std::cout << "  ";
        }
    }
    std::cout << "]\n";
}

Gobblet Player::getGobbletFromArsenal(std::string sz) {
    for (auto& g : arsenal) {
        if (g.getSize() == sz && g.getStatus() == "a") {
            g.setStatus("b");
            return g;
        }
    }

    return Gobblet("NONE", "ERROR", "e", "");
}

void Player::returnGobbletToArsenal(Gobblet g) {
    for (auto& existingGobblet : arsenal) {
        if (existingGobblet.getSize() == g.getSize() && existingGobblet.getStatus() == "b") {
            existingGobblet.setStatus("a");
            return;
        }
    }
}