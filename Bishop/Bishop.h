#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Bishop : public Piece {
  public:
  Bishop(std::string colour, std::string type = "Bishop");
  ~Bishop();

  // Takes two strings (source and destination square) and a board as
  // input and returns true if move is 'pseudo-legal' for the Piece
  // (i.e., checks if move follows rules applying to the specific piece,
  // e.g., that Bishops can only move diagonally, but not generic 
  // Piece rules like that you can't put or leave own king in check 
  // or move onto a square where your own teammate is on)
  bool validMove(
      std::string srcSquare, std::string destSquare, Piece* board[8][8]);
};