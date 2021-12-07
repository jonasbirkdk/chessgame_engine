#pragma once

#include "macros.h"
#include <iostream>

void printBoard(int board[8][8])
{
  for (int rank = 7; rank >= 0; --rank) {
    for (int file = 0; file <= 7; ++file) {
      if (board[file][rank] < 10 && board[file][rank] >= 0) {
        std::cout << " ";
      }
      std::cout << board[file][rank] << " ";
    }
    std::cout << std::endl;
  }
}

int fileToInt(std::string square) { return (square[0] - 'A'); }

int rankToInt(std::string square) { return (square[1] - '0' - 1); }

std::string integersToSquare(int file, int rank)
{
  std::string square;
  square.push_back(file + 'A');
  square.push_back(rank + '0' + 1);

  return square;
}

bool inputValid(std::string square)
{
  int file = fileToInt(square);
  int rank = rankToInt(square);

  if (file < 0 || file > 7) {
    return false;
  }

  if (rank < 0 || rank > 7) {
    return false;
  }

  return true;
}

bool diagonalMove(std::string srcSquare, std::string destSquare)
{
  int sourceFile = fileToInt(srcSquare);
  int sourceRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  if (abs(sourceFile - destFile) == abs(sourceRank - destRank)) {
    return (abs(sourceFile - destFile) > 0);
  }

  return false;
}

bool sideToSideMove(std::string srcSquare, std::string destSquare)
{
  int sourceFile = fileToInt(srcSquare);
  int sourceRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  if (sourceFile == destFile) {
    return (abs(sourceRank - destRank) > 0);
  }

  if (sourceRank == destRank) {
    return (abs(sourceFile - destFile) > 0);
  }

  return false;
}

bool squareEmpty(std::string square, int board[8][8])
{
  int file = fileToInt(square);
  int rank = rankToInt(square);

  return (board[file][rank] < 0);
}

bool friendlyFire(std::string square, int pieceType, int board[8][8])
{
  int file = fileToInt(square);
  int rank = rankToInt(square);
  // std::cout << "Checking friendly fire for " << pieceType << " on " << square << std::endl;
  if (pieceType >= W_KING && pieceType <= W_PAWN) {
    return (board[file][rank] >= W_KING && board[file][rank] <= W_PAWN);
  } else {
    return (board[file][rank] >= B_KING && board[file][rank] <= B_PAWN);
  }
}

std::string getPieceColour(std::string square, int board[8][8])
{
  int file = fileToInt(square);
  int rank = rankToInt(square);
  int pieceType = board[file][rank];

  if (pieceType >= W_KING && pieceType <= W_PAWN) {
    return "White";
  } else if (board[file][rank] >= B_KING && board[file][rank] <= B_PAWN) {
    return "Black";
  } else {
    return "Empty";
  }
}

std::string getPieceType(std::string square, int board[8][8])
{
  int file = fileToInt(square);
  int rank = rankToInt(square);

  switch (board[file][rank]) {
  case W_KING:
  case B_KING:
    return "King";
  case W_QUEEN:
  case B_QUEEN:
    return "Queen";
  case W_BISHOP:
  case B_BISHOP:
    return "Bishop";
  case W_KNIGHT:
  case B_KNIGHT:
    return "Knight";
  case W_CASTLE:
  case B_CASTLE:
    return "Castle";
  case W_PAWN:
  case B_PAWN:
    return "Pawn";
  default:
    return "Empty";
  }
}

void copyArray(int destBoard[8][8], int srcBoard[8][8])
{
  for (int file = 0; file <= 7; ++file) {
    for (int rank = 0; rank <= 7; ++rank) {
      destBoard[file][rank] = srcBoard[file][rank];
    }
  }
}

bool freePath(std::string srcSquare, std::string destSquare, int board[8][8])
{
  int sourceFile = fileToInt(srcSquare);
  int sourceRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  int currentFile;
  if (sourceFile < destFile) {
    currentFile = sourceFile + 1;
  } else if (sourceFile > destFile) {
    currentFile = sourceFile - 1;
  } else {
    currentFile = sourceFile;
  }

  int currentRank;
  if (sourceRank < destRank) {
    currentRank = sourceRank + 1;
  } else if (sourceRank > destRank) {
    currentRank = sourceRank - 1;
  } else {
    currentRank = sourceRank;
  }

  // Values to add to current file / rank in while loop.
  // Will be +1 if sourceFile(or rank) is
  // lower than destFile(or rank); -1 if
  // greater than destFile(or rank); 0 if
  // sourceFile (or rank) equals destFile (or rank)
  int fileValueChange = currentFile - sourceFile;
  int rankValueChange = currentRank - sourceRank;

  while (currentFile != destFile || currentRank != destRank) {
    if (!squareEmpty(integersToSquare(currentFile, currentRank), board)) {
      return false;
    }
    currentFile += fileValueChange;
    currentRank += rankValueChange;
  }

  return true;
}
