#pragma once

#include "macros.h"
#include "Piece/Piece.h"
#include <iostream>

class ChessBoard {
  public:
  Piece* board[8][8];
  // Team colour for the team whose turn it is (always "White" or "Black")
  // Initialised to "White" and changes every time a legal move is made
  std::string nextUp;
  bool gameOver;

  ChessBoard();
  ~ChessBoard();

  // Sets 'nextUp' to "White", deletes any current pieces on board,
  // and sets up a new board with all pieces in their starting positions
  void resetBoard();

  // Takes two strings (source and destination square) as input,
  // checks that move is legal (e.g., srcSquare not empty, move doesn't
  // leave or put own king in check, move is valid for piece on srcSquare)
  // and prints the move to the console if it is legal (along with whether
  // the move captured any pieces and / or put the opponent in check),
  // otherwise prints informative error message.
  // If move is legal and results in the game to end (e.g., checkmate or
  // stalemate), this will be printed to the console too
  void submitMove(std::string srcSquare, std::string destSquare);
};