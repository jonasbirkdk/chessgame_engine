#include "Castle.h"
#include "../helper/helper.h"
#include "../macros.h"
#include <iostream>

Castle::Castle(std::string colour, std::string type, bool castlingRight)
    : Piece(colour, type, castlingRight) {};

Castle::Castle(Piece const& other)
    : Piece(other) {};

Castle::~Castle() {};

bool Castle::validMove(
    std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
  // Check that move is sideToSide
  if (!sideToSideMove(srcSquare, destSquare)) {
    return false;
  }

  // Check that path is free
  if (!freePath(srcSquare, destSquare, board)) {
    return false;
  }

  return true;
}