#pragma once

#include <iostream>

class Piece {
    std::string colour;

public:
    virtual bool validMove(std::string srcSquare, std::string destSquare, int pieceType,
        int board[8][8])
        = 0;
};