#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Queen : public Piece {
  public:
  Queen(std::string colour, std::string type = "Queen");
  ~Queen();
  bool validMove(
      std::string srcSquare, std::string destSquare, Piece* board[8][8]);
};