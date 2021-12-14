#include "ChessBoard.h"
#include "King/King.h"
#include "Bishop/Bishop.h"
#include "Castle/Castle.h"
#include "Pawn/Pawn.h"
#include "Knight/Knight.h"
#include "Queen/Queen.h"
#include "helper/helper.h"
#include <iostream>

ChessBoard::ChessBoard()
{
  auto resetSquare
      = [&](int file, int rank) { this->board[file][rank] = nullptr; };
  forEachSquare(resetSquare);

  this->resetBoard();
};

ChessBoard& ChessBoard::operator=(ChessBoard const& other)
{
  this->nextUp = other.nextUp;
  this->gameOver = other.gameOver;

  auto copySquare = [&](int file, int rank) {
    if (this->board[file][rank] != nullptr) {
      delete this->board[file][rank];
    }
    if (other.board[file][rank] == nullptr) {
      this->board[file][rank] = nullptr;
      return;
    }
    if (other.board[file][rank]->getType() == "Pawn") {
      this->board[file][rank] = new Pawn(*other.board[file][rank]);
      return;
    }
    if (other.board[file][rank]->getType() == "Castle") {
      this->board[file][rank] = new Castle(*other.board[file][rank]);
      return;
    }
    if (other.board[file][rank]->getType() == "Knight") {
      this->board[file][rank] = new Knight(*other.board[file][rank]);
      return;
    }
    if (other.board[file][rank]->getType() == "Bishop") {
      this->board[file][rank] = new Bishop(*other.board[file][rank]);
      return;
    }
    if (other.board[file][rank]->getType() == "Queen") {
      this->board[file][rank] = new Queen(*other.board[file][rank]);
      return;
    }
    if (other.board[file][rank]->getType() == "King") {
      this->board[file][rank] = new King(*other.board[file][rank]);
      return;
    }
  };
  forEachSquare(copySquare);

  return *this;
}

ChessBoard::ChessBoard(ChessBoard const& other) { *this = other; }

ChessBoard::~ChessBoard()
{
  // Deleting any remaining pieces
  auto deletePiece = [&](int file, int rank) {
    if (this->board[file][rank] != nullptr) {
      delete this->board[file][rank];
    }
    this->board[file][rank] = nullptr;
  };
  forEachSquare(deletePiece);
};

void ChessBoard::submitMove(std::string srcSquare, std::string destSquare)
{
  auto srcFile = fileToInt(srcSquare);
  auto srcRank = rankToInt(srcSquare);
  auto destFile = fileToInt(destSquare);
  auto destRank = rankToInt(destSquare);

  // Check that game has not ended
  if (this->gameOver == true) {
    printErrorMessage(srcSquare, destSquare, this->board, GAME_OVER);
    return;
  }

  // Check that srcSquare and destSquare are on the board
  if (!inputValid(srcSquare) || !inputValid(destSquare)) {
    printErrorMessage(srcSquare, destSquare, this->board, INVALID_INPUT);
    return;
  }

  // Check that srcSquare and destSquare are not identical
  if (srcSquare == destSquare) {
    printErrorMessage(srcSquare, destSquare, this->board, NO_MOVE);
    return;
  }

  // Checking srcSquare is not empty
  if (this->board[srcFile][srcRank] == nullptr) {
    printErrorMessage(srcSquare, destSquare, this->board, EMPTY_SOURCE_SQUARE);
    return;
  }

  // Check destSquare does not have piece of own colour
  if (board[destFile][destRank] != nullptr
      && (board[srcFile][srcRank]->getColour()
          == board[destFile][destRank]->getColour())) {
    printErrorMessage(srcSquare, destSquare, this->board, FRIENDLY_FIRE);
    return;
  }

  // Checking that srcSquare has a valid piece (i.e., white
  // piece if white's turn)
  if (this->board[srcFile][srcRank]->getColour() != nextUp) {
    printErrorMessage(srcSquare, destSquare, this->board, NOT_YOUR_TURN);
    return;
  }

  // Check that move does not put or leave own king in check
  Piece* tmpBoard[8][8];
  copyBoard(tmpBoard, board);
  tmpBoard[destFile][destRank] = tmpBoard[srcFile][srcRank];
  tmpBoard[srcFile][srcRank] = nullptr;
  if (inCheck(nextUp, tmpBoard)) {
    printErrorMessage(srcSquare, destSquare, this->board, OWN_KING_IN_CHECK);
    return;
  }

  // Check that move is legal for piece and update board if true
  if (this->board[srcFile][srcRank]->validMove(
          srcSquare, destSquare, this->board)) {
    printMove(srcSquare, destSquare, this->board);

    if (this->board[destFile][destRank] != nullptr) {
      delete this->board[destFile][destRank];
    }
    this->board[destFile][destRank] = this->board[srcFile][srcRank];
    this->board[srcFile][srcRank] = nullptr;
    if (this->board[destFile][destRank]->getCastlingRight() == true) {
      this->board[destFile][destRank]->setCastlingRight(false);
    }

    this->nextUp = (this->nextUp == "White") ? "Black" : "White";

    if (inCheck(this->nextUp, this->board)) {
      std::cout << this->nextUp << " is in check";
      if (noValidMoves(this->nextUp, board)) {
        std::cout << "mate" << std::endl;
        this->gameOver = true;
      } else {
        std::cout << std::endl;
      }
    } else {
      if (noValidMoves(this->nextUp, board)) {
        std::cout << "Game ended in a stalemate" << std::endl;
        this->gameOver = true;
      }
    }
    return;
  } else {
    printErrorMessage(srcSquare, destSquare, this->board, PIECE_RULES_BROKEN);
    return;
  }
}

