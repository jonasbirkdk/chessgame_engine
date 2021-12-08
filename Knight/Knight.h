#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Knight : public Piece {
    std::string colour;

public:
    Knight(std::string colour);
    bool validMove(std::string srcSquare, std::string destSquare, int pieceType,
        int board[8][8]);
};