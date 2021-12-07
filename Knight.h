#pragma once

#include "Piece.h"
#include "helper.h"
#include "macros.h"
#include <iostream>

class Knight : public Piece {
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
    if (pieceType != B_KNIGHT && pieceType != W_KNIGHT) {
      return false;
    }

    // Check destSquare does not have piece of own colour
    if (friendlyFire(destSquare, pieceType, board)) {
      return false;
    }

    // Check case where Knight jumps one square horizontally
    if (abs(sourceFile - destFile) == 1) {
      return (abs(sourceRank - destRank) == 2);
    }

    // Check case where Knight jumps one square vertically
    if (abs(sourceRank - destRank) == 1) {
      return (abs(sourceFile - destFile) == 2);
    }

    return false;
  }
};