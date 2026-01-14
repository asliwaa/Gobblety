#include <iostream>
#include <string>

#include "move.h"

Move::Move (std::string rw, std::string col) : row(rw), column(col) {}

std::string Move::getRow() const {
    return row;
}

std::string Move::getColumn() const {
    return column;
}

void Move::setRow(std::string rw) {
    row = rw;
}

void Move::setColumn(std::string colm) {
    column = colm;
}