#pragma once

#include <iostream>

class Piece {
  private:
  std::string colour;
  std::string type;

  public:
  Piece(std::string colour, std::string type)
      : colour(colour)
      , type(type) {};
  std::string getColour() { return this->colour; }
  std::string getType() { return this->type; }

  // NOTE: Declared virtual, to be overriden by each 'Piece' subclass
  // Takes two strings (source and destination square) and a board as
  // input and returns true if move is 'pseudo-legal' for the Piece
  // (i.e., checks if move follows rules applying to the specific piece,
  // e.g., that Bishops can only move diagonally, but not generic Piece rules
  // like that you can't put or leave own king in check or move onto a square
  // where your own teammate is on)
  virtual bool validMove(
      std::string srcSquare, std::string destSquare, Piece* board[8][8])
      = 0;
  virtual ~Piece() {};
};