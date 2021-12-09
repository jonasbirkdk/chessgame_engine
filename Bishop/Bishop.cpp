#include "Bishop.h"
#include "../helper/helper.h"
#include "../macros.h"
#include <iostream>

Bishop::Bishop(std::string colour, std::string type)
    : Piece(colour, type) {};

Bishop::~Bishop() {};

bool Bishop::validMove(
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