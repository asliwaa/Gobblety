#include <iostream>
#include <string>
#include <cstdlib> 
#include <limits> 

#include "game.h"
#include "player.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

Game::Game() : gamestatus(true) {};

bool Game::getGamestatus() const{
    return gamestatus; 
}

void Game::setGamestatus(bool gs) {
    gamestatus = gs;
}

//Parses user input for rows and columns so it can be read properly
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

//Clears screen after errors and after valid inputs
void Game::clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

//If players enters too many characters, focuses on the first one
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//GAme lolgic
void Game::runGame() {

    Board game;
    Player p1("B");
    Player p2("O");

    //Pointer to the player
    Player* currentPlayer = nullptr;
    //Pointer to the oponennt needed to check if a move doesn't make them win
    Player* opponentPlayer = nullptr;

    //Counter for turns, used for order interpretation
    int turnCounter = 0;
    std::string errorMessage = "";

    while(gamestatus) {
        clearScreen();

        //Determine whose turn it is
        if(turnCounter % 2 == 0) {
            currentPlayer = &p1;
            opponentPlayer = &p2;
        } else {
            currentPlayer = &p2;
            opponentPlayer = &p1;
        }

        //Draw board and arsenal
        game.drawBoard();
        currentPlayer->printArsenal();
        
        //Display previous error
        if (!errorMessage.empty()) {
            std::cout << "\n" << RED << "[!] " << errorMessage << RESET << "\n";
            errorMessage = ""; 
        } else {
            std::cout << "\n"; 
        }

        //Check if player can place, move or both
        bool canMove = game.hasVisibleGobblets(currentPlayer->getPlayerColor());
        bool canPlace = currentPlayer->hasGobbletsInArsenal();

        //Players choice
        char actionInput;

        //Decides which menu should be displayed based on available options 
        if (canMove && canPlace) {
            std::cout << "Choose action: (P)lace, (M)ove: ";
            std::cin >> actionInput;
            clearInputBuffer();
            actionInput = std::toupper(actionInput);
        } else if (!canPlace && canMove) {
            if (errorMessage.empty()) std::cout << "Your arsenal is empty. You must MOVE.\n";
            actionInput = 'M';
        } else if(turnCounter == 0 || turnCounter == 1) {
            if (errorMessage.empty()) std::cout << "Place your first gobblet.\n";
            actionInput = 'P';
        } else {
             if (errorMessage.empty()) std::cout << "No visible gobblets. You must PLACE.\n";
             actionInput = 'P';
        }

        //Tracks wheter move really happened
        bool actionSuccess = false;

        //Move action
        if (actionInput == 'M') {
            char fCol, fRow, tCol, tRow;

            //Enter position of gobblet player wants to move
            std::cout << "FROM Column (A-C): "; std::cin >> fCol; clearInputBuffer();
            std::cout << "FROM Row (1-3): ";    std::cin >> fRow; clearInputBuffer();

            int fc = parseInput(fCol);
            int fr = parseInput(fRow);

            if (fc == -1 || fr == -1) { errorMessage = "Invalid FROM coordinates!"; continue; }

            //Enter position where you want to move the gobblet
            std::cout << "TO Column (A-C): "; std::cin >> tCol; clearInputBuffer();
            std::cout << "TO Row (1-3): ";    std::cin >> tRow; clearInputBuffer();

            int tc = parseInput(tCol);
            int tr = parseInput(tRow);

            if (tc == -1 || tr == -1) { errorMessage = "Invalid TO coordinates!"; continue; }

            //Attempt the move
            if (game.moveGobblet(fr, fc, tr, tc, currentPlayer->getPlayerColor())) {
                actionSuccess = true;
            } else {
                errorMessage = "Invalid move (rules violation)!";
            }

        //Place action
        } else if (actionInput == 'P') {
            //Enter gobblet size
            char sizeInput;
            std::cout << "Enter gobblet's size (S/M/L): ";
            std::cin >> sizeInput; clearInputBuffer();

            char upperSize = std::toupper(sizeInput);
            std::string gobbletSize = "";

            //String so it can be interpreted
            if (upperSize == 'S') {
                gobbletSize = "S";
            } else if (upperSize == 'M') {
                gobbletSize = "M";
            } else if (upperSize == 'L') {
                gobbletSize = "L";
            }

            //If gobblet wasnt any of the valid sizes, show error
            if (gobbletSize == "") { errorMessage = "Invalid size!"; continue; }

            //Get gobblet from arsenal
            Gobblet gobblet = currentPlayer->getGobbletFromArsenal(gobbletSize);
            if(gobblet.getSize() == "ERROR") { errorMessage = "No such gobblet!"; continue; }

            //Enter position
            char colInput, rowInput;
            std::cout << "Enter column (A-C): "; std::cin >> colInput; clearInputBuffer();
            std::cout << "Enter row (1-3): ";    std::cin >> rowInput; clearInputBuffer();

            //Parse so it can be interpreted
            int c = parseInput(colInput);
            int r = parseInput(rowInput);

            if (c == -1 || r == -1) { 
                errorMessage = "Invalid coordinates!"; 
                currentPlayer->returnGobbletToArsenal(gobblet); 
                continue; 
            }

            //Attempt placement
            if (game.placeGobblet(gobblet, r, c)) {
                actionSuccess = true;
            } else {
                errorMessage = "Invalid move (occupied by larger/equal)!";
                currentPlayer->returnGobbletToArsenal(gobblet);
            }
        
        } else {
            //Entered something else than P or M
            errorMessage = "Invalid action!";
        }

        //Checking board for win
        if (actionSuccess) {
            //Clear screen and show state after last move
            clearScreen();
            game.drawBoard();

            //Checks if current player won
            bool myWin = game.checkWin(currentPlayer->getPlayerColor());
            //Checks if oponent won (after current player moved his gobblet and have them a win)
            bool opponentWin = game.checkWin(opponentPlayer->getPlayerColor());

            //Tie
            if (myWin && opponentWin) {
                std::cout << "\n" << GREEN << "Tie!" << RESET << "\n";
                std::cout << "You won but also gave a win to your oponent!";
                
                std::cout << "\nPress ENTER to exit...";
                std::cin.get(); // Czekamy na enter
                gamestatus = false;

            //Oponent won
            } else if (opponentWin) {
                std::cout << "\n" << RED << "=== " << opponentPlayer->getPlayerColor() << " WINS! ===" << RESET << "\n";
                std::cout << "You gave your oponent a win!";

                std::cout << "\nPress ENTER to exit...";
                std::cin.get();
                gamestatus = false;

            //Current player won
            } else if (myWin) {
                std::cout << "\n" << GREEN << "=== " << currentPlayer->getPlayerColor() << " WINS! ===" << RESET << "\n";
                std::cout << "You won!\n";

                std::cout << "\nPress ENTER to exit...";
                std::cin.get();
                gamestatus = false;

            } else {
                
                turnCounter++;
            }
        }
    }
}