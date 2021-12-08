#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Pawn : public Piece {
    std::string colour;

public:
    Pawn(std::string colour);
    bool validMove(std::string srcSquare, std::string destSquare, int pieceType,
        int board[8][8]);
};