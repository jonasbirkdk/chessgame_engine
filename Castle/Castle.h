#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Castle : public Piece {
public:
    Castle(std::string colour, std::string type = "Castle");
    ~Castle();
    bool validMove(std::string srcSquare, std::string destSquare, Piece* board[8][8]);
};