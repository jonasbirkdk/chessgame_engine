#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Bishop : public Piece {
  public:
  Bishop(std::string colour, std::string type = "Bishop");
  ~Bishop();
  bool validMove(
      std::string srcSquare, std::string destSquare, Piece* board[8][8]);
};