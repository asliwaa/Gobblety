#ifndef MOVE_H
#define MOVE_H

#include <string>

class Move {
    protected:
        std::string row;
        std::string column;

    public:
        Move(std::string rw, std::string colm);

        std::string getRow() const;
        std::string getColumn() const;

        void setRow(std::string rw);
        void setColumn(std::string colm);
};

#endif MOVE_H