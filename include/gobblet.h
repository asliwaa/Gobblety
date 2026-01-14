#ifndef GOBBLET_H
#define GOBBLET_H

#include <string>


class Gobblet {

private:
    std::string color; //B = blue, O - orange
    std::string size; // S M L
    std::string status; // a - arsenal, b - board, e - eaten
    std::string position; // 1-3,A-C

public:
    Gobblet(std::string col, std::string sz, std::string stat, std::string pos);

    std::string getColor() const;
    std::string getSize() const;
    int getNumericSize() const;
    std::string getStatus() const;
    std::string getPosition() const;

    

    void setColor(std::string col);
    void setSize(std::string sz);
    void setStatus(std::string stat);
    void setPosition(std::string pos);

};

#endif