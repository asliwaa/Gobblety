#ifndef MOVE_H
#define MOVE_H

#include <string>

#include "gobblet.h"
#include "player.h"

class Move {
    protected:
        std::string row; // 1 2 3
        std::string column; // A B C

    public:
        Move(std::string rw, std::string colm);

        std::string getRow() const;
        std::string getColumn() const;

        void setRow(std::string rw);
        void setColumn(std::string colm);

        void place();
        void shift(std::string rw, std::string colm);
};

#endif