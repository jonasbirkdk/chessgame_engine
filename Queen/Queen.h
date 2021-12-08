#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Queen : public Piece {
    std::string colour;

public:
    Queen(std::string colour);
    bool validMove(std::string srcSquare, std::string destSquare, int pieceType,
        int board[8][8]);
};