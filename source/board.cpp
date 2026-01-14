#include <iostream>
#include <vector>

#include "board.h"

Board::Board() {}

void Board::drawBoard() {
    std::cout << " GOBBLETY\n";

    for (int r = 0; r < 3; r++) {
        std::cout << (r+1) << " ";
        for(int c = 0; c < 3; c++) {
            if(grid[r][c].empty()) {
                std::cout << "_ ";
            } else {
                Gobblet g = grid[r][c].back();
                std::cout << g.getSize() << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "  A B C\n";
}

bool Board::placeGobblet(Gobblet g, int r, int c) {
    //Check if position is in range
    if( r < 0 || r > 2 || c < 0 || c > 2) {
        std::cout << "Position out of range";
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