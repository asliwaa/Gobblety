#include <iostream>

#include "game.h"

Game::Game() : gamestatus(true) {};

bool Game::getGamestatus() const{
    return gamestatus;
}

void Game::setGamestatus(bool gs) {
    gamestatus = gs;
}

int Game::parseInput(char input) {
    char upper = std::toupper(input);

    if(upper >= '1' && upper <= '3') {
        return upper - '1';
    } else if (upper >= 'A' && upper <= 'C') {
        return upper - 'A';
    } else {
        return -1;
    }
}

void Game::runGame() {

    Board game;
    Player p1("B");
    Player p2("O");

    //Pointer to the player that currently must place a gobblet
    Player* currentPlayer = nullptr;
    int turnCounter = 0;

    while(gamestatus) {
        //Decide whose turn it is
        if(turnCounter %2 == 0) {
            currentPlayer = &p1;
        } else {
            currentPlayer = &p2;
        }

        //Draw the game state
        game.drawBoard();
        currentPlayer->printArsenal();

        //Gobblet size input
        char sizeInput;
        std::cout << "Enter gobblet's size: ";
        std::cin >> sizeInput;

        char upperSize = std::toupper(sizeInput);
        std::string gobbletSize;

        if (upperSize == 'S') {
            gobbletSize = "S";
        } else if (upperSize == 'M') {
            gobbletSize = "M";
        } else if (upperSize == 'L') {
            gobbletSize = "L";
        }

        //Take gobblet from arsenal
        Gobblet gobblet = currentPlayer->getGobbletFromArsenal(gobbletSize);

        //Validate size
        if(gobblet.getSize() == "ERROR") {
            std::cout << "No such gobblet in your arsenal\n";
            continue;
        }

        //Gobblet position input
        char colInput;
        char rowInput;

        std::cout << "Enter column (A-C): ";
        std::cin >> colInput;
        std::cout << "Enter row (1-3): ";
        std::cin >> rowInput;

        //Parse input to int
        int c = parseInput(colInput);
        int r = parseInput(rowInput);

        //Validate
        if (c == -1) {
            std::cout << "Invalid column! Use A, B, or C.\n";
            currentPlayer->returnGobbletToArsenal(gobblet);
            continue;
        }

        if (r == -1) {
            std::cout << "Invalid row! Use 1, 2, or 3.\n";
            currentPlayer->returnGobbletToArsenal(gobblet);
            continue;
        }

        //Move gobblet
        bool place = game.placeGobblet(gobblet, r, c);

        if(place) {
            std::cout << "Gobblet placed at: " << colInput << rowInput << "\n";
            turnCounter++;
        } else {
            std::cout << "Invalid move. Try again.\n\n";
            currentPlayer->returnGobbletToArsenal(gobblet);
        }
    }

}