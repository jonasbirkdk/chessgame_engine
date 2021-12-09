#pragma once

#include "macros.h"
#include "Piece/Piece.h"
#include <iostream>

class ChessBoard {
  public:
  Piece* board[8][8];
  std::string nextUp;

  ChessBoard();
  ~ChessBoard();
  void resetBoard();
  void submitMove(std::string srcSquare, std::string destSquare);
};