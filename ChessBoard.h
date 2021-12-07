#pragma once

#include "Bishop.h"
#include "Castle.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"
#include "Queen.h"
#include "helper.h"
#include "macros.h"
#include <iostream>

class ChessBoard {
  public:
  int board[8][8];
  Piece* pieceArray[TOTAL_PIECES];
  std::string nextUp = "White";

  ChessBoard()
  {
    this->resetBoard();
    for (auto i = 0; i < TOTAL_PIECES; ++i) {
      switch (i) {
      case W_KING:
      case B_KING:
        pieceArray[i] = new King;
        break;
      case W_QUEEN:
      case B_QUEEN:
        pieceArray[i] = new Queen;
        break;
      case W_BISHOP:
      case B_BISHOP:
        pieceArray[i] = new Bishop;
        break;
      case W_KNIGHT:
      case B_KNIGHT:
        pieceArray[i] = new Knight;
        break;
      case W_CASTLE:
      case B_CASTLE:
        pieceArray[i] = new Castle;
        break;
      case W_PAWN:
      case B_PAWN:
        pieceArray[i] = new Pawn;
        break;
      }
    }
  };

  bool kingInCheck(std::string srcSquare, std::string destSquare, int kingID)
  {
    int sourceFile = fileToInt(srcSquare);
    int sourceRank = rankToInt(srcSquare);
    int destFile = fileToInt(destSquare);
    int destRank = rankToInt(destSquare);
    int tmpBoard[8][8];

    copyArray(tmpBoard, this->board);
    tmpBoard[destFile][destRank] = tmpBoard[sourceFile][sourceRank];
    tmpBoard[sourceFile][sourceRank] = -1;

    std::string kingPosition;
    for (int file = 0; file <= 7; ++file) {
      for (int rank = 0; rank <= 7; ++rank) {
        if (tmpBoard[file][rank] == kingID) {
          kingPosition = integersToSquare(file, rank);
          break;
        }
      }
    }

    for (int file = 0; file <= 7; ++file) {
      for (int rank = 0; rank <= 7; ++rank) {
        std::string currentSquare = integersToSquare(file, rank);
        if (!squareEmpty(currentSquare, tmpBoard)) {
          int pieceType = tmpBoard[file][rank];
          if (this->pieceArray[pieceType]->validMove(
                  currentSquare, kingPosition, pieceType, tmpBoard)) {
            return true;
          }
        }
      }
    }

    return false;
  }

  bool noValidMoves(int kingID)
  {
    int tmpBoard[8][8];
    std::string teamColour = (kingID == B_KING) ? "Black" : "White";
    copyArray(tmpBoard, this->board);

    for (int srcFile = 0; srcFile <= 7; ++srcFile) {
      for (int srcRank = 0; srcRank <= 7; ++srcRank) {
        std::string srcSquare = integersToSquare(srcFile, srcRank);
        if (getPieceColour(srcSquare, tmpBoard) == teamColour) {
          int pieceType = tmpBoard[srcFile][srcRank];
          for (int destFile = 0; destFile <= 7; ++destFile) {
            for (int destRank = 0; destRank <= 7; ++destRank) {
              std::string destSquare = integersToSquare(destFile, destRank);
              if (this->pieceArray[pieceType]->validMove(
                      srcSquare, destSquare, pieceType, tmpBoard)) {
                if (!kingInCheck(srcSquare, destSquare, kingID)) {
                  return false;
                }
              }
            }
          }
        }
      }
    }
    return true;
  }
  void submitMove(std::string srcSquare, std::string destSquare)
  {
    int sourceFile = fileToInt(srcSquare);
    int sourceRank = rankToInt(srcSquare);
    int destFile = fileToInt(destSquare);
    int destRank = rankToInt(destSquare);
    int pieceType = this->board[sourceFile][sourceRank];

    // Checking that srcSquare has a valid piece (i.e., white
    // piece if white's turn)
    if (getPieceColour(srcSquare, this->board) != nextUp) {
      if (squareEmpty(srcSquare, this->board)) {
        std::cout << "There is no piece in position " << srcSquare << std::endl;
        return;
      }
      std::cout << "It is not ";
      if (nextUp == "White") {
        std::cout << "Black";
      } else {
        std::cout << "White";
      }
      std::cout << "'s turn to move!" << std::endl;
      return;
    }

    if (this->pieceArray[pieceType]->validMove(
            srcSquare, destSquare, pieceType, this->board)) {
      int ownKingID = (getPieceColour(srcSquare, this->board) == "White")
          ? W_KING
          : B_KING;
      if (!kingInCheck(srcSquare, destSquare, ownKingID)) {
        std::cout << nextUp << "'s " << getPieceType(srcSquare, this->board)
                  << " moves from " << srcSquare << " to " << destSquare;
        if (!squareEmpty(destSquare, this->board)) {
          std::cout << " capturing " << getPieceColour(destSquare, this->board)
                    << "'s " << getPieceType(destSquare, this->board);
        }
        std::cout << std::endl;
        this->nextUp = (getPieceColour(srcSquare, this->board) == "White")
            ? "Black"
            : "White";
        int opponentKingID = (ownKingID == W_KING) ? B_KING : W_KING;
        if (kingInCheck(srcSquare, destSquare, opponentKingID)) {
          std::cout << nextUp << " is in check";
        }
        this->board[destFile][destRank] = this->board[sourceFile][sourceRank];
        this->board[sourceFile][sourceRank] = -1;
        if (noValidMoves(opponentKingID)) {
          std::cout << "mate";
        }
        return;
      } else {
        std::cout << nextUp << "'s " << getPieceType(srcSquare, this->board)
                  << " cannot move from " << srcSquare << " to " << destSquare;
        std::cout << std::endl;
        return;
      }
    } else {
      std::cout << nextUp << "'s " << getPieceType(srcSquare, this->board)
                << " cannot move from " << srcSquare << " to " << destSquare;
      std::cout << std::endl;
    }
  }

  void resetBoard()
  {
    this->nextUp = "White";
    
    board[0][0] = W_CASTLE;
    board[1][0] = W_KNIGHT;
    board[2][0] = W_BISHOP;
    board[3][0] = W_QUEEN;
    board[4][0] = W_KING;
    board[5][0] = W_BISHOP;
    board[6][0] = W_KNIGHT;
    board[7][0] = W_CASTLE;

    board[0][7] = B_CASTLE;
    board[1][7] = B_KNIGHT;
    board[2][7] = B_BISHOP;
    board[3][7] = B_QUEEN;
    board[4][7] = B_KING;
    board[5][7] = B_BISHOP;
    board[6][7] = B_KNIGHT;
    board[7][7] = B_CASTLE;

    for (int file = 0; file <= 7; ++file) {
      board[file][6] = B_PAWN;
      board[file][1] = W_PAWN;
    }

    for (int rank = 2; rank <= 5; ++rank) {
      for (int file = 0; file <= 7; ++file) {
        board[file][rank] = -1;
      }
    }

    std::cout << "A new chess game is started!" << std::endl;
  }
};