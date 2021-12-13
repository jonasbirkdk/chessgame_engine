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
  ChessBoard& operator=(ChessBoard const& other);
  ChessBoard(ChessBoard const& other);
  ~ChessBoard();

  // Takes two strings (source and destination square) as input,
  // checks that move is legal (e.g., srcSquare not empty, move doesn't
  // leave or put own king in check, move is valid for piece on srcSquare)
  // and prints the move to the console if it is legal (along with whether
  // the move captured any pieces and / or put the opponent in check),
  // otherwise prints informative error message.
  // If move is legal and results in the game to end (e.g., checkmate or
  // stalemate), this will be printed to the console too
  void submitMove(std::string srcSquare, std::string destSquare);

  // PRECONDITION: castlingType input must be either "O-O" or "O-O-O" 
  // (the letter O, not the number zero)
  // Takes one string (castling type, O-O for kingside or O-O-O for Queenside)
  // and checks that castling move is legal (i.e. king not in check, no 
  // pieces between king and castle, neither king or castle have moved before)
  // and prints move to console if legal.
  // If move is legal and results in the game to end (e.g., checkmate or
  // stalemate), this will be printed to the console too
  void submitMove(std::string castlingType);

  // Sets 'nextUp' to "White", deletes any current pieces on board,
  // and sets up a new board with all pieces in their starting positions
  void resetBoard();
};