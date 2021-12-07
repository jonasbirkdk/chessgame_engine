#pragma once

#include "Piece.h"
#include "helper.h"
#include "macros.h"
#include <iostream>

class Bishop : public Piece {
  public:
  bool validMove(std::string srcSquare, std::string destSquare, int pieceType,
      int board[8][8])
  {
    // Check that srcSquare or destSquare are on the board
    if (!inputValid(srcSquare) || !inputValid(destSquare)) {
      return false;
    }

    // Handle case where move may be valid, but pieceType input is invalid
    if (pieceType != B_BISHOP && pieceType != W_BISHOP) {
      return false;
    }

    // Check destSquare does not have piece of own colour
    if (friendlyFire(destSquare, pieceType, board)) {
      return false;
    }

    // Check that move is diagonal or sideToSide
    if (!diagonalMove(srcSquare, destSquare)
        && !sideToSideMove(srcSquare, destSquare)) {
      return false;
    }

    // Check that path is free
    if (!freePath(srcSquare, destSquare, board)) {
      return false;
    }

    return true;
  }
};