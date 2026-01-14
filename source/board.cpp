#include <iostream>
#include <vector>

#include "board.h"

#define BLUE    "\033[1;34m"
#define ORANGE  "\033[38;5;208m"
#define RESET   "\033[0m"

Board::Board() {}

//Draws current board stata
void Board::drawBoard() {
    std::cout << BLUE << " GO" << ORANGE << "BB" << BLUE << "LE" << ORANGE << "TY\n" << RESET;

    for (int r = 0; r < 3; r++) {
        std::cout << (r+1) << " ";
        for(int c = 0; c < 3; c++) {
            if(grid[r][c].empty()) {
                std::cout << "_ ";
            } else {
                //Top gobblet on this position
                Gobblet g = grid[r][c].back();
                //Sets display color
                std::string colorCode = (g.getColor() == "B") ? BLUE : ORANGE;
                
                std::cout << colorCode << g.getSize() << RESET << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "  A B C\n";
}

//Attempts to place gobblet at given position
bool Board::placeGobblet(Gobblet g, int r, int c) {
    //Check if position is in range
    if( r < 0 || r > 2 || c < 0 || c > 2) {
        std::cout << "Position out of range\n";
        return false;
    }

    //Position empty
    if(grid[r][c].empty()) {
        grid[r][c].push_back(g);
        return true;
    }

    //Gobblet that is currentyl on top of the position
    Gobblet onTop = grid[r][c].back();

    //Check if position is occupied if so check the occupiers size
    if(g.getNumericSize() > onTop.getNumericSize()) {
        grid[r][c].push_back(g);
        return true;
    } else {
        return false;
    }

}

//Attempts to move gobblet from one position to another
bool Board::moveGobblet(int fromR, int fromC, int toR, int toC, std::string pcol) {
    //Validate moved gobblets coordinates
    if (fromR < 0 || fromR > 2 || fromC < 0 || fromC > 2) {
        std::cout << "Invalid 'from' position!\n";
        return false;
    }

    //Checks if given position isn't empty
    if (grid[fromR][fromC].empty()) {
        std::cout << "This position is empty!\n";
        return false;
    }

    //Validating gobblets ownership
    Gobblet& candidate = grid[fromR][fromC].back();

    if (candidate.getColor() != pcol) {
        std::cout << "That's not your gobblet!\n";
        return false;
    }

    //Lifting the gobblet
    Gobblet movingGobblet = candidate;
    grid[fromR][fromC].pop_back(); 

    //Attempt to place elsewhere
    bool moveSuccess = placeGobblet(movingGobblet, toR, toC);

    if (moveSuccess) {
        //Move successfull
        return true;
    } else {
        //Move unsuccessfull, put gobblet back
        grid[fromR][fromC].push_back(movingGobblet);
        std::cout << "Move failed! Gobblet returned to original position.\n";
        return false;
    }
}

//Checks if players has any gobblets visible on board
bool Board::hasVisibleGobblets(std::string pcol) {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            //Look for a taken position
            if (!grid[r][c].empty()) {
                //Check color of gobblet on top of the position
                if(grid[r][c].back().getColor() == pcol)
                //Gobblet with players color found
                return true;
            }
        }
    }
    //No gobblets of playes color found on the board
    return false;
}

//Check if player won
bool Board::checkWin(std::string pcol) {
    //Row check
    for (int r = 0; r < 3; r++) {
        if (!grid[r][0].empty() && !grid[r][1].empty() && !grid[r][2].empty()) {
            if (grid[r][0].back().getColor() == pcol &&
                grid[r][1].back().getColor() == pcol &&
                grid[r][2].back().getColor() == pcol) {
                return true;
            }
        }
    }

    //Column Check
    for (int c = 0; c < 3; c++) {
        if (!grid[0][c].empty() && !grid[1][c].empty() && !grid[2][c].empty()) {
            if (grid[0][c].back().getColor() == pcol &&
                grid[1][c].back().getColor() == pcol &&
                grid[2][c].back().getColor() == pcol) {
                return true;
            }
        }
    }

    //First diagonal check
    if (!grid[0][0].empty() && !grid[1][1].empty() && !grid[2][2].empty()) {
        if (grid[0][0].back().getColor() == pcol &&
            grid[1][1].back().getColor() == pcol &&
            grid[2][2].back().getColor() == pcol) {
            return true;
        }
    }

    //Second diagonal check
    if (!grid[0][2].empty() && !grid[1][1].empty() && !grid[2][0].empty()) {
        if (grid[0][2].back().getColor() == pcol &&
            grid[1][1].back().getColor() == pcol &&
            grid[2][0].back().getColor() == pcol) {
            return true;
        }
    }

    return false;
}