#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class King : public Piece {
  public:
  King(std::string colour, std::string type = "King");
  ~King();
  bool validMove(
      std::string srcSquare, std::string destSquare, Piece* board[8][8]);
};