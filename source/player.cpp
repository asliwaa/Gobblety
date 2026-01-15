#include <iostream>
#include <string>

#include "player.h"

#define BLUE    "\033[1;34m"
#define ORANGE  "\033[38;5;208m"
#define RESET   "\033[0m"

//Constructor, sets players color and fills their arsenal
Player::Player (std::string pcol) : p_color(pcol) {
    arsenal.push_back(Gobblet(pcol, "S", "a"));
    arsenal.push_back(Gobblet(pcol, "S", "a"));

    arsenal.push_back(Gobblet(pcol, "M", "a"));
    arsenal.push_back(Gobblet(pcol, "M", "a"));

    arsenal.push_back(Gobblet(pcol, "L", "a"));
    arsenal.push_back(Gobblet(pcol, "L", "a"));
}

std::string Player::getPlayerColor() const{
    return p_color;
}

void Player::setPlayerColor (std::string pcol) {
    p_color = pcol;
}

//Displays user's color and their arsenal during gameplay
void Player::printArsenal() {
    std::string col_disp;
    std::string colorCode;

    if (p_color == "B") {
        col_disp = "Blue";
        colorCode = BLUE;
    } else {
        col_disp = "Orange";
        colorCode = ORANGE;
    }
    
    std::cout << "\nPlayer: " << colorCode << col_disp <<  RESET <<"  Arsenal: [ " << colorCode;
    for(const auto& g : arsenal ) {
        //Display only those on arsenal, not on board
        if(g.getStatus() == "a") {
            std::cout << g.getSize()  << " ";
        } else {
            std::cout << "  ";
        }
    }
    std::cout << RESET << "]\n";
}

//Takes gobblet from arsenal while player tries to place it
Gobblet Player::getGobbletFromArsenal(std::string sz) {
    for (auto& g : arsenal) {
        if (g.getSize() == sz && g.getStatus() == "a") {
            //Sets status to board
            g.setStatus("b");
            return g;
        }
    }

    return Gobblet("NONE", "ERROR", "e");
}

//Returns gobblet to arsenal after failed placement/move attempt
void Player::returnGobbletToArsenal(Gobblet g) {
    for (auto& existingGobblet : arsenal) {
        if (existingGobblet.getSize() == g.getSize() && existingGobblet.getStatus() == "b") {
            //Sets status back to arsenal
            existingGobblet.setStatus("a");
            return;
        }
    }
}

//Checks if player has any gobblets left in their arsenal
bool Player::hasGobbletsInArsenal() {
    for (const auto& g : arsenal) {
        if (g.getStatus() == "a") {
            return true;
        }
    }
    return false;
}