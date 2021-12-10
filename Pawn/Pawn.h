#pragma once

#include "../Piece/Piece.h"
#include <iostream>

class Pawn : public Piece {
  public:
  Pawn(std::string colour, std::string type = "Pawn");
  ~Pawn();

  // Takes two strings (source and destination square) and a board as
  // input and returns true if move is 'pseudo-legal' for the Piece
  // (i.e., checks if move follows rules applying to the specific piece,
  // e.g., that Pawns can only move 2 spaces on first move, but not generic 
  // Piece rules like that you can't put or leave own king in check 
  // or move onto a square where your own teammate is on)
  bool validMove(
      std::string srcSquare, std::string destSquare, Piece* board[8][8]);
};