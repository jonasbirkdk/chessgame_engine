#include "ChessBoard.h"
#include "../King/King.h"
#include "../Bishop/Bishop.h"
#include "../Castle/Castle.h"
#include "../Pawn/Pawn.h"
#include "../Knight/Knight.h"
#include "../Queen/Queen.h"
#include "../helper/helper.h"
#include <iostream>

ChessBoard::ChessBoard()
{
  int totalFiles = 7;
  int totalRanks = 7;

  for (int rank = 0; rank <= totalRanks; ++rank) {
    for (int file = 0; file <= totalFiles; ++file) {
      board[file][rank] = nullptr;
    }
  }
  this->resetBoard();
};

void ChessBoard::submitMove(std::string srcSquare, std::string destSquare)
{
  int srcFile = fileToInt(srcSquare);
  int srcRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  // Check that srcSquare and destSquare are on the board
  if (!inputValid(srcSquare) || !inputValid(destSquare)) {
    printErrorMessage(srcSquare, destSquare, this->board, INVALID_INPUT);
    return;
  }

  // Checking srcSquare is not empty
  if (squareEmpty(srcSquare, this->board)) {
    printErrorMessage(srcSquare, destSquare, this->board, EMPTY_SOURCE_SQUARE);
    return;
  }

  // Checking that srcSquare has a valid piece (i.e., white
  // piece if white's turn)
  if (this->board[srcFile][srcRank]->getColour() != nextUp) {
    printErrorMessage(srcSquare, destSquare, this->board, NOT_YOUR_TURN);
    return;
  }

  // Check destSquare does not have piece of own colour
  if (friendlyFire(srcSquare, destSquare, board)) {
    printErrorMessage(srcSquare, destSquare, this->board, FRIENDLY_FIRE);
    return;
  }

  // Check that move does not put or leave own king in check
  Piece* tmpBoard[8][8];
  copyArray(tmpBoard, board);
  tmpBoard[destFile][destRank] = tmpBoard[srcFile][srcRank];
  tmpBoard[srcFile][srcRank] = nullptr;
  if (inCheck(nextUp, tmpBoard)) {
    printErrorMessage(srcSquare, destSquare, this->board, OWN_KING_IN_CHECK);
    return;
  }

  if (this->board[srcFile][srcRank]->validMove(
          srcSquare, destSquare, this->board)) {

    printMove(srcSquare, destSquare, this->board);

    this->board[destFile][destRank] = this->board[srcFile][srcRank];
    this->board[srcFile][srcRank] = nullptr;

    this->nextUp = (this->nextUp == "White") ? "Black" : "White";

    return;

  } else {
    printErrorMessage(srcSquare, destSquare, this->board, PIECE_RULES_BROKEN);
    return;
  }
}

void ChessBoard::resetBoard()
{
  int totalFiles = 7;
  int totalRanks = 7;
  int piecesPerTeam = 5;
  int blackBackRank = 7;
  int whiteBackRank = 0;

  std::cout << "A new chess game is started!" << std::endl;

  // Setting starting team colour to White
  this->nextUp = "White";

  // Setting all squares to nullptr while also
  // deleting any remaining pieces from previous games
  for (int rank = 0; rank <= totalRanks; ++rank) {
    for (int file = 0; file <= totalFiles; ++file) {
      if (this->board[file][rank] != nullptr) {
        delete this->board[file][rank];
      }
      this->board[file][rank] = nullptr;
    }
  }

  // Setting up all pieces on their starting positions
  for (int file = 0; file <= piecesPerTeam; ++file) {
    switch (file) {
    case CASTLE:
      this->board[file][blackBackRank] = new Castle("Black");
      this->board[totalFiles - file][blackBackRank] = new Castle("Black");
      this->board[file][whiteBackRank] = new Castle("White");
      this->board[totalFiles - file][whiteBackRank] = new Castle("White");
      break;
    case KNIGHT:
      this->board[file][blackBackRank] = new Knight("Black");
      this->board[totalFiles - file][blackBackRank] = new Knight("Black");
      this->board[file][whiteBackRank] = new Knight("White");
      this->board[totalFiles - file][whiteBackRank] = new Knight("White");
      break;
    case BISHOP:
      this->board[file][blackBackRank] = new Bishop("Black");
      this->board[totalFiles - file][blackBackRank] = new Bishop("Black");
      this->board[file][whiteBackRank] = new Bishop("White");
      this->board[totalFiles - file][whiteBackRank] = new Bishop("White");
      break;
    case QUEEN:
      this->board[file][blackBackRank] = new Queen("Black");
      this->board[file][whiteBackRank] = new Queen("White");
      break;
    case KING:
      this->board[file][blackBackRank] = new King("Black");
      this->board[file][whiteBackRank] = new King("White");
      break;
    case PAWN:
      for (int tmpFile = 0; tmpFile <= totalFiles; ++tmpFile) {
        this->board[tmpFile][blackBackRank - 1] = new Pawn("Black");
        this->board[tmpFile][whiteBackRank + 1] = new Pawn("White");
      }
    }
  }
}
