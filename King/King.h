#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class King : public Piece {
public:
    std::string colour;
    King(std::string colour);
    bool validMove(std::string srcSquare, std::string destSquare, int pieceType,
        int board[8][8]);
};