#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include "gobblet.h"

class Board {
public:
    std::vector<Gobblet> grid[3][3];

    Board();
    void drawBoard();

    bool placeGobblet(Gobblet g, int r, int c);
    
};

#endif