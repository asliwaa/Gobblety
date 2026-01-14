#include <iostream>
#include "board.h"
#include "player.h"

int main() {
    Board gra;
    Player p1("Blue");

    gra.drawBoard();

    std::cout << "\n\nTEST PLACEMENT\n\n";
    
    Gobblet g = p1.getGobbletFromArsenal("L");

    if (g.getSize() == "ERROR") {
        std::cout << "No more gobblets of that size in the arsenal!\n";
    } else {
        bool success = gra.placeGobblet(g, 1, 1);
        
        if (success) {
            gra.drawBoard();
            std::cout << "SUCCESS!\n";
        }
    }


    return 0;
}