#include "King.h"
#include "../helper/helper.h"
#include "../macros.h"
#include <iostream>

King::King(std::string colour, std::string type, bool castlingRight)
    : Piece(colour, type, castlingRight) {};

King::King(Piece const& other)
    : Piece(other) {};

King::~King() {};

bool King::validMove(
    std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
  auto srcFile = fileToInt(srcSquare);
  auto srcRank = rankToInt(srcSquare);
  auto destFile = fileToInt(destSquare);
  auto destRank = rankToInt(destSquare);

  if (abs(srcFile - destFile) != 1 || abs(srcRank - destRank) != 1) {
    return false;
  }

  return true;
}