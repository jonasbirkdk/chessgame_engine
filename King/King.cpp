#include "King.h"
#include "../helper/helper.h"
#include "../macros.h"
#include <iostream>

King::King(std::string colour, std::string type)
    : Piece(colour, type) {};

King::~King() {};

bool King::validMove(
    std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
  int srcFile = fileToInt(srcSquare);
  int srcRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  if (abs(srcFile - destFile) != 1 || abs(srcRank - destRank) != 1) {
    return false;
  }

  return true;
}