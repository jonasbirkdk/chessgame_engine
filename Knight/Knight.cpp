#include "Knight.h"
#include "../helper/helper.h"
#include "../macros.h"
#include <iostream>

Knight::Knight(std::string colour, std::string type, bool castlingRight)
    : Piece(colour, type, castlingRight) {};

Knight::Knight(Piece const& other)
    : Piece(other) {};

Knight::~Knight() {};

bool Knight::validMove(
    std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
  auto srcFile = fileToInt(srcSquare);
  auto srcRank = rankToInt(srcSquare);
  auto destFile = fileToInt(destSquare);
  auto destRank = rankToInt(destSquare);

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