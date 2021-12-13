#pragma once

#include <iostream>

class Piece {
  std::string colour;
  std::string type;
  bool castlingRight;

  public:
  Piece(std::string colour, std::string type, bool castlingRight)
      : colour(colour)
      , type(type)
      , castlingRight(castlingRight) {};
  Piece& operator=(Piece const& other)
  {
    this->colour = other.colour;
    this->type = other.type;
    this->castlingRight = other.castlingRight;
    return *this;
  }
  Piece(Piece const& other) { *this = other; }
  std::string getColour() const { return this->colour; }
  std::string getType() const { return this->type; }
  bool getCastlingRight() const { return this->castlingRight; }
  void setCastlingRight(bool castlingRight)
  {
    this->castlingRight = castlingRight;
  }
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