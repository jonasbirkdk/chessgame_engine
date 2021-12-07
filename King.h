#pragma once

#include "Piece.h"
#include "helper.h"
#include "macros.h"
#include <iostream>

class King : public Piece {
  public:
  bool validMove(std::string srcSquare, std::string destSquare, int pieceType,
      int board[8][8])
  {
    int sourceFile = fileToInt(srcSquare);
    int sourceRank = rankToInt(srcSquare);
    int destFile = fileToInt(destSquare);
    int destRank = rankToInt(destSquare);

    // Check that srcSquare or destSquare are on the board
    if (!inputValid(srcSquare) || !inputValid(destSquare)) {
      return false;
    }

    // Handle case where move may be valid, but pieceType input is invalid
    if (pieceType != B_KING && pieceType != W_KING) {
      return false;
    }

    // Check destSquare does not have piece of own colour
    if (friendlyFire(destSquare, pieceType, board)) {
      return false;
    }

    if (abs(sourceFile - destFile) != 1 || abs(sourceRank - destRank) != 1) {
      return false;
    }

    return true;
  }
};