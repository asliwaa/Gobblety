#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <iostream>

#include "gobblet.h"

class Board {
public:
    std::vector<Gobblet> grid[3][3];

    Board();
    void drawBoard();

    bool placeGobblet(Gobblet g, int r, int c);

    bool moveGobblet(int fromR, int fromC, int toR, int toC, std::string pcol);

    bool hasVisibleGobblets(std::string pcol);

    bool checkWin(std::string pcol);
    
};

#endif