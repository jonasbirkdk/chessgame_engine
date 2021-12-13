#include "Knight.h"
#include "../helper/helper.h"
#include "../macros.h"
#include <iostream>

Knight::Knight(std::string colour, std::string type, bool castlingRight)
    : Piece(colour, type, castlingRight) {};

Knight::Knight(Piece const& other) : Piece(other) {};

Knight::~Knight() {};

bool Knight::validMove(
    std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
  int srcFile = fileToInt(srcSquare);
  int srcRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  // Check case where Knight jumps one square horizontally
  if (abs(srcFile - destFile) == 1) {
    return (abs(srcRank - destRank) == 2);
  }

  // Check case where Knight jumps one square vertically
  if (abs(srcRank - destRank) == 1) {
    return (abs(srcFile - destFile) == 2);
  }

  return false;
}