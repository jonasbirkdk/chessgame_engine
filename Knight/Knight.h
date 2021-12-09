#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Knight : public Piece {
public:
    Knight(std::string colour, std::string type = "Knight");
    ~Knight();
    bool validMove(std::string srcSquare, std::string destSquare, Piece* board[8][8]);
};