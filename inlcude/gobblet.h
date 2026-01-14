#ifndef GOBBLET_H
#define GOBBLET_H

#include <string>


class Gobblet {

private:
    std::string color;
    std::string size;
    std::string status;

public:
    Gobblet(std::string col, std::string sz, std::string stat);

    std::string getColor() const;
    std::string getSize() const;
    std::string getStatus() const;

    void setColor(std::string col);
    void setSize(std::string sz);
    void setStatus(std::string stat);

};

#endif GOBBLET_H