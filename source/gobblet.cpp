#include <iostream>
#include <string>

#include "gobblet.h"


Gobblet::Gobblet (std::string col, std::string sz, std::string stat) : color(col), size(sz), status(stat) {}

std::string Gobblet::getColor() const {
    return color;
}

std::string Gobblet::getSize() const {
    return size;
}

//Converts size from string to int, used for size comparison
int Gobblet::getNumericSize() const {
    if(size == "S") return 1;
    if(size == "M") return 2;
    if(size == "L") return 3;
    return 0;
}

std::string Gobblet::getStatus() const {
    return status;
}

void Gobblet::setColor(std::string col) {
    color = col;
}

void Gobblet::setSize(std::string sz) {
    size = sz;
}

void Gobblet::setStatus(std::string stat) {
    status = stat;
}