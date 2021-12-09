#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Pawn : public Piece {
public:
    Pawn(std::string colour, std::string type = "Pawn");
    ~Pawn();
    bool validMove(std::string srcSquare, std::string destSquare, Piece* board[8][8]);
};