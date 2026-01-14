#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "gobblet.h"

class Player {
    private:
        std::string p_color; //B - blue, O - orange
        std::vector<Gobblet> arsenal; // S S M M L L

    public:
        Player(std::string pcol);
    
        std::string getPlayerColor() const;
        void setPlayerColor(std::string pcol);

        void printArsenal();
        
        Gobblet getGobbletFromArsenal(std::string sz);

        void returnGobbletToArsenal(Gobblet g);
        

};

#endif