void ChessBoard::submitMove(std::string castlingType)
{
  auto castleSrcFile = (castlingType == "O-O-O") ? 0 : 7;
  auto kingSrcFile = KING;
  auto castleDestFile = (castlingType == "O-O-O") ? (KING - 1) : (KING + 1);
  auto kingDestFile = (castlingType == "O-O-O") ? (KING - 2) : (KING + 2);
  auto rank = (this->nextUp == "White") ? 0 : 7;
  auto castleSrcSquare = integersToSquare(castleSrcFile, rank);
  auto kingSrcSquare = integersToSquare(kingSrcFile, rank);

  // Check that input to submitMove() is valid castling notation
  if (castlingType != "O-O" && castlingType != "O-O-O") {
    printErrorMessage(
        kingSrcSquare, castleSrcSquare, this->board, INVALID_CASTLING);
    return;
  }

  // Check that game has not ended
  if (this->gameOver == true) {
    printErrorMessage(kingSrcSquare, castleSrcSquare, this->board, GAME_OVER);
    return;
  }

  // Check neither kingSquare or castleSquare are empty
  if (this->board[kingSrcFile][rank] == nullptr
      || this->board[castleSrcFile][rank] == nullptr) {
    printErrorMessage(
        kingSrcSquare, castleSrcSquare, this->board, INVALID_CASTLING);
    return;
  }

  // Check both King and Castle have castling rights
  if (this->board[kingSrcFile][rank]->getCastlingRight() != true
      || this->board[castleSrcFile][rank]->getCastlingRight() != true) {
    printErrorMessage(
        kingSrcSquare, castleSrcSquare, this->board, INVALID_CASTLING);
    return;
  }

  // Check King is not in check
  if (inCheck(this->nextUp, this->board)) {
    printErrorMessage(
        kingSrcSquare, castleSrcSquare, this->board, INVALID_CASTLING);
    return;
  }

  // Check no pieces between King and Castle
  if (!freePath(kingSrcSquare, castleSrcSquare, this->board)) {
    printErrorMessage(
        kingSrcSquare, castleSrcSquare, this->board, INVALID_CASTLING);
    return;
  }

  // Check move does not put own King in check
  Piece* tmpBoard[8][8];
  copyBoard(tmpBoard, board);
  tmpBoard[kingDestFile][rank] = tmpBoard[kingSrcFile][rank];
  tmpBoard[kingSrcFile][rank] = nullptr;
  tmpBoard[castleDestFile][rank] = tmpBoard[castleSrcFile][rank];
  tmpBoard[castleDestFile][rank] = nullptr;
  if (inCheck(nextUp, tmpBoard)) {
    printErrorMessage(
        kingSrcSquare, castleSrcSquare, this->board, INVALID_CASTLING);
    return;
  }

  // Make move
  std::cout << nextUp << " castles "
            << ((castlingType == "O-O-O") ? "queenside" : "kingside")
            << std::endl;
  this->board[kingDestFile][rank] = this->board[kingSrcFile][rank];
  this->board[kingSrcFile][rank] = nullptr;
  this->board[castleDestFile][rank] = this->board[castleSrcFile][rank];
  this->board[castleSrcFile][rank] = nullptr;

  // Set colour for next player and remove castling rights
  this->board[kingDestFile][rank]->setCastlingRight(false);
  this->board[castleDestFile][rank]->setCastlingRight(false);
  this->nextUp = (this->nextUp == "White") ? "Black" : "White";

  // Check for checkmate or stalemate
  if (inCheck(this->nextUp, this->board)) {
    std::cout << this->nextUp << " is in check";
    if (noValidMoves(this->nextUp, board)) {
      std::cout << "mate" << std::endl;
      this->gameOver = true;
    } else {
      std::cout << std::endl;
    }
  } else {
    if (noValidMoves(this->nextUp, board)) {
      std::cout << "Game ended in a stalemate" << std::endl;
      this->gameOver = true;
    }
  }
}

void ChessBoard::resetBoard()
{
  auto piecesPerTeam = 5;
  auto blackBackRank = 7;
  auto whiteBackRank = 0;

  std::cout << "A new chess game is started!" << std::endl;

  this->gameOver = false;
  this->nextUp = "White";

  // Setting all squares to nullptr while also
  // deleting any remaining pieces from previous games
  auto deletePiece = [&](int file, int rank) {
    if (this->board[file][rank] != nullptr) {
      delete this->board[file][rank];
    }
    this->board[file][rank] = nullptr;
  };
  forEachSquare(deletePiece);

  // Setting up all pieces on their starting positions
  for (auto file = 0u; file <= piecesPerTeam; ++file) {
    switch (file) {
    case CASTLE:
      this->board[file][blackBackRank] = new Castle("Black");
      this->board[MAX_FILE - file][blackBackRank] = new Castle("Black");
      this->board[file][whiteBackRank] = new Castle("White");
      this->board[MAX_FILE - file][whiteBackRank] = new Castle("White");
      break;
    case KNIGHT:
      this->board[file][blackBackRank] = new Knight("Black");
      this->board[MAX_FILE - file][blackBackRank] = new Knight("Black");
      this->board[file][whiteBackRank] = new Knight("White");
      this->board[MAX_FILE - file][whiteBackRank] = new Knight("White");
      break;
    case BISHOP:
      this->board[file][blackBackRank] = new Bishop("Black");
      this->board[MAX_FILE - file][blackBackRank] = new Bishop("Black");
      this->board[file][whiteBackRank] = new Bishop("White");
      this->board[MAX_FILE - file][whiteBackRank] = new Bishop("White");
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
      for (auto tmpFile = 0u; tmpFile <= MAX_FILE; ++tmpFile) {
        this->board[tmpFile][blackBackRank - 1] = new Pawn("Black");
        this->board[tmpFile][whiteBackRank + 1] = new Pawn("White");
      }
    }
  }
}
