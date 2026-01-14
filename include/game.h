#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"

class Game {
    private:
        bool gamestatus;

        int parseInput(char input);
    
    public:
        Game();
        bool getGamestatus() const;
        void setGamestatus(bool gs);

        void runGame();

};

#endif