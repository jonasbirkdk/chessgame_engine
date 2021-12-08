#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Bishop : public Piece {
    std::string colour;

public:
    Bishop(std::string colour);
    bool validMove(std::string srcSquare, std::string destSquare, int pieceType,
        int board[8][8]);
};