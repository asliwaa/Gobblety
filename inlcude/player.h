#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Player {
    private:
        std::string p_color;
        std::vector<std::string> arsenal;

    public:
        Player(std::string pcol, std::vector<std::string> ars);

        std::string getPlayerColor() const;
        
        void setPlayerColor(std::string pcol);
};

#endif PLAYER_H