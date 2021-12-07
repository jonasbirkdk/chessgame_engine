#pragma once

#include "Piece.h"
#include "helper.h"
#include "macros.h"
#include <iostream>

class Pawn : public Piece {
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
    if (pieceType != B_PAWN && pieceType != W_PAWN) {
      return false;
    }

    // Check destSquare does not have piece of own colour
    if (friendlyFire(destSquare, pieceType, board)) {
      return false;
    }

    if (pieceType == B_PAWN) {
      // Check direction along rank is valid
      if ((sourceRank - destRank) <= 0) {
        return false;
      }

      // Check move valid for sideToSide move
      // including whether any pieces are blocking the path, or if any
      // pieces are on the destSquare
      if (sideToSideMove(srcSquare, destSquare)
          && freePath(srcSquare, destSquare, board)
          && squareEmpty(destSquare, board)) {
        if (sourceRank == 6) {
          return (
              abs(sourceRank - destRank) <= 2 && (sourceFile - destFile) == 0);
        } else {
          return (
              abs(sourceRank - destRank) == 1 && (sourceFile - destFile) == 0);
        }
      }

      // Check move is valid for diagonal move, including whether any
      // pieces are blocking the path and that destSquare contains
      // opponent piece
      if (diagonalMove(srcSquare, destSquare)
          && freePath(srcSquare, destSquare, board)
          && !squareEmpty(destSquare, board)) {
        return (
            abs(sourceRank - destRank) == 1 && abs(sourceFile - destFile) == 1);
      }
      return false;
    }
    if (pieceType == W_PAWN) {
      // Check direction along rank is valid
      if ((sourceRank - destRank) >= 0) {
        return false;
      }

      // Check move valid for sideToSide move
      // including whether any pieces are blocking the path, or if any
      // pieces are on the destSquare
      if (sideToSideMove(srcSquare, destSquare)
          && freePath(srcSquare, destSquare, board)
          && squareEmpty(destSquare, board)) {
        if (sourceRank == 1) {
          return (
              abs(sourceRank - destRank) <= 2 && (sourceFile - destFile) == 0);
        } else {
          return (
              abs(sourceRank - destRank) == 1 && (sourceFile - destFile) == 0);
        }
      }

      // Check move is valid for diagonal move, including whether any
      // pieces are blocking the path and that destSquare contains
      // opponent piece
      if (diagonalMove(srcSquare, destSquare)
          && freePath(srcSquare, destSquare, board)) {
        return (
            abs(sourceRank - destRank) == 1 && abs(sourceFile - destFile) == 1);
      }
      return false;
    }
    return false;
  }
};