#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Knight : public Piece {
  public:
  Knight(std::string colour, std::string type = "Knight");
  ~Knight();

  // Takes two strings (source and destination square) and a board as
  // input and returns true if move is 'pseudo-legal' for the Piece
  // (i.e., checks if move follows rules applying to the specific piece,
  // e.g., that Knight can't move 3 squares straight, but not generic
  // Piece rules like that you can't put or leave own king in check
  // or move onto a square where your own teammate is on)
  bool validMove(std::string srcSquare, std::string destSquare,
      Piece* board[8][8]) override;
};