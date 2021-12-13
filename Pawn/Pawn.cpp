#include "Pawn.h"
#include "../helper/helper.h"
#include "../macros.h"
#include <iostream>

Pawn::Pawn(std::string colour, std::string type, bool castlingRight)
    : Piece(colour, type, castlingRight) {};

Pawn::Pawn(Piece const& other)
    : Piece(other) {};

Pawn::~Pawn() {};

bool Pawn::validMove(
    std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
  int srcFile = fileToInt(srcSquare);
  int srcRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);
  int pawnRank = (this->getColour() == "Black") ? 6 : 1;

  // Check direction along rank is valid
  if (this->getColour() == "Black") {
    if ((srcRank - destRank) <= 0) {
      return false;
    }
  } else {
    if ((srcRank - destRank) >= 0) {
      return false;
    }
  }

  // Check move valid for sideToSide move
  // including whether any pieces are blocking the path, or if any
  // pieces are on the destSquare
  if (sideToSideMove(srcSquare, destSquare)
      && freePath(srcSquare, destSquare, board)
      && board[destFile][destRank] == nullptr) {
    if (srcRank == pawnRank) {
      return (abs(srcRank - destRank) <= 2 && (srcFile - destFile) == 0);
    } else {
      return (abs(srcRank - destRank) == 1 && (srcFile - destFile) == 0);
    }
  }

  // Check move is valid for diagonal move, including whether any
  // pieces are blocking the path and that destSquare contains
  // opponent piece
  if (diagonalMove(srcSquare, destSquare)
      && freePath(srcSquare, destSquare, board)
      && board[destFile][destRank] != nullptr) {
    return (abs(srcRank - destRank) == 1 && abs(srcFile - destFile) == 1);
  }

  return false;
}