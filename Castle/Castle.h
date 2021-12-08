#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Castle : public Piece {
    std::string colour;

public:
    Castle(std::string colour);
    bool validMove(std::string srcSquare, std::string destSquare, int pieceType,
        int board[8][8]);
};