#pragma once

#include <iostream>

class Piece {
private:
    std::string colour;
    std::string type;

public:
    Piece(std::string colour, std::string type)
        : colour(colour)
        , type(type) {};
    std::string getColour() { return this->colour; }
    std::string getType() { return this->type; }
    virtual bool validMove(std::string srcSquare, std::string destSquare, Piece* board[8][8])
        = 0;
    virtual ~Piece() {};
};