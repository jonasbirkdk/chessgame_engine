#include "Queen.h"
#include "../helper/helper.h"
#include "../macros.h"
#include <iostream>

Queen::Queen(std::string colour, std::string type, bool castlingRight)
    : Piece(colour, type, castlingRight) {};

Queen::Queen(Piece const& other)
    : Piece(other) {};

Queen::~Queen() {};

bool Queen::validMove(
    std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
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