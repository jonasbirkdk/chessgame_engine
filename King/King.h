#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class King : public Piece {
  public:
  King(
      std::string colour, std::string type = "King", bool castlingRight = true);
  King(Piece const& other);
  ~King();
  // Takes two strings (source and destination square) and a board as
  // input and returns true if move is 'pseudo-legal' for the Piece
  // (i.e., checks if move follows rules applying to the specific piece,
  // e.g., that King can only move one square, but not generic
  // Piece rules like that King can't move into check)
  bool validMove(std::string srcSquare, std::string destSquare,
      Piece* board[8][8]) override;
};